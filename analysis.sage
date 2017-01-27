import os

files = []
for filename in os.listdir('puzzles/'):
    if '.txt' not in filename: continue
    if 'E1' in filename: continue
    files += [filename]
files = sorted(files)
group_map = {}
for name in files:
    node_map = {}
    perm_map = {}
    perm_list = []
    with open('puzzles/' + name, 'r') as f:
        for line in f:
            vals = line.strip().split()
            if 'node' in line:
                node_map[vals[1]] = len(node_map) + 1
            if 'permutation' in line:
                perm_data = ' '.join(vals[2:])
                perm_data = perm_data[2:-2]
                perm_lists = perm_data.split('], [')
                cycles = [[node_map[y] for y in x.split(', ')] for x in perm_lists]
                perm_map[vals[1]] = cycles
                perm_list += [''.join(['(' + ','.join(map(str, c)) + ')' for c in cycles])]

    P = PermutationGroup(perm_list)
    print name + ' --> ' + str(P.order())
    root = name[:-4]
    group_map[root] = P
