class PlainPoint(object):
    def __init__(self, color, width):
        self.color = color
        self.width = width
    def get_color(self, x, y):
        return self.color
    def get_width(self, x, y):
        return self.width