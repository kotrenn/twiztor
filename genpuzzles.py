import os, subprocess

dirname = 'puzzles'
num_puzzles = 0
with open('puzzlelist.txt', 'w') as f:
    for filename in os.listdir('puzzles'):
        if '.puz' not in filename: continue
        fullname = dirname + '/' + filename
        print >>f, fullname
        num_puzzles += 1
print 'Wrote ' + str(num_puzzles) + ' puzzles to puzzlelist.txt'
