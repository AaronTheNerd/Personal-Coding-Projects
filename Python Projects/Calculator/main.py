'''
The goal of this project is to create a fully functional calculator with gui
'''
import tkinter


class Calculator(object):
  def __init__(self, width):
    self.calc = tkinter.Tk()
    self.width = width
    self.font = ('Courier', 30)
    self.func_font= ('Courier', 20)
    self.curr_input = tkinter.StringVar()
    self.curr_input.set('0')
    self.curr_function = tkinter.StringVar()
    self.curr_function.set('')
    self.result = 0
    self.buttons = []
    self.init()
    self.pack()
    self.calc.mainloop()
  def init(self):
    self.calc.title('Calculator')
    self.buttons.insert(0, [tkinter.Message(self.calc, textvariable=self.curr_function, width=self.width, font=self.func_font)])
    self.buttons.insert(1, [tkinter.Message(self.calc, textvariable=self.curr_input, width=self.width, font=self.font)])
    self.buttons.insert(2, [tkinter.Button(self.calc, text='%', width=self.width//4, height=1, font=self.font),
                            tkinter.Button(self.calc, text='sqrt', width=self.width//4, height=1, font=self.font),
                            tkinter.Button(self.calc, text='x^2', width=self.width//4, height=1, font=self.font),
                            tkinter.Button(self.calc, text='1/x', width=self.width//4, height=1, font=self.font, command=lambda:self.push_function('='))])
    self.buttons.insert(3, [tkinter.Button(self.calc, text='CE', width=self.width//4, height=1, font=self.font),
                            tkinter.Button(self.calc, text='C', width=self.width//4, height=1, font=self.font),
                            tkinter.Button(self.calc, text='DEL', width=self.width//4, height=1, font=self.font),
                            tkinter.Button(self.calc, text='/', width=self.width//4, height=1, font=self.font, command=lambda:self.push_function('/'))])
    self.buttons.insert(4, [tkinter.Button(self.calc, text='7', width=self.width//4, height=1, font=self.font, command=lambda:self.push_current(7)),
                            tkinter.Button(self.calc, text='8', width=self.width//4, height=1, font=self.font, command=lambda:self.push_current(8)),
                            tkinter.Button(self.calc, text='9', width=self.width//4, height=1, font=self.font, command=lambda:self.push_current(9)),
                            tkinter.Button(self.calc, text='X', width=self.width//4, height=1, font=self.font, command=lambda:self.push_function('*'))])
    self.buttons.insert(5, [tkinter.Button(self.calc, text='4', width=self.width//4, height=1, font=self.font, command=lambda:self.push_current(4)),
                            tkinter.Button(self.calc, text='5', width=self.width//4, height=1, font=self.font, command=lambda:self.push_current(5)),
                            tkinter.Button(self.calc, text='6', width=self.width//4, height=1, font=self.font, command=lambda:self.push_current(6)),
                            tkinter.Button(self.calc, text='-', width=self.width//4, height=1, font=self.font, command=lambda:self.push_function('-'))])
    self.buttons.insert(6, [tkinter.Button(self.calc, text='1', width=self.width//4, height=1, font=self.font, command=lambda:self.push_current(1)),
                            tkinter.Button(self.calc, text='2', width=self.width//4, height=1, font=self.font, command=lambda:self.push_current(2)),
                            tkinter.Button(self.calc, text='3', width=self.width//4, height=1, font=self.font, command=lambda:self.push_current(3)),
                            tkinter.Button(self.calc, text='+', width=self.width//4, height=1, font=self.font, command=lambda:self.push_function('+'))])
    self.buttons.insert(7, [tkinter.Button(self.calc, text='+/-', width=self.width//4, height=1, font=self.font),
                            tkinter.Button(self.calc, text='0', width=self.width//4, height=1, font=self.font, command=lambda:self.push_current(0)),
                            tkinter.Button(self.calc, text='.', width=self.width//4, height=1, font=self.font),
                            tkinter.Button(self.calc, text='=', width=self.width//4, height=1, font=self.font, command=lambda:self.push_function('='))])
  def pack(self):
    for row in range(len(self.buttons)):
      if row == 0 or row == 1:
        self.buttons[row][0].grid(column=0, row=row, columnspan=self.width)
      else:
        for column in range(len(self.buttons[row])):
          self.buttons[row][column].grid(column=column, row=row)
  def push_current(self, digit):
    self.curr_input.set(str(float(self.curr_input.get())*10 + int(digit)))
  def push_function(self, operator):
    if operator == '+':
      self.result = self.result + float(self.curr_input.get())
      self.curr_function.set(self.curr_function.get() + '+' + self.curr_input.get())
    self.curr_input.set(0)



def main():
  '''
  The main method
  '''
  calculator = Calculator(16) 

if __name__ == "__main__":
  main()
