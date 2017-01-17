import sys
from math import *
from vec2f import *

def eval_exp(var_table, val):
    # constants
    zero = vec2f(0, 0)
    w0 = tau(3, 0)
    w1 = tau(3, 1)
    w2 = tau(3, 2)

    # load var table
    for var_name, var_value in var_table.iteritems():
        exec var_name + ' = ' + var_value

    # evaluate
    if val[0] != '%': return val
    decl = val[1]
    exp = val[2:-1]
    return str(eval(exp))

def update_vars(var_table, vals):
    if vals[0] == 'float':
        f = eval_exp(var_table, vals[2])
        var_table[vals[1]] = f
    if vals[0] == 'vec2f':
        x = eval_exp(var_table, vals[2])
        y = eval_exp(var_table, vals[3])
        var_table[vals[1]] = 'vec2f(' + x + ',' + y + ')'

var_table = {}
with open(sys.argv[1], 'r') as f:
    for line in f:
        vals = line.strip().split()
        if len(vals) == 0: continue
        update_vars(var_table, vals)
        if vals[0] == 'float' or vals[0] == 'vec2f': continue
        vals = [eval_exp(var_table, val) for val in vals]
        print ' '.join(vals)
