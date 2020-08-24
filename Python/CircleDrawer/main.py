import pyautogui
import numpy
import math
import time

time.sleep(5)
width, height = pyautogui.size()
origin_x, origin_y = width / 2, 432
radius = 300
pyautogui.moveTo(origin_x, origin_y + radius)
for deg in numpy.arange(0, 2 * math.pi, 0.0001):
    pyautogui.dragTo(origin_x + radius * math.sin(deg), origin_y + radius * math.cos(deg), duration=0.01)
