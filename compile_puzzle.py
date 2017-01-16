import sys
from math import *

class vec2f(object):
    def __init__(self, x, y):
        self.x = float(x)
        self.y = float(y)

    def __add__(self, rhs):
        return vec2f(self.x + rhs.x, self.y + rhs.y)

    def __sub__(self, rhs):
        return vec2f(self.x - rhs.x, self.y - rhs.y)

    def __neg__(self):
        return vec2f(-self.x, -self.y)

    def __mul__(self, rhs):
        return vec2f(self.x * float(rhs), self.y * float(rhs))

    def __div__(self, rhs):
        return vec2f(self.x / float(rhs), self.y / float(rhs))

    def __rmul__(self, lhs):
        return vec2f(float(lhs) * self.x, float(lhs) * self.y)

    def __rdiv__(self, lhs):
        return vec2f(float(lhs) / self.x, float(lhs) / self.y)

    def norm(self):
        return sqrt(self.x * self.x + self.y * self.y)

    def __str__(self):
        xstr = '{0:.4f}'.format(self.x)
        ystr = '{0:.4f}'.format(self.y)
        return xstr + ' ' + ystr

def tau(n, k):
    theta = float(k) * 2.0 * pi / float(n)
    return vec2f(cos(theta), sin(theta))

def tau_(n, k):
    theta = float(k) * -2.0 * pi / float(n) + pi
    return vec2f(cos(theta), sin(theta))

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
