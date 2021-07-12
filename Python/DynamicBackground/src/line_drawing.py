from colorsys import hsv_to_rgb, rgb_to_hsv
from helpers import interpolate
import math

class SolidLine(object):
    def __init__(self, COLOR=None, WIDTH=1):
        self.color = COLOR if COLOR is not None else [0] * 3
        self.width = WIDTH
    def get_color(self, edge):
        return self.color
    def get_width(self, edge):
        return self.width

class FadingLine(object):
    def __init__(self, START_COLOR=None, END_COLOR=None, MIN_DIST=0, MAX_DIST=0, WIDTH=1):
        self.start_color = rgb_to_hsv(*[START_COLOR[i] / 255 for i in range(3)]) if START_COLOR is not None else [0.0] * 3
        self.end_color = rgb_to_hsv(*[END_COLOR[i] / 255 for i in range(3)]) if END_COLOR is not None else [0.0] * 3
        self.min_dist = MIN_DIST
        self.max_dist = MAX_DIST
        self.width = WIDTH
    def get_color_at(self, t):
        h = interpolate(self.start_color[0], self.end_color[0], t)
        s = interpolate(self.start_color[1], self.end_color[1], t)
        v = interpolate(self.start_color[2], self.end_color[2], t)
        rgb = hsv_to_rgb(h, s, v)
        return (int(rgb[0] * 255), int(rgb[1] * 255), int(rgb[2] * 255))
    def get_color(self, edge):
        dist = math.sqrt((edge[0].x - edge[1].x) ** 2 + (edge[0].y - edge[1].y) ** 2)
        if dist < self.min_dist:
            start_rgb = hsv_to_rgb(self.start_color[0], self.start_color[1], self.start_color[2])
            return [int(start_rgb[0] * 255), int(start_rgb[1] * 255), int(start_rgb[2] * 255)]
        if dist > self.max_dist:
            end_rgb = hsv_to_rgb(self.end_color[0], self.end_color[1], self.end_color[2])
            return [int(end_rgb[0] * 255), int(end_rgb[1] * 255), int(end_rgb[2] * 255)]
        t = (dist - self.min_dist) / (self.max_dist - self.min_dist)
        return self.get_color_at(t)
    def get_width(self, edge):
        return self.width