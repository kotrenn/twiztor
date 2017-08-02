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

    def cross(self, rhs):
        return self.x * rhs.y - self.y * rhs.x

    def __str__(self):
        xstr = '{0:.4f}'.format(self.x)
        ystr = '{0:.4f}'.format(self.y)
        return xstr + ' ' + ystr

    def ipair(self):
        return (int(self.x), int(self.y))

def tau(n, k):
    theta = float(k) * 2.0 * pi / float(n)
    return vec2f(cos(theta), sin(theta))

def tau_(n, k):
    theta = float(k) * -2.0 * pi / float(n) + pi
    return vec2f(cos(theta), sin(theta))

import sys

def circle_radius(p, q, r):
    pq = q - p
    pr = r - p
    qr = r - q
    top = pq.norm() * pr.norm() * qr.norm()
    bot = abs(2 * pq.cross(pr))
    if bot < 0.0001:
        return 0.0001
    return top / bot
