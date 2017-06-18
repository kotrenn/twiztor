import pygame, math, os, sys

SIZE = 500
THICKNESS = 5
RADIUS = 20

def color_lookup(color):
    data = {
	'red':            (1.0,   0.0,   0.0),
	'orange':         (1.0,   0.5,   0.0),
	'yellow':         (1.0,   1.0,   0.0),
	'green':          (0.0,   1.0,   0.0),
	'cyan':           (0.0,   1.0,   1.0),
	'blue':           (0.0,   0.0,   1.0),
	'magenta':        (1.0,   0.0,   1.0),
	'purple':         (0.5,   0.0,   0.5),
	'gray':           (0.5,   0.5,   0.5),
	'grey':           (0.5,   0.5,   0.5),
	'black':          (0.0,   0.0,   0.0),
	'white':          (1.0,   1.0,   1.0),
	'darkred':        (0.5,   0.0,   0.0),
	'darkgreen':      (0.0,   0.5,   0.0),
	'darkblue':       (0.0,   0.0,   0.5),
	'cornflowerblue': (0.392, 0.584, 0.929),
	'brown':          (0.647, 0.165, 0.165),
	'darkseagreen':   (0.561, 0.737, 0.561),
	'darkorchid':     (0.600, 0.196, 0.800),
	'yellowgreen':    (0.604, 0.804, 0.196),
	'turquoise4':     (0.000, 0.525, 0.545),
	'violet':         (0.933, 0.510, 0.933),
	'violetred':      (0.816, 0.125, 0.565),
	'violetred4':     (0.545, 0.133, 0.322),
    }
    
    unorm = data[color]
    byte = [int(255.0 * x) for x in unorm]
    return byte

class Node(object):
    def __init__(self, name, color, x, y):
        self.name = name
        self.color = color_lookup(color)
        self.x = x
        self.y = y

    def scale(self):
        self.x = int(0.45 * SIZE * self.x + 0.5 * SIZE)
        self.y = int(0.45 * SIZE * self.y + 0.5 * SIZE)

class Permutation(object):
    def __init__(self, color, cycle_list):
        self.color = color_lookup(color)
        self.cycle_list = cycle_list

class Arc(object):
    def __init__(self, color, u, v, r, flags):
        self.color = color_lookup(color)
        self.u = u
        self.v = v
        self.r = r
        self.flags = flags
        self.centerX = 0.0
        self.centerY = 0.0
        self.thetaU = 0.0
        self.thetaV = 0.0
        self.dTheta = 0.0

    def adjustCenter(self, centerX, centerY):
        self.r = self.r

    def normalize(self, radius):
        self.r /= 1.0 * radius

    def computeParameters(self):
        ux, uy = self.u.x, self.u.y
        vx, vy = self.v.x, self.v.y

        dx = ux - vx
        dy = uy - vy
        d = math.sqrt(dx * dx + dy * dy)
        r2 = self.r * self.r
        disc = r2 - d * d / 4.0
        minDisc = 0.00001
        if disc < minDisc:
            disc = minDisc
        h = math.sqrt(disc)
        midpointX = 0.5 * (ux + vx)
        midpointY = 0.5 * (uy + vy)
        dispX = vx - ux
        dispY = vy - uy
        norm = math.sqrt(dispX * dispX + dispY * dispY)
        dispX /= 1.0 * norm
        dispY /= 1.0 * norm
        rotX = dispY
        rotY = -dispX
        if self.flags[0]:
            rotX *= -1.0
            rotY *= -1.0
        self.centerX = midpointX + rotX * h
        self.centerY = midpointY + rotY * h

        deltaUX = ux - self.centerX
        deltaUY = uy - self.centerY
        deltaVX = vx - self.centerX
        deltaVY = vy - self.centerY

        self.thetaU = math.atan2(deltaUY, deltaUX)
        self.thetaV = math.atan2(deltaVY, deltaVX)
        self.dTheta = self.thetaV - self.thetaU

        if self.flags[1]:
            self.thetaU += 2.0 * math.pi
            self.dTheta = self.thetaV - self.thetaU
        if self.flags[2]:
            self.thetaU -= 2.0 * math.pi
            self.dTheta = self.thetaV - self.thetaU

        self.thetaV = self.thetaU + self.dTheta
        
    def scale(self):
        self.centerX = int(0.45 * SIZE * self.centerX + 0.5 * SIZE)
        self.centerY = int(0.45 * SIZE * self.centerY + 0.5 * SIZE)
        self.r = int(0.45 * SIZE * self.r)

def make_surface(filename):
    surface = pygame.Surface((SIZE, SIZE))
    
    white = (255, 255, 255)
    surface.fill(white)

    node_map = {}
    node_list = []
    perm_map = {}
    perm_list = []
    arc_list = []
    mapped_arcs = set([])
    
    root = '.'.join(filename.split('/')[-1].split('.')[:-1])
    with open(filename, 'r') as f:
        for line in f:
            line = line.strip()
            if len(line) == 0: continue
            vals = line.split()
            if vals[0] == 'node':
                name = vals[1]
                color = vals[2]
                x = float(vals[3])
                y = float(vals[4])
                node_map[name] = len(node_map)
                node_list += [Node(name, color, x, y)]
            if vals[0] == 'permutation':
                color = vals[1]
                cycle_list = ' '.join(vals[2:])
                sorted_names = sorted(node_map.keys(), key=len)
                for name in sorted_names[::-1]:
                    index = node_map[name]
                    cycle_list = cycle_list.replace(name, str(index))
                cycle_list = eval(cycle_list)
                perm = Permutation(color, cycle_list)
                perm_list += [perm]
                perm_map[color] = perm
            if vals[0] == 'arc':
                color = vals[2]
                u = node_list[node_map[vals[3]]]
                r = float(vals[4])
                bool_map = { '-': False, '+': True }
                flags = [bool_map[f] for f in vals[5]]
                v = None
                for cycle in perm_map[color].cycle_list:
                    for i in xrange(len(cycle)):
                        if cycle[i] == node_map[vals[3]]:
                            j = (i + 1) % len(cycle)
                            v = node_list[cycle[j]]
                            mapped_arcs |= set([(cycle[i], cycle[j])])
                arc_list += [Arc(color, u, v, r, flags)]

    centerSumX = 0
    centerSumY = 0
    for node in node_list:
        centerSumX += node.x
        centerSumY += node.y
    centerSumX /= 1.0 * len(node_list)
    centerSumY /= 1.0 * len(node_list)
    for node in node_list:
        node.x -= centerSumX
        node.y -= centerSumY
    for arc in arc_list:
        arc.adjustCenter(centerSumX, centerSumY)

    maxRadius = -1.0
    for node in node_list:
        radius = math.sqrt(node.x * node.x + node.y * node.y)
        if radius > maxRadius:
            maxRadius = radius
    for node in node_list:
        node.x /= maxRadius
        node.y /= maxRadius
    for arc in arc_list:
        arc.normalize(maxRadius)
        arc.computeParameters()

    for node in node_list:
        node.scale()
    for arc in arc_list:
        arc.scale()

    for permutation in perm_list:
        color = permutation.color
        for cycle in permutation.cycle_list:
            for i in xrange(len(cycle)):
                j = (i + 1) % len(cycle)
                u = cycle[i]
                v = cycle[j]
                if (u, v) in mapped_arcs: continue
                node_u = node_list[u]
                node_v = node_list[v]
                pygame.draw.line(surface,
                                 color,
                                 (node_u.x, node_u.y),
                                 (node_v.x, node_v.y),
                                 THICKNESS)

    for arc in arc_list:
        x = arc.centerX - arc.r
        y = arc.centerY - arc.r
        w = 2 * arc.r
        h = 2 * arc.r
        tU = arc.thetaU
        tV = arc.thetaV
        if tU > tV: tU, tV = tV, tU
        while tU < 0:
            tU += 2.0 * math.pi
            tV += 2.0 * math.pi
        #pygame.draw.arc(surface, arc.color, (x, y, w, h), tU, tV, THICKNESS)
        numIntervals = 2
        dTheta = arc.dTheta / numIntervals
        for i in xrange(numIntervals):
            thetaU = arc.thetaU +       i * dTheta
            thetaV = arc.thetaU + (i + 1) * dTheta
            pygame.draw.line(surface,
                             arc.color,
                             (arc.centerX + arc.r * math.cos(thetaU),
                              arc.centerY + arc.r * math.sin(thetaU)),
                             (arc.centerX + arc.r * math.cos(thetaV),
                              arc.centerY + arc.r * math.sin(thetaV)),
                             THICKNESS)
                
    for node in node_list:
        pygame.draw.circle(surface, node.color, (node.x, node.y), RADIUS)

    image_file = 'images/' + root + '.png'
    pygame.image.save(surface, 'bin/' + image_file)

make_surface(sys.argv[1])
