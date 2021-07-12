import json
import os
import time

import numpy as np
from PIL import Image, ImageDraw

import generate_points
import point
from configs import CONFIGS, GIF_CONFIGS, LINE_DRAWING_CONFIGS, POINT_DRAWING_CONFIGS
from get_drawing_objects import *
from triangulation import *

# File locations should be changed
# Expected directory structure for gifs
# <ABS_PATH>/<GIF_NUM>/<ALL_IMAGES_AND_JSON_HERE>
ABS_PATH = "/home/aaronthenerd/Documents/Personal-Coding-Projects/Python/DynamicBackground/gifs"

def draw(image, t, points, triangle_coloring, line_coloring, point_coloring):
    triangles = BowyerWatson(points, t)
    for triangle in triangles:
        center = triangle.center()
        triangle_color = triangle_coloring.get_color(triangle)
        image.polygon([triangle.a.x, triangle.a.y, triangle.b.x, triangle.b.y, triangle.c.x, triangle.c.y], fill=(triangle_color[0], triangle_color[1], triangle_color[2]))
        if LINE_DRAWING_CONFIGS["DRAW_LINES"]:
            edges = triangle.edges()
            for edge in edges:
                color = line_coloring.get_color(edge)
                width = line_coloring.get_width(edge)
                image.line([edge[0].x, edge[0].y, edge[1].x, edge[1].y], width=width, fill=(color[0], color[1], color[2]))
    if POINT_DRAWING_CONFIGS["DRAW_POINTS"]:
        for point in points:
            color = point_coloring.get_color(point.x, point.y)
            radius = int(point_coloring.get_width(point.x, point.y) / 2)
            image.ellipse([point.at(t).x - radius, point.at(t).y - radius, point.at(t).x + radius, point.at(t).y + radius], fill=(color[0], color[1], color[2]))

def run():
    # Create directory for files if necessary
    os.system(f"mkdir {ABS_PATH}/{GIF_CONFIGS['NUM']}")
    # Remove any existing files in directory
    os.system(f"rm {ABS_PATH}/{GIF_CONFIGS['NUM']}/*")
    # Generate random seed if necessary
    if CONFIGS["RANDOM_SEED"]:
        CONFIGS["SEED"] = round(time.time())
        CONFIGS["RANDOM_SEED"] = False
    # Seed components
    generate_points.seed(CONFIGS["SEED"])
    point.seed(CONFIGS["SEED"])
    # Generate objects needed to color the gif
    triangle_coloring = get_triangle_coloring_object()
    line_coloring = get_line_drawing_object()
    point_coloring = get_point_drawing_object()
    # Generate initial points
    points = generate_points.generate_points()
    # Generate frames
    i = 0
    for t in np.linspace(0.0, 1.0, CONFIGS["NUM_OF_FRAMES"], endpoint=False):
        image = Image.new("RGB", (CONFIGS["WIDTH"], CONFIGS["HEIGHT"]), 
                (CONFIGS["BACKGROUND_COLOR"][0], CONFIGS["BACKGROUND_COLOR"][1], CONFIGS["BACKGROUND_COLOR"][2]))
        image_draw = ImageDraw.Draw(image)
        draw(image_draw, t, points, triangle_coloring, line_coloring, point_coloring)
        file_name = f"{ABS_PATH}/{GIF_CONFIGS['NUM']}/image#{str(i).zfill(3)}.bmp"
        image.save(file_name)
        i += 1
    # Convert frames to gif
    os.system(f"convert -delay {GIF_CONFIGS['MS_PER_FRAME']} -loop 0 {ABS_PATH}/{GIF_CONFIGS['NUM']}/*.bmp -crop {CONFIGS['WIDTH'] - 2 * GIF_CONFIGS['MARGIN']}x{CONFIGS['HEIGHT'] - 2 * GIF_CONFIGS['MARGIN']}+{GIF_CONFIGS['MARGIN']}+{GIF_CONFIGS['MARGIN']} +repage {ABS_PATH}/{GIF_CONFIGS['NUM']}/gif{GIF_CONFIGS['NUM']}.gif")
    # Remove frames
    os.system(f"rm {ABS_PATH}/{GIF_CONFIGS['NUM']}/*.bmp")
    # Create copy of configs to be able to remake the gif
    with open(f"{ABS_PATH}/{GIF_CONFIGS['NUM']}/config.json", 'w+') as file:
        json.dump(CONFIGS, file, indent=4)

if __name__ == "__main__":
    run()
