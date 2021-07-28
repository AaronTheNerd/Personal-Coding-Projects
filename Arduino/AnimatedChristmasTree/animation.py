import random 

class Color(object):
    def __init__(self, red=0xFF, green=0xFF, blue=0xFF):
        self.red = red & 0xFF
        self.green = green & 0xFF
        self.blue = blue & 0xFF

    def __str__(self):
        return "Color(" + str(self.red) + ", " + str(self.green) + ", " + str(self.blue) + ")"

    def __eq__(self, color):
        return self.red == color.red and self.green == color.green and self.blue == color.blue

    def __hash__(self):
        return id(self)


class Frame(object):
    def __init__(self, hold=50, leds={}):
        self.hold = hold & 0xFFFF
        self.leds = leds

    def set_all(self, color):
        for i in range(50):
            self.leds[i] = color

    def clear(self):
        self.leds.clear()

    def __str__(self):
        ret = "Frame(" + str(self.hold) + ", {"
        for index, color in self.leds.items():
            ret += str(index) + ": " + str(color) + ", "
        ret = ret.rstrip(", ")
        ret += "})"
        return ret

    def __eq__(self, frame):
        if len(self.leds) != len(frame.leds) or self.hold != frame.hold:
            return False
        for i in range(len(self.leds)):
            if self.leds[i] != frame.leds[i]:
                return False
        return True


class Animation(object):
    def __init__(self, frames=[], repeat=0):
        self.frames = frames
        self.repeat = repeat

    def clear(self):
        for frame in self.frames:
            frame.clear()

    def chasingLights(self, repeat=1, hold=50):
        for i in range(repeat):
            for j in range(50):
                self.frames.append(Frame(hold, {j: Color()}))
            for j in range(50):
                self.frames.append(Frame(hold, {49 - j: Color()}))

    def colorChanging(self, repeat=1, hold=1000):
        for i in range(repeat):
            for j in range(1, 8):
                self.frames.append(Frame(1000, {}))
                self.frames[-1].set_all(Color(255 if (j & 0x4) else 0, 255 if (j & 0x2) else 0, 255 if (j & 0x1) else 0))

    def singularColorSwapping(self, color1=Color(255, 0, 0), color2=Color(0, 255, 0), repeat=1, hold=750):
        for i in range(repeat):
            self.frames.append(Frame(hold, {}))
            for j in range(50):
                if i % 2 == j % 2:
                    self.frames[-1].leds[j] = color1
                else:
                    self.frames[-1].leds[j] = color2

    def multipleColorSwapping(self, color1=Color(255, 0, 0), color2=Color(0, 255, 0), multiple=3, repeat=1, hold=250):
        for i in range(repeat):
            for j in range(2 * multiple):
                self.frames.append(Frame(hold, {}))
                for k in range(50):
                    if (k + j) % (2 * multiple) < multiple:
                        self.frames[-1].leds[k] = color1
                    else:
                        self.frames[-1].leds[k] = color2

    def snake(self, background=Color(0, 255, 0), color=Color(255, 0, 0), length=7, repeat=1, hold=150):
        for i in range(repeat):
            for j in range(50):
                self.frames.append(Frame(hold, {}))
                self.frames[-1].set_all(background)
                for k in range(length):
                    if j + k < 50:
                        self.frames[-1].leds[j + k] = color

    def boop(self, background=Color(0, 255, 0), color=Color(255, 0, 0), repeat=1, hold=150):
        for i in range(repeat):
            for j in range(50):
                self.frames.append(Frame(hold, {}))
                self.frames[-1].set_all(background)
                self.frames[-1].leds[j] = color
                self.frames[-1].leds[49 - j] = color

    def gradualColorChange(self, color1=Color(255, 0, 0), color2=Color(0, 255, 0), repeat=1, hold=150):
        for i in range(repeat):
            for j in range(25):
                self.frames.append(Frame(hold, {}))
                self.frames[-1].set_all(color1)
                for k in range(j):
                    self.frames[-1].leds[k] = color2
                    self.frames[-1].leds[49 - k] = color2
            for j in range(25):
                self.frames.append(Frame(hold, {}))
                self.frames[-1].set_all(color2)
                for k in range(j):
                    self.frames[-1].leds[k] = color1
                    self.frames[-1].leds[49 - k] = color1

    def gradient(self, repeat=1, hold=150):
        for i in range(repeat):
            for j in range(0, 256, 5):
                self.frames.append(Frame(hold, {}))
                self.frames[-1].set_all(Color(j, 255 - j, 0))
            for j in range(0, 256, 5):
                self.frames.append(Frame(hold, {}))
                self.frames[-1].set_all(Color(255 - j, j, 0))

    def spinningRainbow(self, repeat=1, hold=200):
        strips = [[0, 17],
                      [1, 16],
                      [2, 15, 18, 31],
                      [3, 14, 19, 30],
                      [4, 13, 20, 29, 32, 41],
                      [5, 12, 21, 28, 33, 40],
                      [6, 11, 22, 27, 34, 39, 42, 47],
                      [7, 10, 23, 26, 35, 38, 43, 46],
                      [8, 9, 24, 25, 36, 37, 44, 45, 48, 49]]
        for k in range(repeat):
            color_index = {Color(252, 32, 3): [7, 8, 19],
                           Color(252, 136, 3): [5, 6, 17, 18],
                           Color(252, 235, 3): [3, 4, 15, 16],
                           Color(65, 252, 3): [1, 2, 13, 14],
                           Color(3, 90, 252): [0, 11, 12],
                           Color(82, 2, 252): [9, 10]}
            for i in range(10):
                self.frames.append(Frame(hold, {}))
                for color, indicies in color_index.items():
                    for index in indicies:
                        if index >= 0 and index < 9:
                            for light in strips[index]:
                                self.frames[-1].leds[light] = color
                    for j in range(len(indicies)):
                        indicies[j] -= 1

    def spiral(self, color1=Color(255,255,255), color2=Color(255, 0, 0), repeat=1, hold=200):
        strips = [[49],
                  [48, 47],
                  [46, 42, 41],
                  [45, 43, 40, 32],
                  [44, 39, 33, 30, 18, 17],
                  [38, 34, 29, 19, 16, 0],
                  [37, 35, 28, 20, 15, 1],
                  [36, 27, 21, 14, 2],
                  [26, 22, 13, 3],
                  [25, 23, 12, 4],
                  [24, 11, 5],
                  [10, 6],
                  [9, 7],
                  [8]]
        for k in range(repeat):
            color_index = {color1: [0, 1, 2, 3, 8, 9, 10, 11, 16, 17, 18, 19],
                           color2: [4, 5, 6, 7, 12, 13, 14,15, 20, 21, 22, 23]}
            for i in range(7):
                self.frames.append(Frame(hold, {}))
                for color, indicies in color_index.items():
                    for index in indicies:
                        if index >= 0 and index < len(strips):
                            for light in strips[index]:
                                self.frames[-1].leds[light] = color
                    for j in range(len(indicies)):
                        indicies[j] -= 1

    def snow(self, hold=150):
        rows = [[49],
               [48],
               [47, 46, 45],
               [42, 43, 44],
               [41, 40, 39, 38, 37],
               [32, 33, 34, 35, 36],
               [31, 30, 29, 28, 27, 26, 25],
               [18, 19, 20, 21, 22, 23, 24],
               [17, 16, 15, 14, 13, 12, 11, 10,  9],
               [ 0,  1,  2,  3,  4,  5,  6,  7,  8]]
        snow_flakes_row = [[0, 0] for i in range(15)]
        for i in range(60):
            self.frames.append(Frame(hold, {}))
            for flake in snow_flakes_row:
                choice = random.random()
                if choice <= 0.40:
                    if flake[0] % 2:
                        flake[0] += 1
                    if flake[1] == len(rows) - 1:
                        flake[0] = 0
                        flake[1] = 0
                    else:
                        flake[1] += 1
                elif choice <= 0.6:
                    if not flake[0]:
                        flake[0] = 0
                        flake[1] = 0
                    else:
                        flake[0] -= 1
                elif choice <= 0.8:
                    if flake[0] == len(rows[flake[1]]) - 1:
                        flake[0] = 0
                        flake[1] = 0
                    else:
                        flake[0] += 1
                self.frames[-1].leds[rows[flake[1]][flake[0]]] = Color()
        while len(snow_flakes_row):
            self.frames.append(Frame(hold, {}))
            for flake in snow_flakes_row:
                choice = random.random()
                if choice <= 0.40:
                    if flake[0] % 2:
                        flake[0] += 1
                    if flake[1] == len(rows) - 1:
                        snow_flakes_row.remove(flake)
                        continue
                    else:
                        flake[1] += 1
                elif choice <= 0.6:
                    if not flake[0]:
                        snow_flakes_row.remove(flake)
                        continue
                    else:
                        flake[0] -= 1
                elif choice <= 0.8:
                    if flake[0] == len(rows[flake[1]]) - 1:
                        snow_flakes_row.remove(flake)
                        continue
                    else:
                        flake[0] += 1
                self.frames[-1].leds[rows[flake[1]][flake[0]]] = Color()


    def __str__(self):
        ret = "Animation(" + str(self.repeat) + ", ["
        for frame in self.frames:
            ret += str(frame) + ", "
        ret = ret.rstrip(", ")
        ret += "])"
        return ret

    def __eq__(self, animation):
        if len(self.frames) != len(animation.frames) or self.repeat != animation.repeat:
            return False
        for i in range(len(self.frames)):
            if self.frames[i] != animation.frames[i]:
                return False
        return True
