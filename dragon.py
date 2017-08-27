import os, sys

if len(sys.argv) == 1:
    for x in xrange(1, 9):
        for y in xrange(2, 4):
            for z in xrange(y, 4):
                nums = map(str, [x, y, z])
                os.system('python dragon.py ' +
                          ' '.join(nums) +
                          ' > puzzles/dragon' +
                          '_'.join(nums) +
                          '.txt')
    exit()

L = int(sys.argv[1])
m = int(sys.argv[2])
n = int(sys.argv[3])

node_palette = ['red', 'yellow', 'green', 'cyan', 'blue', 'purple']
edge_palette = ['red', 'yellow', 'green', 'blue', 'magenta', 'cyan', 'black', 'black', 'black']

rules = { 'X': 'X+YF+',
          'Y': '-FX-Y' }

curve = 'FX'
for _ in xrange(L):
    result = ''
    for x in curve:
        result += rules[x] if x in rules else x
    curve = result

curve = ''.join([x for x in curve if x not in rules])

loc = [0, 0]
vel = [[0, 1], [1, 0], [0, -1], [-1, 0]]
rot = 0

points = [list(loc)]

for action in curve:
    if action == 'F':
        loc[0] += vel[rot][0]
        loc[1] += vel[rot][1]
        points += [list(loc)]
    elif action == '+':
        rot += 1
    elif action == '-':
        rot -= 1
    rot += len(vel)
    rot %= len(vel)

points = map(tuple, points)

point_set = set([])
for p in points:
    point_set |= set([p])

def sint(x):
    return str(x) if x >= 0 else '_' + str(abs(x))

def node_str(p):
    return 'q_' + sint(p[0]) + '_' + sint(p[1])

def mod(x, n):
    while x < 0: x += n
    return x % n

def node_color(p):
    index = mod(p[0] + p[1], len(node_palette))
    return node_palette[index]

for p in point_set:
    print ' '.join(['node', node_str(p), node_color(p)] + map(str, p))

edge_sets = {edge_palette[x]: set([]) for x in xrange(m + n)}
for i in xrange(len(points) - 1):
    p = points[i]
    q = points[i + 1]
    xMin = mod(min(p[0], q[0]), m)
    yMin = mod(min(p[1], q[1]), n)
    index = xMin if p[1] == q[1] else m + yMin
    index = mod(index, len(edge_palette))
    color = edge_palette[index]
    edge_sets[color] |= set([(p, q)])

for color in edge_sets:
    edges = edge_sets[color]
    if len(edges) == 0: continue
    out = 'permutation ' + color + ' '
    cycles = []
    for p, q in edges:
        cycles += [map(node_str, [p, q])]
    out += str(cycles).replace('\'', '')
    print out
