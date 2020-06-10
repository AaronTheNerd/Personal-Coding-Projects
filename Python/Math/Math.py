# Written by Aaron Barge
# Copyright 2019
import math
def f(x):
  return (x**2) - (2 * x)
def g(x):
  return (3 * x**3) + (5 * x)
def h(x):
  return 1 / (5 - x)
def graph(x0, x1, num_of_entries):
  if x1 < x0:
    return
  detail = -(int(math.log10((x1 - x0)/num_of_entries)) - 1)
  for increment in range(num_of_entries):
    x = (increment / num_of_entries) * (x1 - x0) + x0
    try:
      print("y = h(" + str(round(x, detail)) + ") = " + str(round(h(x), detail)))
    except:
      print("y = h(" + str(round(x, detail)) + ") = undefined")

graph(4.9999999999, 5.0000000001, 100)