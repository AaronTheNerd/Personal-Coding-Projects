from colorsys import hsv_to_rgb, rgb_to_hsv
import math

class PlainColor(object):
    def __init__(self, color):
        self.color = color
    def __dict__(self):
        return {
            "TYPE": self.__class__.__name__,
            "COLOR": self.color
        }
    def get_color_at(self, t):
        return self.color
    def get_color(self, x, y):
        return self.color    

class HSVLinearGradientContinuous(object):
    def __init__(self , start_x, start_y, end_x, end_y, start_color, end_color):
        self.start_x = start_x
        self.start_y = start_y
        self.delta_x = end_x - start_x
        self.delta_y = end_y - start_y
        self.start_color = rgb_to_hsv(start_color[0] / 255, start_color[1] / 255, start_color[2] / 255)
        self.end_color = rgb_to_hsv(end_color[0] / 255, end_color[1] / 255, end_color[2] / 255)
    def __dict__(self):
        rgb_start = hsv_to_rgb(self.start_color[0], self.start_color[1], self.start_color[2])
        rgb_end = hsv_to_rgb(self.end_color[0], self.end_color[1], self.end_color[2])
        return {
            "TYPE": self.__class__.__name__,
            "START_X": self.start_x,
            "START_Y": self.start_y,
            "END_X": self.start_x + self.delta_x,
            "END_Y": self.start_y + self.delta_y,
            "START_COLOR": (int(rgb_start[0] * 255), int(rgb_start[1] * 255), int(rgb_start[2] * 255)),
            "END_COLOR": (int(rgb_end[0] * 255), int(rgb_end[1] * 255), int(rgb_end[2] * 255))
        }
    @staticmethod
    def interpolate(start, end, t):
        return (end - start) * t + start
    def get_color_at(self, t):
        h = HSVLinearGradientContinuous.interpolate(self.start_color[0], self.end_color[0], t)
        s = HSVLinearGradientContinuous.interpolate(self.start_color[1], self.end_color[1], t)
        v = HSVLinearGradientContinuous.interpolate(self.start_color[2], self.end_color[2], t)
        rgb = hsv_to_rgb(h, s, v)
        return (int(rgb[0] * 255), int(rgb[1] * 255), int(rgb[2] * 255))
    def get_color(self, x, y):
        t = (self.delta_x * (x - self.start_x) + self.delta_y * (y - self.start_y)) / ((self.delta_x)**2 + (self.delta_y)**2)
        return self.get_color_at(t)

class HSVExponentialGradientContinuous(HSVLinearGradientContinuous):
    def __init__(self , start_x, start_y, end_x, end_y, start_color, end_color, alpha):
        super().__init__(start_x, start_y, end_x, end_y, start_color, end_color)
        self.alpha = alpha
    def __dict__(self):
        info = super().__dict__()
        info['ALPHA'] = self.alpha
        return info
    def interpolate(self, start, end, t):
        t_scaled = (math.exp(self.alpha * t) - 1) / (math.exp(self.alpha) - 1)
        return (end - start) * t_scaled + start
    def get_color_at(self, t):
        h = self.interpolate(self.start_color[0], self.end_color[0], t)
        s = self.interpolate(self.start_color[1], self.end_color[1], t)
        v = self.interpolate(self.start_color[2], self.end_color[2], t)
        rgb = hsv_to_rgb(h, s, v)
        return (int(rgb[0] * 255), int(rgb[1] * 255), int(rgb[2] * 255))
    def get_color(self, x, y):
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
    def get_color(self, x, y):
        t = (self.delta_x * (x - self.start_x) + self.delta_y * (y - self.start_y)) / ((self.delta_x)**2 + (self.delta_y)**2)
        t *= self.num_of_colors
        t = int(t)
        t /= self.num_of_colors - 1
        return self.get_color_at(t)
    