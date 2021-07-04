import math

from opensimplex import OpenSimplex

from configs import CONFIGS, POINT_CONFIGS

open_simplex = None

def seed(seed):
    global open_simplex
    open_simplex = OpenSimplex(seed=seed)

class StaticPoint(object):
    def __init__(self, x=0.0, y=0.0, z=None):
        global open_simplex
        self.x = x
        self.y = y
        self.z = open_simplex.noise2d(x=self.x, y=self.y) if z is None else z
    def __repr__(self):
        return str(self)
    def __str__(self):
        return f"({round(self.x, 2)}, {round(self.y, 2)})"
    def __eq__(self, p):
        return (self.x == p.x and self.y == p.y) or (self is p)
    def at(self, t):
        return StaticPoint(self.x, self.y, self.z)

class SwayingPoint(StaticPoint):
    def __init__(self, x=0.0, y=0.0, z=None):
        super().__init__(x, y, z)
    def __repr__(self):
        return str(self)
    def __str__(self):
        return super().__str__(self)
    def __eq__(self, p):
        return super().__eq__(p)
    def at(self, t):
        global open_simplex
        new_x = self.x + POINT_CONFIGS["AMPLITUDE"] * open_simplex.noise4d(
                x=self.x * POINT_CONFIGS["SCALE"],
                y=self.y * POINT_CONFIGS["SCALE"],
                z=POINT_CONFIGS["INTENSITY"] * math.cos(2 * math.pi * t),
                w=POINT_CONFIGS["INTENSITY"] * math.sin(2 * math.pi * t))
        new_y = self.y + POINT_CONFIGS["AMPLITUDE"] * open_simplex.noise4d(
                x=self.x * POINT_CONFIGS["SCALE"] + POINT_CONFIGS["OFFSET_Y"],
                y=self.y * POINT_CONFIGS["SCALE"],
                z=POINT_CONFIGS["INTENSITY"] * math.cos(2 * math.pi * t),
                w=POINT_CONFIGS["INTENSITY"] * math.sin(2 * math.pi * t))
        if new_x < 0.0 or new_x > CONFIGS["WIDTH"]:
            new_x = float((int(new_x) + CONFIGS["WIDTH"]) % CONFIGS["WIDTH"])
        if new_y < 0.0 or new_y > CONFIGS["HEIGHT"]:
            new_y = float((int(new_y) + CONFIGS["HEIGHT"]) % CONFIGS["HEIGHT"])
        return SwayingPoint(new_x, new_y, self.z)

class DriftingPoint(SwayingPoint):
    def __init__(self, x=0.0, y=0.0, z=None, dx=1, dy=1):
        super().__init__(x, y, z)
        self.dx = dx
        self.dy = dy
    def __repr__(self):
        return str(self)
    def __str__(self):
        return super().__str__(self)
    def __eq__(self, p):
        return super().__eq__(p)
    def at(self, t):
        shifted_point = super().at(t)
        new_x = shifted_point.x + CONFIGS["WIDTH"] * t * self.dx
        new_y = shifted_point.y + CONFIGS["HEIGHT"] * t * self.dy
        if new_x < 0.0 or new_x > CONFIGS["WIDTH"]:
            new_x = float((int(new_x) + CONFIGS["WIDTH"]) % CONFIGS["WIDTH"])
        if new_y < 0.0 or new_y > CONFIGS["HEIGHT"]:
            new_y = float((int(new_y) + CONFIGS["HEIGHT"]) % CONFIGS["HEIGHT"])
        return DriftingPoint(new_x, new_y, self.z)
