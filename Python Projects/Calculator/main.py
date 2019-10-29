'''
The goal of this project is to create a fully functional calculator with gui
'''

import tkinter as tk

class Calculator(object):
  def __init__(self, width):
    self.prev_operator = '='
    self.calc = tk.Tk()
    self.width = width
    self.font = ('Courier', 30)
    self.func_font= ('Courier', 20)
    self.curr_input = tk.StringVar()
    self.curr_input.set('0')
    self.curr_function = tk.StringVar()
    self.curr_function.set('')
    self.result = 0
    self.buttons = []
    self.init()
    self.pack()
    self.bind()
    self.calc.mainloop()


  def init(self):
    self.calc.title('Calculator')
    self.buttons.insert(0, [tk.Label(self.calc, textvariable=self.curr_function, width=self.width, font=self.func_font)])
    self.buttons.insert(1, [tk.Label(self.calc, textvariable=self.curr_input, width=self.width, font=self.font)])
    self.buttons.insert(2, [tk.Button(self.calc, text='%', width=self.width//4, height=1, font=self.font),
                            tk.Button(self.calc, text='sqrt', width=self.width//4, height=1, font=self.font),
                            tk.Button(self.calc, text='x^2', width=self.width//4, height=1, font=self.font),
                            tk.Button(self.calc, text='1/x', width=self.width//4, height=1, font=self.font, command=lambda:self.push_function('='))])
    self.buttons.insert(3, [tk.Button(self.calc, text='CE', width=self.width//4, height=1, font=self.font, command=self.clear_input),
                            tk.Button(self.calc, text='C', width=self.width//4, height=1, font=self.font),
                            tk.Button(self.calc, text='DEL', width=self.width//4, height=1, font=self.font, command=self.clear_last),
                            tk.Button(self.calc, text='/', width=self.width//4, height=1, font=self.font, command=lambda:self.push_function('/'))])
    self.buttons.insert(4, [tk.Button(self.calc, text='7', width=self.width//4, height=1, font=self.font, command=lambda:self.push_current(7)),
                            tk.Button(self.calc, text='8', width=self.width//4, height=1, font=self.font, command=lambda:self.push_current(8)),
                            tk.Button(self.calc, text='9', width=self.width//4, height=1, font=self.font, command=lambda:self.push_current(9)),
                            tk.Button(self.calc, text='X', width=self.width//4, height=1, font=self.font, command=lambda:self.push_function('*'))])
    self.buttons.insert(5, [tk.Button(self.calc, text='4', width=self.width//4, height=1, font=self.font, command=lambda:self.push_current(4)),
                            tk.Button(self.calc, text='5', width=self.width//4, height=1, font=self.font, command=lambda:self.push_current(5)),
                            tk.Button(self.calc, text='6', width=self.width//4, height=1, font=self.font, command=lambda:self.push_current(6)),
                            tk.Button(self.calc, text='-', width=self.width//4, height=1, font=self.font, command=lambda:self.push_function('-'))])
    self.buttons.insert(6, [tk.Button(self.calc, text='1', width=self.width//4, height=1, font=self.font, command=lambda:self.push_current(1)),
                            tk.Button(self.calc, text='2', width=self.width//4, height=1, font=self.font, command=lambda:self.push_current(2)),
                            tk.Button(self.calc, text='3', width=self.width//4, height=1, font=self.font, command=lambda:self.push_current(3)),
                            tk.Button(self.calc, text='+', width=self.width//4, height=1, font=self.font, command=lambda:self.push_function('+'))])
    self.buttons.insert(7, [tk.Button(self.calc, text='+/-', width=self.width//4, height=1, font=self.font),
                            tk.Button(self.calc, text='0', width=self.width//4, height=1, font=self.font, command=lambda:self.push_current(0)),
                            tk.Button(self.calc, text='.', width=self.width//4, height=1, font=self.font),
                            tk.Button(self.calc, text='=', width=self.width//4, height=1, font=self.font, command=lambda:self.push_function('='))])


  def bind(self):
    self.calc.focus_set()
    self.calc.bind('7', lambda x:self.push_current(7))
    self.calc.bind('8', lambda x:self.push_current(8))
    self.calc.bind('9', lambda x:self.push_current(9))
    self.calc.bind('4', lambda x:self.push_current(4))
    self.calc.bind('5', lambda x:self.push_current(5))
    self.calc.bind('6', lambda x:self.push_current(6))
    self.calc.bind('1', lambda x:self.push_current(1))
    self.calc.bind('2', lambda x:self.push_current(2))
    self.calc.bind('3', lambda x:self.push_current(3))
    self.calc.bind('0', lambda x:self.push_current(0))
    self.calc.bind('<BackSpace>', lambda x:self.clear_last())
    self.calc.bind('<Return>', lambda x:self.push_function('='))
    self.calc.bind('+', lambda x:self.push_function('+'))
    self.calc.bind('-', lambda x:self.push_function('-'))
    self.calc.bind('*', lambda x:self.push_function('*'))
    self.calc.bind('^', lambda x:self.push_function('^'))
    self.calc.bind('%', lambda x:self.push_function('%'))
    self.calc.bind('/', lambda x:self.push_function('/'))
    self.calc.bind('.', lambda x:self.push_current('.'))



  def pack(self):
    for row in range(len(self.buttons)):
      if row == 0 or row == 1:
        self.buttons[row][0].grid(column=0, row=row, columnspan=self.width)
      else:
        for column in range(len(self.buttons[row])):
          self.buttons[row][column].grid(column=column, row=row)


  def clear_last(self):
    self.curr_input.set(int(float(self.curr_input.get())//10))


  def push_current(self, digit):
    self.curr_input.set(str(int(self.curr_input.get())*10 + int(digit)))


  def clear_input(self):
    self.curr_input.set(0)


  def push_function(self, operator):
    self.curr_function.set(self.curr_function.get() + self.curr_input.get())
    if self.prev_operator == '=':
      self.curr_input.set('0')
      self.curr_function.set(self.result)
    if self.result == 0:
      self.result = self.result + float(self.curr_input.get())
    if operator == '+':
      self.prev_operator = '+'
      self.curr_function.set(self.curr_function.get() + ' + ')
      self.curr_input.set(0)
    if operator == '=':
      if self.prev_operator == '+':
        self.prev_operator = '='
        self.result = self.result + float(self.curr_input.get())
        self.curr_function.set(self.result)
      self.curr_input.set(self.result)


def main():
  '''
  The main method
  '''
  Calculator(32) 


if __name__ == "__main__":
  main()
