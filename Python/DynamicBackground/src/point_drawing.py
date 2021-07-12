class PlainPoint(object):
    def __init__(self, COLOR=None, WIDTH=1):
        self.color = COLOR if COLOR is not None else [0] * 3
        self.width = WIDTH
    def get_color(self, x, y):
        return self.color
    def get_width(self, x, y):
        return self.width