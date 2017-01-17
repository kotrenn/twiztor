import pygame
from vec2f import *

FONT_SIZE = 20
font = None

def draw_string(dst, msg, x, y, centered=False):
    black = (0, 0, 0)
    text = font.render(msg, True, black)
    if centered:
        x -= text.get_width() / 2
        y -= text.get_height() / 2
    dst.blit(text, (x, y))

TILE_RADIUS = 40.0

DIR_UP = 0
DIR_LEFT_UP = 1
DIR_LEFT_DOWN = 2
DIR_DOWN = 3
DIR_RIGHT_DOWN = 4
DIR_RIGHT_UP = 5

def dir_to_vec2f(the_dir):
    return tau(12, -the_dir * 2 - 5)

class HexTile(object):
    def __init__(self, center):
        self.center = center
        self.radius = TILE_RADIUS
        self.selected = False
        self.text = '???'

    def get_corners(self):
        return [tau(6, i) * self.radius + self.center for i in xrange(6)]

    def is_in_hex(self, p):
	corners = self.get_corners()
	for i in xrange(6):
            j = (i + 1) % 6
            k = (i + 2) % 6
            q = corners[j]
            r = corners[i]
            s = corners[k]
            qr = r - q
            qp = p - q
            qs = s - q
            rpSign = qr.cross(qp) > 0
            psSign = qp.cross(qs) > 0
            rsSign = qr.cross(qs) > 0
            if rpSign != psSign: return False
            if rpSign != rsSign: return False
            if psSign != rsSign: return False
        return True

    def paint(self, dst, camera):
        black = (0, 0, 0)
        red = (255, 0, 0)
        corners = self.get_corners()
        for i in xrange(6):
            j = (i + 1) % 6
            p1 = corners[i] - camera
            p2 = corners[j] - camera
            color = black
            if self.selected: color = red
            pygame.draw.line(dst, color, p1.ipair(), p2.ipair())
        cx, cy = (self.center - camera).ipair()
        draw_string(dst, self.text, cx, cy, True)

    def toggle_selected(self):
        self.selected = self.selected == False

    def make_neighbor(self, the_dir):
        vel = 2 * self.radius * dir_to_vec2f(the_dir)
        return HexTile(self.center + vel)

    def save_to_file(self, f):
        if len(self.text) == 0: self.text = '???'
        print >>f, self.text + ' ' + str(self.center / TILE_RADIUS)

class HexMap(object):
    def __init__(self, filename, width, height):
        self.tiles = [HexTile(vec2f(0, 0))]
        self.start_camera = vec2f(-width / 2, -height / 2)
        self.camera = vec2f(0, 0)
        self.cur_selection = None
        self.set_selection(self.tiles[-1])
        self.text_editing = False
        self.filename = filename

        self.reset_camera()

    def reset_camera(self):
        self.camera.x = self.start_camera.x
        self.camera.y = self.start_camera.y

    def update(self):
        if self.text_editing: return
        
        keys = pygame.key.get_pressed()

        # move camera
        speed = 3
        key_mappings = {
            pygame.K_UP: vec2f(0, -speed),
            pygame.K_DOWN: vec2f(0, speed),
            pygame.K_LEFT: vec2f(-speed, 0),
            pygame.K_RIGHT: vec2f(speed, 0),
            pygame.K_w: vec2f(0, -speed),
            pygame.K_s: vec2f(0, speed),
            pygame.K_a: vec2f(-speed, 0),
            pygame.K_d: vec2f(speed, 0)
        }

        for key, vel in key_mappings.iteritems():
            if keys[key]: self.camera += vel
        
    def key_up(self, key):
        # text mode
        if self.text_editing:
            if key == pygame.K_RETURN:
                self.text_editing = False
            elif key == pygame.K_BACKSPACE:
                if len(self.cur_selection.text) > 0:
                    self.cur_selection.text = self.cur_selection.text[:-1]
            elif key == pygame.K_SPACE:
                return
            else:
                if self.cur_selection.text == '???':
                    self.cur_selection.text = ''
                self.cur_selection.text += pygame.key.name(key).upper()
            return

        if key == pygame.K_0:
            self.save_to_file()
        if key == pygame.K_BACKSLASH:
            self.load_from_file()
            
        if self.cur_selection is None:
            return

        # enter typing mode
        if key == pygame.K_e:
            self.text_editing = True
            
        # create a new hex
        key_mappings = {
            pygame.K_u: DIR_UP,
            pygame.K_i: DIR_RIGHT_UP,
            pygame.K_k: DIR_RIGHT_DOWN,
            pygame.K_m: DIR_DOWN,
            pygame.K_n: DIR_LEFT_DOWN,
            pygame.K_h: DIR_LEFT_UP
        }

        if key in key_mappings:
            the_dir = key_mappings[key]
            new_tile = self.cur_selection.make_neighbor(the_dir)
            self.add_tile(new_tile)
            self.set_selection(new_tile)

        if key == pygame.K_DELETE and len(self.tiles) > 1:
            self.tiles.remove(self.cur_selection)
            self.cur_selection = None

    def paint(self, dst):
        draw_string(dst, str(len(self.tiles)), 5, 5)
        if self.cur_selection is not None:
            cur_text = self.cur_selection.text
            draw_string(dst, cur_text, 5, 25)
            if self.text_editing:
                draw_string(dst, '[Editing]', 5, 45)
        
        for tile in self.tiles:
            tile.paint(dst, self.camera)

    def mouse_clicked(self):
        x, y = pygame.mouse.get_pos()
        coord = vec2f(x, y)
        for tile in self.tiles:
            if tile.is_in_hex(coord + self.camera):
                self.set_selection(tile)

    def add_tile(self, new_tile):
        for tile in self.tiles:
            if tile.is_in_hex(new_tile.center): return
        self.tiles += [new_tile]

    def set_selection(self, new_tile):
        if self.cur_selection is not None:
            self.cur_selection.toggle_selected()
        self.cur_selection = new_tile
        if new_tile is not None:
            new_tile.toggle_selected()

    def save_to_file(self):
        with open(self.filename, 'w') as f:
            for tile in self.tiles:
                tile.save_to_file(f)

    def load_from_file(self):
        self.tiles = []
        with open(self.filename, 'r') as f:
            for line in f:
                vals = line.strip().split()
                text = vals[0]
                x = float(vals[1])
                y = float(vals[2])
                center = vec2f(x, y) * TILE_RADIUS
                new_tile = HexTile(center)
                new_tile.text = text
                self.add_tile(new_tile)
        self.reset_camera()

def main():
    global font

    white = (255, 255, 255)
    size = width, height = 640, 480

    passed, failed = pygame.init()
    pygame.display.init()
    screen = pygame.display.set_mode(size)
    pygame.display.set_caption('Hex editor')
    pygame.font.init()

    font = pygame.font.Font(pygame.font.get_default_font(), FONT_SIZE)

    hex_map = HexMap('world.txt', width, height)

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    running = False
            elif event.type == pygame.KEYUP:
                hex_map.key_up(event.key)
            elif event.type == pygame.MOUSEBUTTONUP:
                hex_map.mouse_clicked()

        #update
        hex_map.update()

        #draw
        screen.fill(white)
        hex_map.paint(screen)
        pygame.display.flip()

        pygame.time.delay(1000 / 30)
        
    pygame.quit()

main()

