import tkinter
import math
import random
import sys

# Window dimensions
window_width=1360
window_height=768

# Constants
max_depth = 10
min_width = 2
min_length = 5
leaf_threshold = max_depth / 2.2
trunk_width = 40
trunk_height = window_height / 5
trunk_angle = math.pi * 1 / 2

# Only used for random rule generation
num_of_rules = 10
seed = random.randint(-sys.maxsize - 1, sys.maxsize)

class BranchRule(object):
    def __init__(self, length_mult=0.9, width_mult=0.9, angle_change=math.pi/5):
        self.length_mult = length_mult
        self.width_mult = width_mult
        self.angle_change = angle_change

def random_rules(num_of_rules, seed):
    rules = []
    random.seed(seed)
    for _ in range(num_of_rules):
        rules.append(BranchRule(
            random.uniform(0.5, 0.9),
            random.uniform(0.5, 0.9),
            random.uniform(-math.pi / 4 , math.pi / 4)))
    return rules

rules = random_rules(num_of_rules, seed)

'''
rules = [
    BranchRule(length_mult=0.5, width_mult=0.6, angle_change=math.pi / 5),
    BranchRule(length_mult=0.7, width_mult=0.75, angle_change=-math.pi / 15),
    BranchRule(length_mult=0.9, width_mult=0.6, angle_change=math.pi / 10),
    BranchRule(length_mult=0.9, width_mult=0.5, angle_change=-math.pi / 10)
]
'''
'''
rules = [
    BranchRule(0.8, 0.9, 0),
    BranchRule(0.6, 0.6, -math.pi / 5),
    BranchRule(0.6, 0.6, math.pi / 5)
]
'''

def draw(window, canvas, depth, pos_x, pos_y, length, width, angle):
    new_pos_x = pos_x + length * math.cos(angle)
    new_pos_y = pos_y + length * math.sin(angle)
    color = 'dark green' if depth > leaf_threshold else 'saddle brown'
    canvas.create_line(pos_x, pos_y, new_pos_x, new_pos_y, width=width, fill=color)
    if depth >= max_depth or length < min_length or width < min_width:
        return
    else:
        for rule in rules:
            draw(window, canvas, depth + 1,
                 new_pos_x, new_pos_y,
                 length * rule.length_mult,
                 width * rule.width_mult,
                 angle + rule.angle_change)
        window.update()

# The main window of the animation
def create_window():
    window = tkinter.Tk()
    window.title("Tkinter Animation Demo")
    # Uses python 3.6+ string interpolation
    window.geometry(f'{window_width}x{window_height}')
    return window
 
# Create a canvas for animation and add it to main window
def create_canvas(window):
    canvas = tkinter.Canvas(window)
    canvas.configure(bg="deep sky blue")
    canvas.pack(fill="both", expand=True)
    return canvas
        
 
# The actual execution starts here
window = create_window()
canvas = create_canvas(window)
print(f"Seed: {seed}")
print(f"Num of Rules: {num_of_rules}")

draw(window, canvas, 0, window_width / 2, window_height, trunk_height, trunk_width, -trunk_angle)
while(True): pass