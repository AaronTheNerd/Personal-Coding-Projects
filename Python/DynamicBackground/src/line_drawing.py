from colorsys import hsv_to_rgb, rgb_to_hsv
import math

from configs import POINT_CONFIGS

class SolidLine(object):
    def __init__(self, color, width):
        self.color = color
        self.width = width
    def get_color(self, edge):
        return self.color
    def get_width(self, edge):
        return self.width

class FadingLine(object):
    def __init__(self, start_color, end_color, min_dist, max_dist, width):
        self.start_color = rgb_to_hsv(start_color[0] / 255, start_color[1] / 255, start_color[2] / 255)
        self.end_color = rgb_to_hsv(end_color[0] / 255, end_color[1] / 255, end_color[2] / 255)
        self.min_dist = min_dist
        self.max_dist = max_dist
        self.width = width
    def __dict__(self):
        rgb_start = hsv_to_rgb(self.start_color[0], self.start_color[1], self.start_color[2])
        rgb_end = hsv_to_rgb(self.end_color[0], self.end_color[1], self.end_color[2])
        return {
            "TYPE": self.__class__.__name__,
            "START_COLOR": [int(rgb_start[0] * 255), int(rgb_start[1] * 255), int(rgb_start[2] * 255)],
            "END_COLOR": [int(rgb_end[0] * 255), int(rgb_end[1] * 255), int(rgb_end[2] * 255)],
            "MIN_DIST": self.min_dist,
            "MAX_DIST": self.min_dist,
            "WIDTH": self.width,
        }
    def get_color(self, edge):
        dist = math.sqrt((edge[0].x - edge[1].x) ** 2 + (edge[0].y - edge[1].y) ** 2)
        if dist < self.min_dist:
            start_rgb = hsv_to_rgb(self.start_color[0], self.start_color[1], self.start_color[2])
            return [int(start_rgb[0] * 255), int(start_rgb[1] * 255), int(start_rgb[2] * 255)]
        if dist > self.max_dist:
            end_rgb = hsv_to_rgb(self.end_color[0], self.end_color[1], self.end_color[2])
            return [int(end_rgb[0] * 255), int(end_rgb[1] * 255), int(end_rgb[2] * 255)]
        return self.color
    def get_width(self, edge):
        return self.width