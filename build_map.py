import os

GRAPH_SIZE = 1200
BOX_SIZE = 20

nodes = set([])
for x in os.listdir('puzzles'):
    if not '.txt' in x: continue
    root = '.'.join(x.split('.')[:-1])
    nodes |= set([root])

edges = {}
with open('map.txt', 'r') as f:
    for line in f:
        vals = line.strip().split()
        head = vals[0][:-1] # strip the ':'
        tail = vals[1:]
        edges[head] = tail

with open('map.dot', 'w') as f:
    print >>f, 'digraph G'
    print >>f, '{'
    print >>f, '  size="' + ','.join(map(str, [GRAPH_SIZE, GRAPH_SIZE])) + '!";'
    print >>f, '  dpi=1.0;'
    print >>f, '  node [shape=square, label="", width=.5, height=.5, fixedsize=true];'
    for node in nodes:
        print >>f, '  ' + node + ' [image="bin/images/' + node + '.png"];'
    for node, edge_list in edges.iteritems():
        for neighbor in edge_list:
            print >>f, '  ' + neighbor + ' -> ' + node + ';'
    print >>f, '}'

os.system('dot -Tdot map.dot -o out.dot')
os.system('dot -Tpng map.dot -o bin/map.png')

locations = {}
graph_dims = []
ratio_w = 1.0
ratio_h = 1.0
with open('out.dot', 'r') as f:
    cur_node = ''
    for line in f:
        if 'graph' in line and not 'digraph' in line:
            graph_dims = map(int, line.split('"')[1].split(','))
            ratio_w = 1.0 * GRAPH_SIZE / graph_dims[2]
            ratio_h = 1.0 * GRAPH_SIZE / graph_dims[3]
        elif 'height=' in line:
            cur_node = line.split()[0]
        elif 'pos' in line and '->' not in line:
            pos = map(int, line.split('"')[1].split(','))
            pos[0] = ratio_w * (pos[0]) - 0.5 * BOX_SIZE
            pos[1] = ratio_h * (graph_dims[3] - pos[1]) - 0.5 * BOX_SIZE
            locations[cur_node] = pos

with open('bin/map.html', 'w') as f:
    print >>f, '<html>'
    print >>f, '  <head>'
    print >>f, '    <title>Twiztor Map</title>'
    print >>f, '  </head>'
    print >>f, '  <body>'
    print >>f, '    <image src="map.png" usemap="#twiztormap">'
    print >>f, '    <map name="twiztormap">'
    for node in sorted(locations):
        pos = locations[node]
        coords = ','.join(map(str, pos + [BOX_SIZE + pos[0], BOX_SIZE + pos[1]]))
        print >>f, '      <area shape="rect" coords="' + coords + '" href="js.html" alt="' + node + '">'
    print >>f, '    </map>'
    print >>f, '  </body>'
    print >>f, '</html>'
