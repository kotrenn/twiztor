import os, subprocess

dirname = 'puzzles'
num_puzzles = 0
with open('puzzlelist.txt', 'w') as f:
    for filename in os.listdir('puzzles'):
        if '.txt' not in filename: continue
        fullname = dirname + '/' + filename
        root = filename[:-4]
        puzname = dirname + '/' + root + '.puz'
        command = 'python compile_puzzle.py ' + fullname
        print 'Processing puzzle ' + fullname
        with open(puzname, 'w') as f2:
            subprocess.call(command.split(), stdout=f2)
        print >>f, puzname
        num_puzzles += 1
print 'Wrote ' + str(num_puzzles) + ' puzzles to puzzlelist.txt'
