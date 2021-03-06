import os, sys

center = sys.argv[1]
center = center.split('/')[-1]
center = center.split('.')[0]
center = center.split('_')[1]

GRAPH_SIZE = 500
BOX_SIZE = 100

local_nodes = set([center])

nodes = set([])
for x in os.listdir('puzzles'):
    if not '.txt' in x: continue
    root = '.'.join(x.split('.')[:-1])
    nodes |= set([root])

edges = {}
with open('map.txt', 'r') as f:
    for line in f:
        if line[0] == '#': continue
        vals = line.strip().split()
        head = vals[0][:-1] # strip the ':'
        tail = vals[1:]
        if center in [head] + tail:
            if center in tail:
                edges[head] = [center]
                local_nodes |= set([head])
            else:
                edges[head] = tail
                local_nodes |= set([head] + tail)

with open('map.dot', 'w') as f:
    print >>f, 'digraph G'
    print >>f, '{'
    print >>f, '  size="' + ','.join(map(str, [GRAPH_SIZE, GRAPH_SIZE])) + '!";'
    print >>f, '  dpi=1.0;'
    print >>f, '  node [shape=square, label="", width=.5, height=.5, fixedsize=true];'
    for node in local_nodes:
        print >>f, '  ' + node + ' [image="bin/images/' + node + '.png"];'
    for node, edge_list in edges.iteritems():
        for neighbor in edge_list:
            print >>f, '  ' + neighbor + ' -> ' + node + ';'
    print >>f, '}'

os.system('dot -Tdot map.dot -o out.dot')
os.system('dot -Tpng map.dot -o bin/images/map_' + center + '.png')

locations = {}
graph_dims = []
ratio_w = 1.0
ratio_h = 1.0
with open('out.dot', 'r') as f:
    cur_node = ''
    for line in f:
        if 'graph' in line and not 'digraph' in line:
            graph_dims = map(float, line.split('"')[1].split(','))
            ratio_w = 1.0 * GRAPH_SIZE / graph_dims[2]
            ratio_h = 1.0 * GRAPH_SIZE / graph_dims[3]
            if graph_dims[2] < graph_dims[3]:
                ratio_w *= 1.0 * graph_dims[2] / graph_dims[3]
            else:
                ratio_h *= 1.0 * graph_dims[3] / graph_dims[2]
        elif 'height=' in line:
            cur_node = line.split()[0]
        elif 'pos' in line and '->' not in line:
            pos = map(float, line.split('"')[1].split(','))
            pos[0] = ratio_w * (pos[0]) - 0.5 * BOX_SIZE
            pos[1] = ratio_h * (graph_dims[3] - pos[1]) - 0.5 * BOX_SIZE
            locations[cur_node] = pos

with open('bin/maps/map_' + center + '.html', 'w') as f:
    print >>f, '<image src="images/map_' + center + '.png" usemap="#localmap">'
    print >>f, '<map name="localmap">'
    for node in sorted(locations):
        pos = locations[node]
        coords = ','.join(map(str, pos + [BOX_SIZE + pos[0], BOX_SIZE + pos[1]]))
        url = 'index.html?puzzle=' + node
        print >>f, '<area shape="rect" coords="' + coords + '" href="' + url + '" alt="' + node + '">'
    print >>f, '</map>'
