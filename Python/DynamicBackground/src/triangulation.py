###############################################################################
# Copyright 2021                                                              #
# Written by Aaron Barge                                                      #
# Idea from: https://necessarydisorder.wordpress.com/2017/11/15/drawing-from-noise-and-then-making-animated-loopy-gifs-from-there/
###############################################################################

################################### Imports ###################################
import math

from configs import CONFIGS, WIDTH, HEIGHT
from point import StaticPoint

############################### Helper Classes ################################
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
        return ((self.a.x + self.b.x + self.c.x) / 3, (self.a.y + self.b.y + self.c.y) / 3, (self.a.z + self.b.z + self.c.z) / 3)

################################### Methods ###################################


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
    mid_point = StaticPoint(0, 0)
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
    r = StaticPoint(0, 0)
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
# Point b: (-WIDTH / 2, HEIGHT)                                               #
# Point c: (3 * WIDTH / 2, HEIGHT)                                            #
# Solving for point a                                                         #
#    Set point a.x to the center of canvas = WIDTH / 2                        #
#    Find angle of left angle of super triangle                               #
#        theta = atan(HEIGHT / (WIDTH / 2))                                   #
#              = atan(2 * HEIGHT / WIDTH)                                     #
#    Find distance from bottom of canvas (HEIGHT) to the point a.y            #
#        tan(theta) = dist / WIDTH =>                                         #
#              dist = WIDTH * tan(theta)                                      #
#    Solve for a.y                                                            #
#    a.y = HEIGHT - dist                                                      #
#        = HEIGHT - WIDTH * tan(theta)                                        #
#        = HEIGHT - WIDTH                                                     #
#             * tan(atan(2 * HEIGHT / WIDTH))                                 #
#        = HEIGHT - WIDTH * 2                                                 #
#             * HEIGHT / WIDTH                                                #
#        = HEIGHT - 2 * HEIGHT                                                #
#        = -HEIGHT                                                            #
#    Point a: (WIDTH / 2, -HEIGHT)                                            #
###############################################################################
def BowyerWatson(points, t):
    super_a = StaticPoint(WIDTH / 2, -HEIGHT)
    super_b = StaticPoint(-WIDTH / 2, HEIGHT)
    super_c = StaticPoint(3 * WIDTH / 2, HEIGHT)
    triangles = [Triangle(super_a, super_b, super_c)]
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
