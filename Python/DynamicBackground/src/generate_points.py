import math
import random

from point import DriftingPoint, StaticPoint, SwayingPoint
from configs import BORDER_CONFIGS, CONFIGS, DRIFTING_CONFIGS, POINT_CONFIGS

def seed(seed):
    random.seed(seed)

def generate_border_points():
    border_points = []
    num_of_x_border_points = math.floor(CONFIGS["WIDTH"] / BORDER_CONFIGS["SEPARATION"]) + 1
    x_dist = CONFIGS["WIDTH"] / (num_of_x_border_points - 1)
    for i in range(num_of_x_border_points):
        if BORDER_CONFIGS["TOP"]:
            border_points.append(StaticPoint(x_dist * i, 1))
        if BORDER_CONFIGS["BOTTOM"]:
            border_points.append(StaticPoint(x_dist * i, CONFIGS["HEIGHT"] - 1))
    num_of_y_border_points = math.floor(CONFIGS["HEIGHT"] / BORDER_CONFIGS["SEPARATION"]) + 1
    y_dist = CONFIGS["HEIGHT"] / (num_of_y_border_points - 1)
    for i in range(num_of_y_border_points-2):
        if BORDER_CONFIGS["LEFT"]:
            border_points.append(StaticPoint(1, y_dist * (i + 1)))
        if BORDER_CONFIGS["RIGHT"]:
            border_points.append(StaticPoint(CONFIGS["WIDTH"] - 1, y_dist * (i + 1)))
    return border_points

def random_point():
    global open_simplex
    if random.random() < DRIFTING_CONFIGS["PERCENTAGE"]:
        return DriftingPoint(
            random.uniform(0, CONFIGS["WIDTH"]),
            random.uniform(0, CONFIGS["HEIGHT"]),
            None,
            random.randint(DRIFTING_CONFIGS["X_MIN"], DRIFTING_CONFIGS["X_MAX"]),
            random.randint(DRIFTING_CONFIGS["Y_MIN"], DRIFTING_CONFIGS["Y_MAX"]))
    else:
        return SwayingPoint(
            random.uniform(0, CONFIGS["WIDTH"]),
            random.uniform(0, CONFIGS["HEIGHT"]))

def generate_points():
    global open_simplex
    # Generate evenly separated border points
    points = generate_border_points()
    # Find how many points are border points
    border_points_length = len(points)
    # Add one initial interior point
    points.append(random_point())
    # Add points while there is space to
    fails = 0
    while len(points) - border_points_length < POINT_CONFIGS["NUM_OF_POINTS"] and fails < POINT_CONFIGS["MAX_FAILS"]:
        # Create a new point
        new_point = random_point()
        failed = False
        # Check if the point can fit without being too close to other points
        for point in points:
            if (point.x - new_point.x)**2 + (point.y - new_point.y)**2 < POINT_CONFIGS["SEPARATION_RADIUS"]**2:
                fails += 1
                failed = True
                break
        # Add new point to total points if the point is well separated from others
        if not failed:
            points.append(new_point)
            fails = 0
    return points
