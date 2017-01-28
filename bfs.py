import os

class Permutation(object):
    def __init__(self, n, cycle_list, node_index):
        self.n = n
        self.mapping = range(n)
        self.node_index = node_index
        for cycle in cycle_list:
            for i in xrange(len(cycle)):
                j = (i + 1) % len(cycle)
                self.mapping[cycle[i]] = cycle[j]

    def __mul__(self, rhs):
        ret = Permutation(self.n, [], self.node_index)
        for i in xrange(self.n):
            ret.mapping[i] = self.mapping[rhs.mapping[i]]
        return ret

    def __str__(self):
        return '_'.join([self.node_index[x] for x in self.mapping])

files = []
for filename in os.listdir('puzzles/'):
    if '.txt' not in filename: continue
    if 'E1' in filename: continue
    if len(files) > 500: continue
    files += [filename]
files = sorted(files)
for name in files:
    node_map = {}
    node_index = []
    perm_map = {}
    perm_list = []
    print name
    with open('puzzles/' + name, 'r') as f:
        for line in f:
            vals = line.strip().split()
            if 'node' in line:
                node_map[vals[1]] = len(node_map)
                node_index += [vals[1]]
            if 'permutation' in line:
                perm_data = ' '.join(vals[2:])
                perm_data = perm_data[2:-2]
                perm_lists = perm_data.split('], [')
                cycles = [[node_map[y] for y in x.split(', ')] for x in perm_lists]
                perm_map[vals[1]] = cycles
                perm_list += [Permutation(len(node_map), cycles, node_index)]
                #print cycles
                #perm_list += [''.join(['(' + ','.join(map(str, c)) + ')' for c in cycles])]

    ident = Permutation(len(node_map), [], node_index)
    group = [ident]
    keys = set([str(ident)])
    q = [ident]
    LIMIT = 1000000
    while len(q) > 0 and len(group) < LIMIT:
        top = q[-1]
        q = q[:-1]
        for p in perm_list:
            r = p * top
            if str(r) not in keys:
                keys |= set([str(r)])
                group += [r]
                q += [r]
    if len(group) < LIMIT:
        print 'Group size = ' + str(len(group))
