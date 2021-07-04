from colorsys import hsv_to_rgb, rgb_to_hsv
import math

from configs import CONFIGS, POINT_CONFIGS

class PlainColor(object):
    def __init__(self, color):
        self.color = color
    def get_color(self, triangle):
        return self.color    

class HSVLinearGradientContinuous(object):
    def __init__(self , start_x, start_y, end_x, end_y, start_color, end_color):
        self.start_x = start_x
        self.start_y = start_y
        self.delta_x = end_x - start_x
        self.delta_y = end_y - start_y
        self.start_color = rgb_to_hsv(start_color[0] / 255, start_color[1] / 255, start_color[2] / 255)
        self.end_color = rgb_to_hsv(end_color[0] / 255, end_color[1] / 255, end_color[2] / 255)
    @staticmethod
    def interpolate(start, end, t):
        return (end - start) * t + start
    def get_color_at(self, t):
        h = HSVLinearGradientContinuous.interpolate(self.start_color[0], self.end_color[0], t)
        s = HSVLinearGradientContinuous.interpolate(self.start_color[1], self.end_color[1], t)
        v = HSVLinearGradientContinuous.interpolate(self.start_color[2], self.end_color[2], t)
        rgb = hsv_to_rgb(h, s, v)
        return (int(rgb[0] * 255), int(rgb[1] * 255), int(rgb[2] * 255))
    def get_color(self, triangle):
        center = triangle.center()
        x, y = center[0], center[1]
        t = (self.delta_x * (x - self.start_x) + self.delta_y * (y - self.start_y)) / ((self.delta_x)**2 + (self.delta_y)**2)
        return self.get_color_at(t)

class HSVExponentialGradientContinuous(HSVLinearGradientContinuous):
    def __init__(self , start_x, start_y, end_x, end_y, start_color, end_color, alpha):
        super().__init__(start_x, start_y, end_x, end_y, start_color, end_color)
        self.alpha = alpha
    def interpolate(self, start, end, t):
        t_scaled = (math.exp(self.alpha * t) - 1) / (math.exp(self.alpha) - 1)
        return (end - start) * t_scaled + start
    def get_color_at(self, t):
        h = self.interpolate(self.start_color[0], self.end_color[0], t)
        s = self.interpolate(self.start_color[1], self.end_color[1], t)
        v = self.interpolate(self.start_color[2], self.end_color[2], t)
        rgb = hsv_to_rgb(h, s, v)
        return (int(rgb[0] * 255), int(rgb[1] * 255), int(rgb[2] * 255))
    def get_color(self, triangle):
        center = triangle.center()
        x, y = center[0], center[1]
        t = (self.delta_x * (x - self.start_x) + self.delta_y * (y - self.start_y)) / ((self.delta_x)**2 + (self.delta_y)**2)
        return self.get_color_at(t)

class HSVLinearGradientDiscrete(HSVLinearGradientContinuous):
    def __init__(self, start_x, start_y, end_x, end_y, start_color, end_color, num_of_colors):
        super().__init__(start_x, start_y, end_x, end_y, start_color, end_color)
        self.num_of_colors = num_of_colors
    def __dict__(self):
        info = super().__dict__()
        info['NUM_OF_COLORS'] = self.num_of_colors
        return info
    @staticmethod
    def interpolate(start, end, t):
        return super().interpolate(start, end, t)
    def get_color_at(self, t):
        return super().get_color_at(t)
    def get_color(self, triangle):
        center = triangle.center()
        x, y = center[0], center[1]
        t = (self.delta_x * (x - self.start_x) + self.delta_y * (y - self.start_y)) / ((self.delta_x)**2 + (self.delta_y)**2)
        t *= self.num_of_colors
        t = int(t)
        t /= self.num_of_colors - 1
        return self.get_color_at(t)
    
# All credit to Scratchapixel 2.0 for how to properly shade the triangles
# https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/shading-normals
class FlatShader(object):
    def __init__(self, cam_pos, gain):
        self.cam_pos = cam_pos
        self.gain = gain
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
    def get_color(self, triangle):
        a, b, c = triangle.a, triangle.b, triangle.c
        edge1 = [b.x - a.x, b.y - a.y, b.z - a.z]
        edge2 = [c.x - a.x, c.y - a.y, c.z - a.z]
        # Perform cross product to find normal vector
        normal = FlatShader.cross3d(edge1, edge2)
        # Check normal vector is facing toward "camera" (z is positive)
        if normal[2] < 0:
            normal = [-normal[i] for i in range(3)]
        # Normalize normal
        normal = FlatShader.normalize3d(normal)
        if normal is None:
            return [0, 0, 0]
        P = triangle.center()
        V = [self.cam_pos[i] - P[i] for i in range(3)]
        # Normalize inverse ray direction
        V = FlatShader.normalize3d(V)
        facingRatio = max(0, FlatShader.dot_product3d(normal, V))
        return [round(255 * self.gain * facingRatio) for _ in range(3)]
