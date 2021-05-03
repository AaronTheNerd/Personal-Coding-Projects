from triangulation import generate_points, BowyerWatson
import time
import tkinter
import numpy as np

# Constants
WINDOW_WIDTH = 800
WINDOW_HEIGHT = 600
REFRESH_RATE = 1.0 / 30.0
PERIOD = 5
NUM_OF_POINTS = 250
SEPARATION_RADIUS = 20

def draw(canvas, t, points, max_x, max_y):
    triangles = BowyerWatson(points, t, max_x, max_y)
    for triangle in triangles:
        canvas.create_polygon(triangle.a.x, triangle.a.y, triangle.b.x, triangle.b.y, triangle.c.x, triangle.c.y, fill='grey')
        edges = triangle.edges()
        for edge in edges:
            canvas.create_line(edge[0].x, edge[0].y, edge[1].x, edge[1].y, width=2, fill='black')

# The main window of the animation
def create_window():
    window = tkinter.Tk()
    window.title("Tkinter Animation Demo")
    # Uses python 3.6+ string interpolation
    window.geometry(f'{WINDOW_WIDTH}x{WINDOW_HEIGHT}')
    return window
 
# Create a canvas for animation and add it to main window
def create_canvas(window):
    canvas = tkinter.Canvas(window)
    canvas.configure(bg="white")
    canvas.pack(fill="both", expand=True)
    return canvas
        
 
# The actual execution starts here
window = create_window()
canvas = create_canvas(window)
print("Generating points")
points = generate_points(num=NUM_OF_POINTS, max_x=WINDOW_WIDTH, max_y=WINDOW_HEIGHT, separation_radius=SEPARATION_RADIUS)
i = 0
for t in np.linspace(0.0, 1.0, int(PERIOD / REFRESH_RATE), endpoint=False):

    canvas.delete("all")
    draw(canvas, t, points, WINDOW_WIDTH, WINDOW_HEIGHT)
    window.update()
    time.sleep(REFRESH_RATE)
    i += 1
