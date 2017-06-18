import os

def color_lookup(color):
    data = {
	'red':            (1.0,   0.0,   0.0),
	'orange':         (1.0,   0.5,   0.0),
	'yellow':         (1.0,   1.0,   0.0),
	'green':          (0.0,   1.0,   0.0),
	'cyan':           (0.0,   1.0,   1.0),
	'blue':           (0.0,   0.0,   1.0),
	'magenta':        (1.0,   0.0,   1.0),
	'purple':         (0.5,   0.0,   0.5),
	'gray':           (0.5,   0.5,   0.5),
	'grey':           (0.5,   0.5,   0.5),
	'black':          (0.0,   0.0,   0.0),
	'white':          (1.0,   1.0,   1.0),
	'darkred':        (0.5,   0.0,   0.0),
	'darkgreen':      (0.0,   0.5,   0.0),
	'darkblue':       (0.0,   0.0,   0.5),
	'cornflowerblue': (0.392, 0.584, 0.929),
	'brown':          (0.647, 0.165, 0.165),
	'darkseagreen':   (0.561, 0.737, 0.561),
	'darkorchid':     (0.600, 0.196, 0.800),
	'yellowgreen':    (0.604, 0.804, 0.196),
	'turquoise4':     (0.000, 0.525, 0.545),
	'violet':         (0.933, 0.510, 0.933),
	'violetred':      (0.816, 0.125, 0.565),
	'violetred4':     (0.545, 0.133, 0.322),
    }
    
    unorm = data[color]
    byte = [int(255.0 * x) for x in unorm]
    html = ['{0:02x}'.format(x) for x in byte]
    return '#' + ''.join(html)

def header(out_file, filename):
    print >>out_file, '// ' + filename

def footer(out_file, filename):
    print >>out_file, ''
    print >>out_file, ''
    print >>out_file, ''

def append(out_file, filename):
    header(out_file, filename)
    
    with open(filename, 'r') as src_file:
        for line in src_file:
            print >>out_file, line[:-1] # skip the newline
            
    footer(out_file, filename)

def puzzle_node(out_file, vals, node_table):
    node = vals[0]
    color = color_lookup(vals[1])
    x = vals[2]
    y = vals[3]

    node_table[node] = len(node_table)
    
    line = '    '
    line += 'builder.addNode('
    line += '\'' + node  + '\', '
    line += '\'' + color + '\', '
    line += x + ', '
    line += y + ');'
    print >>out_file, line

def parse_cycle_list(cycle_list_str, node_table):
    ret = []
    current_cycle = []
    current_node = ''
    height = 0
    for x in cycle_list_str:
        if x == '[': height += 1
        elif x == ']':
            if height == 2:
                current_cycle += [node_table[current_node]]
                ret.append(current_cycle)
                current_cycle = []
                current_node = ''
            height -= 1
        elif x == ',':
            if height == 2:
                current_cycle += [node_table[current_node]]
                current_node = ''
        elif not x.isspace():
            current_node += x
            
    return ret

def puzzle_permutation(out_file, vals, node_table):
    color = color_lookup(vals[0])
    cycle_list = str(parse_cycle_list(' '.join(vals[1:]), node_table))
    line  = '    '
    line += 'builder.addPermutation('
    line += '\'' + color + '\', '
    line += cycle_list + ');'
    print >>out_file, line

def puzzle_arc_circle(out_file, vals, node_table):
    color = color_lookup(vals[0])
    node = vals[1]
    radius = vals[2]
    plus = True if vals[3][0] == '+' else False
    b_reversed = False if len(vals[3]) < 2 else (True if vals[3][1] == '+' else False)
    reflected = False if len(vals[3]) < 3 else (True if vals[3][2] == '+' else False)
    bool_table = { True: 'true', False: 'false' }
    line  = '    '
    line += 'builder.addCircleArc('
    line += '\'' + color + '\', '
    line += '\'' + node + '\', '
    line += str(radius) + ', '
    line += bool_table[plus] + ', '
    line += bool_table[b_reversed] + ', '
    line += bool_table[reflected] + ');'
    print >> out_file, line

def puzzle_arc(out_file, vals, node_table):
    if vals[0] == 'circle':
        puzzle_arc_circle(out_file, vals[1:], node_table)

def puzzle(out_file, puz_filename):
    node_table = {}

    header(out_file, puz_filename)

    puz_name = ''.join(puz_filename.split('.')[:-1]) # drop file extension
    print >>out_file, 'function ' + puz_name.split('/')[-1] + '()'
    print >>out_file, '{'
    print >>out_file, '    var builder = new PuzzleBuilder(\'' + puz_name + '\');'
    print >>out_file, ''
    
    with open(puz_filename, 'r') as puz_file:
        for line in puz_file:
            vals = line.split()
            if vals[0] == 'node':
                puzzle_node(out_file, vals[1:], node_table)
            elif vals[0] == 'permutation':
                puzzle_permutation(out_file, vals[1:], node_table)
            elif vals[0] == 'arc':
                puzzle_arc(out_file, vals[1:], node_table)

    print >>out_file, ''
    print >>out_file, '    builder.recenter();'
    print >>out_file, '    builder.normalize();'
    print >>out_file, ''
    print >>out_file, '    return builder.getPuzzleData();'
    print >>out_file, '}'
                            
    footer(out_file, puz_filename)

def print_puzzle_list(out_file, puzzle_list):
    sorted_names = sorted(puzzle_list)
    reduced_names = [''.join(name.split('.')[:-1]) for name in sorted_names]
    puzzle_funcs = [name + '()' for name in reduced_names]
    line  = 'puzzleList = ['
    line += ', '.join(puzzle_funcs)
    line += '];'
    print >>out_file, line
    print >>out_file, 'puzzleIndex = 0;'
    print >>out_file, 'puzzleData = puzzleList[puzzleIndex];'
    #print >>out_file, 'puzzleData = testAAA();'

with open('bin/game.js', 'w') as out_file:
    for js_filename in os.listdir('src/js'):
        if not '.js' in js_filename: continue
        append(out_file, 'src/js/' + js_filename)

    puzzle_list = []
    for puz_filename in os.listdir('puzzles'):
        if not '.puz' in puz_filename: continue
        puzzle(out_file, 'puzzles/' + puz_filename)
        puzzle_list += [puz_filename]

    print_puzzle_list(out_file, puzzle_list)
    print >>out_file, ''
    print >>out_file, 'main();'
    
os.system('cp src/js/index.html bin/js.html')
