###############################################################################
# Copyright 2021                                                              #
# Written by Aaron Barge                                                      #
# Idea from: https://necessarydisorder.wordpress.com/2017/11/15/drawing-from-noise-and-then-making-animated-loopy-gifs-from-there/
###############################################################################

################################### Imports ###################################
from opensimplex import OpenSimplex
import math
import random
import time

############################## Global Variables ###############################
open_simplex = OpenSimplex()
SEED = 0
MAX_X = 0
MAX_Y = 0
AMPLITUDE = 0
INTENSITY = 0.0
SCALE = 0
OFFSET_X = 0
NUM_OF_POINTS = 0
SEPARATION_RADIUS = 0
MAX_FAILS = 0

############################### Helper Classes ################################
class StaticPoint(object):
    def __init__(self, x=0.0, y=0.0):
        self.x = x
        self.y = y
    def __repr__(self):
        return str(self)
    def __str__(self):
        return f"({round(self.x, 2)}, {round(self.y, 2)})"
    def __eq__(self, p):
        return (self.x == p.x and self.y == p.y) or (self is p)
    def at(self, t):
        return Point(self.x, self.y)

class Point(StaticPoint):
    def __init__(self, x=0.0, y=0.0):
        super().__init__(x, y)
    def __repr__(self):
        return str(self)
    def __str__(self):
        return super().__str__(self)
    def __eq__(self, p):
        return super().__eq__(p)
    def at(self, t):
        global open_simplex, MAX_X, MAX_Y
        new_x = self.x + AMPLITUDE * open_simplex.noise4d(
                x=self.x * SCALE,
                y=self.y * SCALE,
                z=INTENSITY * math.cos(2 * math.pi * t),
                w=INTENSITY * math.sin(2 * math.pi * t))
        new_y = self.y + AMPLITUDE * open_simplex.noise4d(
                x=self.x * SCALE + OFFSET_X,
                y=self.y * SCALE,
                z=INTENSITY * math.cos(2 * math.pi * t),
                w=INTENSITY * math.sin(2 * math.pi * t))
        if new_x < 0.0 or new_x > MAX_X:
            new_x = float((int(new_x) + MAX_X) % MAX_X)
        if new_y < 0.0 or new_y > MAX_Y:
            new_y = float((int(new_y) + MAX_Y) % MAX_Y)
        return Point(new_x, new_y)

class Triangle(object):
    def __init__(self, a, b, c):
        self.a = a
        self.b = b
        self.c = c
    def __eq__(self, t):
        return (self is t) or (self.a == t.a and self.b == t.b and self.c == t.c)
    def __ne__(self, t):
        return not self == t
    def __repr__(self):
        return str(self)
    def __str__(self):
        return f"Triangle({self.a}, {self.b}, {self.c})"
    def edges(self):
        return [[self.a, self.b], [self.a, self.c], [self.b, self.c]]
    def has_point(self, p):
        return (self.a == p) or (self.b is p) or (self.b == p) or (self.c is p) or (self.c == p) or (self.a is p)
    def center(self):
        return ((self.a.x + self.b.x + self.c.x) / 3, (self.a.y + self.b.y + self.c.y) / 3)

################################### Methods ###################################
def triangulation_init(seed=int(time.time()), max_x=400, max_y=400, amplitude=1000, intensity=0.001, scale=10, offset_x=100):
    global SEED, MAX_X, MAX_Y, AMPLITUDE, INTENSITY, SCALE, OFFSET_X
    MAX_X = max_x
    MAX_Y = max_y
    SEED = seed
    AMPLITUDE = amplitude
    INTENSITY = intensity
    SCALE = scale
    OFFSET_X = offset_x

def generate_points(num=50, separation_radius=10, max_fails=100):
    global open_simplex, SEED, MAX_X, MAX_Y, NUM_OF_POINTS, SEPARATION_RADIUS, MAX_FAILS
    NUM_OF_POINTS = num
    SEPARATION_RADIUS = separation_radius
    MAX_FAILS = max_fails
    points = []
    num_of_x_border_points = math.floor(MAX_X / separation_radius) + 1
    x_dist = MAX_X / (num_of_x_border_points - 1)
    for i in range(num_of_x_border_points):
        points.append(StaticPoint(x_dist * i, 1))
        points.append(StaticPoint(x_dist * i, MAX_Y - 1))
    num_of_y_border_points = math.floor(MAX_Y / separation_radius) + 1
    y_dist = MAX_Y / (num_of_y_border_points - 1)
    for i in range(num_of_y_border_points-2):
        points.append(StaticPoint(1, y_dist * (i + 1)))
        points.append(StaticPoint(MAX_X - 1, y_dist * (i + 1)))
    open_simplex = OpenSimplex(seed=SEED)
    random.seed(SEED)
    points.append(Point(random.uniform(0, MAX_X), random.uniform(0, MAX_Y)))
    fails = 0
    while len(points) < num and fails < max_fails:
        x = random.uniform(0, MAX_X)
        y = random.uniform(0, MAX_Y)
        failed = False
        for point in points:
            if (point.x - x)**2 + (point.y - y)**2 < separation_radius**2:
                fails += 1
                failed = True
                break
        if not failed:
            points.append(Point(x, y))
            fails = 0
    return points

def get_info():
    return {
        "seed": SEED,
        "max_x": MAX_X,
        "max_y": MAX_Y,
        "amplitude": AMPLITUDE,
        "intensity": INTENSITY,
        "scale": SCALE,
        "offset_x": OFFSET_X,
        "num_of_points": NUM_OF_POINTS,
        "separation_radius": SEPARATION_RADIUS,
        "max_fails": MAX_FAILS
    }

########################## Start GeeksForGeeks Code ###########################
# https://www.geeksforgeeks.org/find-if-a-point-lies-inside-outside-or-on-the-circumcircle-of-three-points-a-b-c/
# Python3 program to find the points which lies inside, outside or on the     #
# circle                                                                      #
###############################################################################
 
# Function to find the line given
# two points
def lineFromPoints(P, Q, a, b, c):
    a = Q.y - P.y
    b = P.x - Q.x
    c = a * (P.x) + b * (P.y)
    return a, b, c
 
# Function which converts the
# input line to its perpendicular
# bisector. It also inputs the
# points whose mid-lies o
# on the bisector
def perpenBisectorFromLine(P, Q, a, b, c):
    # Find the mid point
    mid_point = Point(0, 0)
    # x coordinates
    mid_point.x = (P.x + Q.x) / 2
    # y coordinates
    mid_point.y = (P.y + Q.y) / 2
    # c = -bx + ay
    c = (-b * (mid_point.x) +
          a * (mid_point.y))
    # Assign the coefficient of
    # a and b
    a, b = -b, a
    return a, b, c
 
# Returns the intersection of
# two lines
def LineInterX(a1, b1, c1, a2, b2, c2):
    # Find determinant
    determ = a1 * b2 - a2 * b1
    x = (b2 * c1 - b1 * c2)
    try:
        x /= determ
    except ZeroDivisionError:
        x = math.inf
    return x
 
# Returns the intersection of
# two lines
def LineInterY(a1, b1, c1, a2, b2, c2):
    # Find determinant
    determ = a1 * b2 - a2 * b1
    y = (a1 * c2 - a2 * c1)
    try:
        y /= determ
    except ZeroDivisionError:
        y = math.inf
    return y
 
# Function to find the point
# lies inside, outside or on
# the circle
def isInside(T, D):
    P = T.a
    Q = T.b
    R = T.c
    # Store the coordinates
    # radius of circumcircle
    r = Point(0, 0)
    # Line PQ is represented
    # as ax + by = c
    a, b, c = lineFromPoints(P, Q, 0, 0, 0)
    # Line QR is represented
    # as ex + fy = g
    e, f, g = lineFromPoints(Q, R, 0, 0, 0)
    # Converting lines PQ and QR
    # to perpendicular bisectors.
    # After this, L = ax + by = c
    # M = ex + fy = g
    a, b, c = perpenBisectorFromLine(P, Q, a, b, c)
    e, f, g = perpenBisectorFromLine(Q, R, e, f, g)
    # The of intersection
    # of L and M gives r as the
    # circumcenter
    r.x = LineInterX(a, b, c, e, f, g)
    if r.x == math.inf:
        return True
    r.y = LineInterY(a, b, c, e, f, g)
    if r.y == math.inf:
        return True
    # Length of radius
    q = ((r.x - P.x)**2 + (r.y - P.y)**2)
    # Distance between radius
    # and the given D
    dis = ((r.x - D.x)**2 + (r.y - D.y)**2)
    # Condition for lies
    # inside circumcircle
    if (dis <= q): # In circumcircle
        return True
    else: # Outside or on circumcircle
        return False
########################### End GeeksForGeeks Code ############################

############################# Start Triangulation #############################
# https://en.wikipedia.org/wiki/Bowyer%E2%80%93Watson_algorithm#/media/File:Bowyer-Watson_6.png
# Super Triangle Math                                                         #
# Point b: (-max_x / 2, max_y)                                                #
# Point c: (3 * max_x / 2, max_y)                                             #
# Solving for point a                                                         #
#    Set point a.x to the center of canvas = max_x / 2                        #
#    Find angle of left angle of super triangle                               #
#        theta = atan(max_y / (max_x / 2)) = atan(2 * max_y / max_x)          #
#    Find distance from bottom of canvas (max_y) to the point a.y             #
#        tan(theta) = dist / max_x => dist = max_x * tan(theta)               #
#    Solve for a.y                                                            #
#    a.y = max_y - dist                                                       #
#        = max_y - max_x * tan(theta)                                         #
#        = max_y - max_x * tan(atan(2 * max_y / max_x))                       #
#        = max_y - max_x * 2 * max_y / max_x                                  #
#        = max_y - 2 * max_y                                                  #
#        = -max_y                                                             #
#    Point a: (max_x / 2, -max_y)                                             #
###############################################################################
def BowyerWatson(points, t):
    global MAX_X, MAX_Y
    super_a = Point(MAX_X / 2, -MAX_Y)
    super_b = Point(-MAX_X / 2, MAX_Y)
    super_c = Point(3 * MAX_X / 2, MAX_Y)

    triangles = [Triangle(super_a, super_b, super_c)] # Super Triangle
    for point in points:
        curr_point = point.at(t)
        bad_triangles = [triangle for triangle in triangles if isInside(triangle, curr_point)]
        polygon = []
        for triangle in bad_triangles:
            edges = triangle.edges()
            for edge in edges:
                shared = False
                for triangle2 in bad_triangles:
                    if triangle != triangle2:
                        edges2 = triangle2.edges()
                        for edge2 in edges2:
                            if edge[0] == edge2[0] and edge[1] == edge2[1]:
                                shared = True
                                break
                    if shared:
                        break
                if not shared:
                    polygon.append(edge)
        for bad_triangle in bad_triangles:
            triangles = [triangle for triangle in triangles if triangle != bad_triangle]
        for edge in polygon:
            triangles.append(Triangle(edge[0], edge[1], curr_point))
    for triangle in triangles:
        triangles = [triangle2 for triangle2 in triangles if not (triangle2.has_point(super_a) or triangle2.has_point(super_b) or triangle2.has_point(super_c))]
    return triangles
############################## End Triangulation ##############################

if __name__ == "__main__":
    triangulation_init()
    points = generate_points()
    print(points)

    triangles = BowyerWatson(points, 0.0)
    print(triangles)
