import serial
import threading
import time
class iRobot(object):
	def __init__(self):
		'''
		Establishes connection to the iRobot and creates a thread for data reading
		'''
		# Establish connection
		self.connection = serial.Serial('/dev/ttyUSB0', baudrate=115200)
		# Create a thread to read data
		self.data_thread = threading.Thread(target=self.read_data)
		# Create a thread to register button pressses
		self.button_thread = threading.Thread(taget=self.read_button)
		# Set a status boolean to True
		self.running = True

	def start(self):
		'''
		Starts the iRobot and starts the data reading thread
		'''
		self.connection.write(chr(128))
		self.data_thread.start()

	def reset(self):
		'''
		Resets the iRobot
		'''
		return

	def stop(self):
		'''
		Stops the iRobot
		'''
		self.running = False

	def passive(self):
		'''
		Sets the iRobot into passive mode
		'''
		return

	def safe(self):
		'''
		Sets the iRobot into safe mode
		'''
		return

	def read_data(self):
		'''
    	function that constantly updates the information from the sensors
    	'''
		# Packets: 7, 8, 9, 10, 11, 12, 17, 52, 53
		self.connection.write(chr(148) + chr(9) + chr(7) + chr(8) + chr(9) + chr(10) + chr(11) + chr(12) + chr(17) + chr(52) + chr(53))
		while (self.running):
			self.data = self.connection.read(9)
			
			time.sleep(0.1)

	def read_button(self):
		while(self.running):
			self.button = self.connection.read(1)