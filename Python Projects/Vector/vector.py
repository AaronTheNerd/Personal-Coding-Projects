import math
class Vector(object):
	def __init__(self, arg1, arg2, polar=False, rad=False):
		'''
		Initializes vector using cartesian or polar form.
		Defaults to cartesian.
		Defaults to degree mode if in polar.
		'''
		arg1 = float(arg1)
		arg2 = float(arg2)
		if polar and rad:
			self.mag = arg1
			self.rad = arg2 % (2 * math.pi)
			self.deg = 360.0 * self.rad / (2 * math.pi)
			self.x = self.mag * math.cos(self.rad)
			self.y = self.mag * math.sin(self.rad)
		elif polar:
			self.mag = arg1
			self.deg = arg2 % 360.0
			self.rad = (2 * math.pi) * self.deg / 360.0
			self.x = self.mag * math.cos(self.rad)
			self.y = self.mag * math.sin(self.rad)
		else:
			self.x = arg1
			self.y = arg2
			self.mag = math.sqrt(arg1**2 + arg2**2)
			self.rad = (math.atan(self.y / self.x) if self.x != 0 else math.pi / 2.0 if self.y > 0 else 3.0 * math.pi / 2.0)
			self.deg = 360.0 * self.rad / (2 * math.pi)
	
	def __str__(self):
		'''
		Returns the vector is the form: '<x, y>'
		'''
		return "<" + str(round(self.x, 3)) + ", " + str(round(self.y, 3)) + ">"

	def __add__(self, v):
		'''
		Returns a new vector where its x and y components are the sum of the two vectors x and y components
		'''
		return Vector(self.x + v.x, self.y + v.y)

	def __sub__(self, v):
		return Vector(self.x - v.x, self.y - v.y)

	def __neg__(self):
		return Vector(-self.x, -self.y)

	def __rmul__(self, scalar):
		return Vector(self.x * scalar, self.y * scalar)

	def __mul__(self, arg):
		if isinstance(arg, Vector):
			return self.mag * arg.mag * math.cos(abs(self.rad - arg.rad))
		else:
			return Vector(self.x * arg, self.y * arg)

	def __eq__(self, v):
		return self.x == v.x and self.y == v.y

	@staticmethod
	def are_perpendicular(v1, v2):
		if isinstance(v1, Vector) and isinstance(v2, Vector):
			return round(v1 * v2, 3) == 0.0
		return False

	

def main():
	print (int('0x43', base=16))
	print ((int('0x43', base=16) & 1) == 1)
	print ((int('0x43', base=16) & 2) == 2)
	print ((int('0x43', base=16) & 4) == 4)
	print ((int('0x43', base=16) & 8) == 8)
	i = Vector(0, 1.0)
	j = Vector(1.0, 0)
	print(Vector.are_perpendicular(i, j))

if __name__ == "__main__":
	main()