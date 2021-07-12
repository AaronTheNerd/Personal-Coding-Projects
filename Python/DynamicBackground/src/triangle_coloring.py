from colorsys import hsv_to_rgb, rgb_to_hsv
import math

from helpers import interpolate
from configs import CONFIGS, POINT_CONFIGS
from triangulation import Triangle

class PlainColor(object):
    def __init__(self, COLOR=None):
        self.color = COLOR if COLOR is not None else [255] * 3
    def get_color(self, triangle):
        return self.color    

class HSVLinearGradientContinuous(object):
    def __init__(self, START_X=0, START_Y=0, END_X=CONFIGS["WIDTH"], END_Y=CONFIGS["WIDTH"], START_COLOR=None, END_COLOR=None):
        self.start_x = START_X
        self.start_y = START_Y
        self.delta_x = END_X - START_X
        self.delta_y = END_Y - START_Y
        if START_COLOR is None:
            self.start_color = rgb_to_hsv(*([1.0] * 3))
        else:
            self.start_color = rgb_to_hsv(*[START_COLOR[i] / 255 for i in range(3)])
        if END_COLOR is None:
            self.end_color = rgb_to_hsv(*([1.0] * 3))
        else:
            self.end_color = rgb_to_hsv(*[END_COLOR[i] / 255 for i in range(3)])
    def get_color_at(self, t):
        h = interpolate(self.start_color[0], self.end_color[0], t)
        s = interpolate(self.start_color[1], self.end_color[1], t)
        v = interpolate(self.start_color[2], self.end_color[2], t)
        rgb = hsv_to_rgb(h, s, v)
        return tuple([int(rgb[i] * 255) for i in range(3)])
    def get_color(self, triangle):
        center = triangle.center()
        x, y = center[0], center[1]
        t = (self.delta_x * (x - self.start_x) + self.delta_y * (y - self.start_y)) / ((self.delta_x)**2 + (self.delta_y)**2)
        return self.get_color_at(t)

class HSVExponentialGradientContinuous(HSVLinearGradientContinuous):
    def __init__(self, START_X=0, START_Y=0, END_X=CONFIGS["WIDTH"], END_Y=CONFIGS["HEIGHT"], START_COLOR=None, END_COLOR=None, ALPHA=1.0):
        super().__init__(START_X=START_X, START_Y=START_Y, END_X=END_X, END_Y=END_Y, START_COLOR=START_COLOR, END_COLOR=END_COLOR)
        self.alpha = ALPHA
    def get_color(self, triangle):
        center = triangle.center()
        x, y = center[0], center[1]
        t = (self.delta_x * (x - self.start_x) + self.delta_y * (y - self.start_y)) / ((self.delta_x)**2 + (self.delta_y)**2)
        t_scaled = (math.exp(self.alpha * t) - 1) / (math.exp(self.alpha) - 1)
        return super().get_color_at(t_scaled)

class HSVLinearGradientDiscrete(HSVLinearGradientContinuous):
    def __init__(self, START_X=0, START_Y=0, END_X=CONFIGS["WIDTH"], END_Y=CONFIGS["WIDTH"], START_COLOR=None, END_COLOR=None, NUM_OF_COLORS=1):
        super().__init__(START_X=START_X, START_Y=START_Y, END_X=END_X, END_Y=END_Y, START_COLOR=START_COLOR, END_COLOR=END_COLOR)
        self.num_of_colors = NUM_OF_COLORS
    def get_color(self, triangle):
        center = triangle.center()
        x, y = center[0], center[1]
        t = (self.delta_x * (x - self.start_x) + self.delta_y * (y - self.start_y)) / ((self.delta_x)**2 + (self.delta_y)**2)
        t *= self.num_of_colors
        t = int(t)
        t /= self.num_of_colors - 1
        return super().get_color_at(t)
    
# All credit to Scratchapixel 2.0 for how to properly shade the triangles
# https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/shading-normals
class AmbientShader(object):
    def __init__(self, AMBIENT_COLOR=None, AMBIENT_VECTOR=None, AMBIENT_GAIN=1.0, AMBIENT_DEFINITION=1):
        self.ambient_color = AMBIENT_COLOR if AMBIENT_COLOR is not None else [255] * 3
        self.ambient_vector = AmbientShader.normalize3d(AMBIENT_VECTOR) if AMBIENT_VECTOR is not None else [0.0, 0.0, 1.0]
        self.ambient_gain = AMBIENT_GAIN
        self.ambient_definition = AMBIENT_DEFINITION
    @staticmethod
    def cross3d(v1, v2):
        return [v1[1] * v2[2] - v1[2] * v2[1],
                v1[2] * v2[0] - v1[0] * v2[2],
                v1[0] * v2[1] - v1[1] * v2[0]]
    @staticmethod
    def normalize3d(v):
        mag = math.sqrt(v[0] ** 2 + v[1] ** 2 + v[2] ** 2)
        return [n / mag for n in v]
    @staticmethod
    def dot_product3d(v1, v2):
        return sum([v1[i] * v2[i] for i in range(3)])
    @staticmethod
    def get_normal(triangle):
        a, b, c = triangle.a, triangle.b, triangle.c
        edge1 = [b.x - a.x, b.y - a.y, b.z - a.z]
        edge2 = [c.x - a.x, c.y - a.y, c.z - a.z]
        # Perform cross product to find normal vector
        normal = AmbientShader.cross3d(edge1, edge2)
        # Check normal vector is facing toward "camera" (z is positive)
        if normal[2] < 0:
            normal = [-normal[i] for i in range(3)]
        # Normalize normal
        return AmbientShader.normalize3d(normal)
    def get_color(self, triangle):
        normal = AmbientShader.get_normal(triangle)
        if normal is None:
            return [0, 0, 0]
        # Normalize inverse ray direction
        # Generate facing ratio
        facing_ratio = AmbientShader.dot_product3d(normal, self.ambient_vector) ** self.ambient_definition
        facing_ratio *= self.ambient_gain
        # Clamp facing ratio between 0 and 1
        t = min(max(0.0, facing_ratio), 1.0)
        return tuple([int(self.ambient_color[i] * t) for i in range(3)])

class MultiLightShader(AmbientShader):
    def __init__(self, AMBIENT_COLOR=None, AMBIENT_VECTOR=None, AMBIENT_GAIN=1.0, AMBIENT_DEFINITION=1, GAIN=1.0, LIGHTS=None):
        super().__init__(AMBIENT_COLOR=AMBIENT_COLOR, AMBIENT_VECTOR=AMBIENT_VECTOR, AMBIENT_GAIN=AMBIENT_GAIN, AMBIENT_DEFINITION=AMBIENT_DEFINITION)
        self.gain = GAIN
        self.lights = LIGHTS if LIGHTS is not None else []
    def get_color(self, triangle):
        rgb = super().get_color(triangle)
        center = triangle.center()
        for light in self.lights:
            L = [light["POS"][i] - center[i] for i in range(3)]
            L = AmbientShader.normalize3d(L)
            normal = AmbientShader.get_normal(triangle)
            dist_sqr = sum([(light["POS"][i] - center[i]) ** 2 for i in range(3)])
            facing_ratio = self.gain * max(0.0, AmbientShader.dot_product3d(normal, L))
            light_ratio = min(light["INTENSITY"] / dist_sqr * facing_ratio, 1.0)
            rgb = [light_ratio * light["COLOR"][i] + rgb[i] for i in range(3)]
        return tuple([int(rgb[i]) for i in range(3)])
