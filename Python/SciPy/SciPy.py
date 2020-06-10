e = 2.71828
pi = 3.141529
i = complex(0,1)
def exp(x):
  result = e**x
  if type(result) is complex:
    result = complex(round(result.real, 2), round(result.imag, 2))
  else:
    result = round(result, 2)
  print("e ^(" + str(x) + ") = " + str(result))
  return result
exp(pi * i)