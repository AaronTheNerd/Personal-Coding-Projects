from color_space import *
from triangulation import *
import numpy as np
from PIL import Image, ImageDraw
import json

# Constants
WINDOW_WIDTH = 1360
WINDOW_HEIGHT = 768
NUM_OF_FRAMES = 200
AMPLITUDE = 1000000
INTENSITY = 0.00005
NUM_OF_POINTS = 250
SEPARATION_RADIUS = 50
MAX_FAILS = 10000
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
START_COLOR = (103, 235, 52)
END_COLOR = (52, 155, 235)
START_POINT = (0, 0)
END_POINT = (WINDOW_WIDTH, WINDOW_HEIGHT)
ALPHA = -1.8

# File locations should be changed
# Expected directory structure for gifs
# <ABS_PATH>/<GIF_NUM>/<ALL_IMAGES_AND_JSON_HERE>
ABS_PATH = "/home/aaronthenerd/Documents/Personal-Coding-Projects/Python/DynamicBackground/gifs"
GIF_NUM = 1
JSON_ABS_PATH = f"{ABS_PATH}/{GIF_NUM}/info.json"

def draw(image, t, points, gradient):
    triangles = BowyerWatson(points, t)
    for triangle in triangles:
        center = triangle.center()
        image.polygon([triangle.a.x, triangle.a.y, triangle.b.x, triangle.b.y, triangle.c.x, triangle.c.y], fill=gradient.get_color(center[0], center[1]))
        edges = triangle.edges()
        for edge in edges:
            image.line([edge[0].x, edge[0].y, edge[1].x, edge[1].y], width=3, fill=WHITE)

def encode_json(gradient):
    info = {
        "type": "GIF",
        "triangulation_info": get_info(),
        "color_space": gradient.__dict__(),
        'num_of_frames': NUM_OF_FRAMES,
    }
    info_file = open(f"{ABS_PATH}/{GIF_NUM}/info.json", 'w+')
    json.dump(info, info_file, indent=4)

def run_with_json():
    global NUM_OF_FRAMES
    info_file = open(JSON_ABS_PATH, 'r')
    info = json.load(info_file)
    if info['type'] != 'GIF':
        print(f"Incorrect type attribute {info['type']} expected GIF")
        return
    triangulation_info = info['triangulation_info']
    triangulation_init(
        seed=triangulation_info['seed'],
        max_x=triangulation_info['max_x'],
        max_y=triangulation_info['max_y'],
        amplitude=triangulation_info['amplitude'],
        intensity=triangulation_info['intensity'],
        scale=triangulation_info['scale'],
        offset_x=triangulation_info['offset_x'])
    color_space_info = info['color_space']
    gradient = None
    if color_space_info['type'] == 'HSVLinearGradientContinuous':
        gradient = HSVLinearGradientContinuous(
            start_x=color_space_info['start_x'],
            start_y=color_space_info['start_y'],
            end_x=color_space_info['end_x'],
            end_y=color_space_info['end_y'],
            start_color=color_space_info['start_color'],
            end_color=color_space_info['end_color']
        )
    elif color_space_info['type'] == 'HSVLinearGradientDiscrete':
        gradient = HSVLinearGradientDiscrete(
            start_x=color_space_info['start_x'],
            start_y=color_space_info['start_y'],
            end_x=color_space_info['end_x'],
            end_y=color_space_info['end_y'],
            start_color=color_space_info['start_color'],
            end_color=color_space_info['end_color'],
            num_of_colors=color_space_info['num_of_colors']
        )
    elif color_space_info['type'] == 'HSVExponentialGradientContinuous':
        gradient = HSVExponentialGradientContinuous(
            start_x=color_space_info['start_x'],
            start_y=color_space_info['start_y'],
            end_x=color_space_info['end_x'],
            end_y=color_space_info['end_y'],
            start_color=color_space_info['start_color'],
            end_color=color_space_info['end_color'],
            alpha=color_space_info['alpha']
        )
    else:
        f"Incorrect color space type attribute {color_space_info['type']}"
        return
    points = generate_points(
        num=triangulation_info['num_of_points'],
        separation_radius=triangulation_info['separation_radius'],
        max_fails=triangulation_info['max_fails'])
    i = 0
    NUM_OF_FRAMES = info['num_of_frames']
    for t in np.linspace(0.0, 1.0, NUM_OF_FRAMES, endpoint=False):
        image = Image.new("RGB", (triangulation_info['max_x'], triangulation_info['max_y']), WHITE)
        image_draw = ImageDraw.Draw(image)
        draw(image_draw, t, points, gradient)
        file_name = f"{ABS_PATH}/{GIF_NUM}/image#{str(i).zfill(3)}.bmp"
        image.save(file_name)
        i += 1
    encode_json(gradient)

def run():
    triangulation_init(amplitude=AMPLITUDE, intensity=INTENSITY, max_x=WINDOW_WIDTH, max_y=WINDOW_HEIGHT)
    gradient = HSVExponentialGradientContinuous(START_POINT[0], START_POINT[1], END_POINT[0], END_POINT[1], START_COLOR, END_COLOR, ALPHA)
    points = generate_points(num=NUM_OF_POINTS, separation_radius=SEPARATION_RADIUS, max_fails=MAX_FAILS)
    i = 0
    for t in np.linspace(0.0, 1.0, NUM_OF_FRAMES, endpoint=False):
        image = Image.new("RGB", (WINDOW_WIDTH, WINDOW_HEIGHT), WHITE)
        image_draw = ImageDraw.Draw(image)
        draw(image_draw, t, points, gradient)
        file_name = f"{ABS_PATH}/{GIF_NUM}/image#{str(i).zfill(3)}.bmp"
        image.save(file_name)
        i += 1
    encode_json(gradient)

if __name__ == "__main__":
    run()
