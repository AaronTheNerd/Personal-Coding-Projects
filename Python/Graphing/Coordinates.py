# Written by Aaron Barge
# Copyright 2019
import math
class Coord(object):
  def __init__(self):
    return

class Cartesian(Coord):
  def __init__(self, x, y):
    self.x = x
    self.y = y

  def __str__(self):
    return "(x = " + str(self.x) + ", y = " + str(self.y) + ")"

  def __eq__(self, p2):
    self_new = self.round()
    p2_new = self.round()
    if type(p2) is type(self):
      return self_new.x == p2_new.x and self_new.y == p2_new.y
    else:
      p2_new = p2.toCartesian()
      return self_new == p2_new
    print("Something didn't work")
    return False

  def toPolar(self):
    r = math.sqrt(self.x ** 2 + self.y ** 2)
    theta = math.atan(self.y / self.x)
    polar = Polar(r, theta)
    print(polar)
    return polar

  def round(self):
    return Cartesian(round(self.x, 3), round(self.y, 3))



class Polar(Coord):
  def __init__(self, r, theta):
    self.r = r
    self.theta = theta

  def __str__(self):
    return "(r = " + str(self.r) + ", theta = " + str(self.theta) + ")"

  def __eq__(self, p2):
    self_new = self.round()
    p2_new = p2.round()
    if type(p2) is type(self):
      return self_new.r == p2_new.r and self_new.theta == p2_new.theta
    else:
      p2_new = p2.toPolar()
      return self_new == p2_new
    print("Something didn't work")
    return False

  def toCartesian(self):
    cartesian = Cartesian(self.r * math.cos(self.theta), self.r * math.sin(self.theta))
    print(cartesian)
    return cartesian

  def round(self):
    return Polar(round(self.r, 3), round(self.theta, 3))

def Test():
  def checkCartesian():
    def EqualTo():
      p1 = Cartesian(0, 2)
      p2 = Cartesian(0, 2)
      print("Testing Cartesian Equal To")
      return p1 == p2
    def NotEqualTo():
      p1 = Cartesian(0, 2)
      p2 = Cartesian(2, 0)
      print("Testing Cartesian Not Equal To")
      return p1 != p2
    if not EqualTo():
      return False
    if not NotEqualTo():
      return False
    return True
  def checkPolar():
    def EqualTo():
      p1 = Polar(5, 0)
      p2 = Polar(5, 0)
      print("Testing Polar Equal To")
      return p1 == p2
    def NotEqualTo():
      p1 = Polar(5, 0)
      p2 = Polar(5, math.pi)
      print("Testing Polar Not Equal To")
      return p1 != p2
    if not EqualTo():
      return False
    if not NotEqualTo():
      return False
    return True
  def checkBoth():
    def EqualTo():
      p1 = Cartesian(-5, 0)
      p2 = Polar(5, math.pi)
      print("Testing Both Equal To")
      return p1 == p2
    def NotEqualTo():
      p1 = Cartesian(5, 0)
      p2 = Polar(5, math.pi)
      print("Testing Both Not Equal To")
      return p1 != p2
    if not EqualTo():
      return False
    if not NotEqualTo():
      return False
    return True
  if not checkCartesian():
    return False
  if not checkPolar():
    return False
  if not checkBoth():
    return False
  return True

Test()