'''
Written by Aaron Barge
Copyright 2020

Goal: Creating a fully Functional scientific calculator
I will be doing this mainly using TKinter.
Additionally, the GUI should accept both keypresses as well as mouse clicks
I will be basing mine off of the Google Scientific Calculator:
+-----------------------------------------------------------------------------+
|                                                                             |
+----------+----------+----------+----------+-----------+----------+----------+
|   Rad    |    Deg   |    x!    |     (    |     )     |     %    |    CE    |
+----------+----------+----------+----------+-----------+----------+----------+
|   Inv    |    sin   |    ln    |     7    |     8     |     9    |     /    |
+----------+----------+----------+----------+-----------+----------+----------+
|    pi    |    cos   |    log   |     4    |     5     |     6    |     X    |
+----------+----------+----------+----------+-----------+----------+----------+
|    e     |    tan   |   sqrt   |     1    |     2     |     3    |     -    |
+----------+----------+----------+----------+-----------+----------+----------+
|   Ans?   |    EXP   |    x^y   |     0    |     .     |     =    |     +    |
+----------+----------+----------+----------+-----------+----------+----------+
I am tempted to not implement the Ans Function. In my opinion it does not seem
like a worthwhile addition.

The Rad and Deg tags are a combined button where you can switch between radians
and Degree mode

The Inv button inverts most of the Function buttons i.e. sine to arcsine
'''

import tkinter as tk
from tkinter import ttk
import matplotlib
#import matplotlib.pyplot as plt

from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
matplotlib.use('TkAgg')

class Func:
    """
    Defines a function where the first string is the label for the button and
    the second string is the equation
    """
    def __init__(self, label, tex):
        self.label = label
        self.tex = tex

class VarText(tk.StringVar):
    """
    Wrapper class for tk.StringVar
    """
    def __init__(self, master, func1, func2):
        tk.StringVar.__init__(self, master=master)
        tk.StringVar.set(self, value=func1.label)
        self.func1 = func1
        self.func2 = func2
    def invert(self, inverted):
        """
        Inverts a function
        """
        if inverted:
            tk.StringVar.set(self, value=self.func2.label)
        else:
            tk.StringVar.set(self, value=self.func1.label)
    def get_func(self):
        """
        Grabs current function
        """
        curr_label = tk.StringVar.get(self)
        if curr_label == self.func1.label:
            return self.func1.tex
        return self.func2.tex

class CalcButton(ttk.Button):
    """
    Wrapper class for ttk.Button
    """
    def __init__(self, t="", vt=None, c=0, r=0, cs=1, cmd=None):
        if vt is not None:
            ttk.Button.__init__(self, textvariable=vt, command=cmd)
            self.var_text = vt
        else:
            ttk.Button.__init__(self, text=t, command=cmd)
        ttk.Button.grid(self, column=c, row=r, columnspan=cs, sticky=tk.W+tk.E+tk.N+tk.S)
    def invert_label(self, inverted):
        """
        Inverts the label on the button
        """
        self.var_text.invert(inverted)
    def get_func(self):
        """
        Grabs the current label from button
        """
        return self.var_text.get_func()

class Calculator(tk.Frame):
    """
    Class for defining a Calculator
    """
    def __init__(self, master=None):
        tk.Frame.__init__(self, master)
        self.master = master
        self.display_text = tk.StringVar()
        self.inverted = False
        self.radians = True
        self.figure_container = None
        self.figure = None
        self.canvas = None
        self.display = None
        self.factorial_cmd = None
        self.open_paren_cmd = None
        self.close_paren_cmd = None
        self.sine_cmd = None
        self.nat_log_cmd = None
        self.zero_cmd = None
        self.one_cmd = None
        self.two_cmd = None
        self.three_cmd = None
        self.four_cmd = None
        self.five_cmd = None
        self.six_cmd = None
        self.seven_cmd = None
        self.eight_cmd = None
        self.nine_cmd = None
        self.divide_cmd = None
        self.cosine_cmd = None
        self.log_cmd = None
        self.times_cmd = None
        self.tangent_cmd = None
        self.sqrt_cmd = None
        self.minus_cmd = None
        self.exp_cmd = None
        self.dot_cmd = None
        self.plus_cmd = None
        self.equal_cmd = None
        self.clear_cmd = None
        self.percent_cmd = None
        self.space_cmd = None
        self.mode = None
        self.factorial = None
        self.open_paren = None
        self.close_paren = None
        self.percent = None
        self.clear = None
        self.invert = None
        self.sine = None
        self.nat_log = None
        self.seven = None
        self.eight = None
        self.nine = None
        self.divide = None
        self.pi_num = None
        self.cosine = None
        self.log = None
        self.four = None
        self.five = None
        self.six = None
        self.times = None
        self.e_num = None
        self.tangent = None
        self.sqrt = None
        self.one = None
        self.two = None
        self.three = None
        self.minus = None
        self.exp = None
        self.pow = None
        self.zero = None
        self.dot = None
        self.equals = None
        self.plus = None
        self.init_window()

    def invert_func(self):
        """
        Inverts all functions
        """
        self.inverted = not self.inverted
        self.sine.invert_label(self.inverted)
        self.nat_log.invert_label(self.inverted)
        self.cosine.invert_label(self.inverted)
        self.log.invert_label(self.inverted)
        self.tangent.invert_label(self.inverted)
        self.sqrt.invert_label(self.inverted)
        self.pow.invert_label(self.inverted)

    def toggle_mode(self):
        """
        Switches the mode from radians to degrees
        """
        self.radians = not self.radians

    def update_canvas(self):
        """
        Updates the canvas based on the current equation
        """
        curr_s = self.display_text.get()
        if curr_s != '':
            curr_s = '$' + curr_s + ' $'
        self.canvas.clear()
        self.canvas.text(0.2, 0.6, curr_s, fontsize=12)
        self.display.draw()

    def clear_display(self):
        """
        Clears the display
        """
        self.display_text.set('')
        self.update_canvas()

    def push(self, character):
        """
        Pushes a character or function to the display
        """
        curr_s = self.display_text.get()
        curr_s += character
        self.display_text.set(curr_s)
        self.update_canvas()


    def equal(self):
        """
        WIP Solves current equation in display
        """
        self.clear_display()

    def init_grid(self):
        """
        Initializes the weights of the grid
        """
        for column in range(7):
            self.master.columnconfigure(column, weight=1)
        for row in range(6):
            self.master.rowconfigure(row, weight=1)

    def init_display(self):
        """
        Initializes the display which shows the equation
        """
        self.figure_container = tk.Label(self.master)
        self.figure_container.grid(column=0, row=0, columnspan=7)
        self.figure = matplotlib.figure.Figure(figsize=(7, 0.5), dpi=100, frameon=False)
        self.canvas = self.figure.add_subplot(111)
        self.display = FigureCanvasTkAgg(self.figure, master=self.figure_container)
        self.display.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=1)
        self.display._tkcanvas.pack(side=tk.TOP, fill=tk.BOTH, expand=1)
        self.canvas.get_xcanvasis().set_visible(False)
        self.canvas.get_ycanvasis().set_visible(False)

    def init_cmds(self):
        """
        Initializes the commands used by the buttons and keybindings
        """
        self.factorial_cmd = lambda x=None: self.push('! ')
        self.open_paren_cmd = lambda x=None: self.push('(')
        self.close_paren_cmd = lambda x=None: self.push(') ')
        self.sine_cmd = lambda x=None: self.push(self.sine.get_func())
        self.nat_log_cmd = lambda x=None: self.push(self.nat_log.get_func())
        self.zero_cmd = lambda x=None: self.push('0')
        self.one_cmd = lambda x=None: self.push('1')
        self.two_cmd = lambda x=None: self.push('2')
        self.three_cmd = lambda x=None: self.push('3')
        self.four_cmd = lambda x=None: self.push('4')
        self.five_cmd = lambda x=None: self.push('5')
        self.six_cmd = lambda x=None: self.push('6')
        self.seven_cmd = lambda x=None: self.push('7')
        self.eight_cmd = lambda x=None: self.push('8')
        self.nine_cmd = lambda x=None: self.push('9')
        self.divide_cmd = lambda x=None: self.push('/')
        self.cosine_cmd = lambda x=None: self.push(self.cosine.get_func())
        self.log_cmd = lambda x=None: self.push(self.log.get_func())
        self.times_cmd = lambda x=None: self.push('*')
        self.tangent_cmd = lambda x=None: self.push(self.tangent.get_func())
        self.sqrt_cmd = lambda x=None: self.push(self.sqrt.get_func())
        self.minus_cmd = lambda x=None: self.push('-')
        self.exp_cmd = lambda x=None: self.push('E')
        self.dot_cmd = lambda x=None: self.push('.')
        self.plus_cmd = lambda x=None: self.push('+')
        self.equal_cmd = lambda x=None: self.equal()
        self.clear_cmd = lambda x=None: self.clear_display()
        self.percent_cmd = lambda x=None: self.push('%')
        self.space_cmd = lambda x=None: self.push(' ')

    def init_buttons(self):
        """
        Initializes all of the buttons on the calculator
        """
        self.mode = CalcButton(t="Rad | Deg", c=0, r=1, cs=2, cmd=self.toggle_mode)
        self.factorial = CalcButton(t="x!", c=2, r=1, cmd=self.factorial_cmd)
        self.open_paren = CalcButton(t="(", c=3, r=1, cmd=self.open_paren_cmd)
        self.close_paren = CalcButton(t=")", c=4, r=1, cmd=self.close_paren_cmd)
        self.percent = CalcButton(t='%', c=5, r=1, cmd=self.percent_cmd)
        self.clear = CalcButton(t='CE', c=6, r=1, cmd=self.clear_cmd)

        self.invert = CalcButton(t='Inv', c=0, r=2, cmd=self.invert_func)
        sine_text = VarText(self.master, Func('sin', 'sin('), Func('arcsin', 'sin^{-1}('))
        self.sine = CalcButton(vt=sine_text, c=1, r=2, cmd=self.sine_cmd)
        nat_log_text = VarText(self.master, Func('ln', 'ln('), Func('e^x', 'e^{} '))
        self.nat_log = CalcButton(vt=nat_log_text, c=2, r=2, cmd=self.nat_log_cmd)
        self.seven = CalcButton(t='7', c=3, r=2, cmd=self.seven_cmd)
        self.eight = CalcButton(t='8', c=4, r=2, cmd=self.eight_cmd)
        self.nine = CalcButton(t='9', c=5, r=2, cmd=self.nine_cmd)
        self.divide = CalcButton(t='/', c=6, r=2, cmd=self.divide_cmd)

        self.pi_num = CalcButton(t='pi', c=0, r=3, cmd=(lambda: self.push('\pi')))
        cosine_text = VarText(self.master, Func('cos', 'cos('), Func('arccos', 'cos^{-1}('))
        self.cosine = CalcButton(vt=cosine_text, c=1, r=3, cmd=self.cosine_cmd)
        log_text = VarText(self.master, Func('log', 'log('), Func('10^x', '10^{}'))
        self.log = CalcButton(vt=log_text, c=2, r=3, cmd=self.log_cmd)
        self.four = CalcButton(t='4', c=3, r=3, cmd=self.four_cmd)
        self.five = CalcButton(t='5', c=4, r=3, cmd=self.five_cmd)
        self.six = CalcButton(t='6', c=5, r=3, cmd=self.six_cmd)
        self.times = CalcButton(t='*', c=6, r=3, cmd=self.times_cmd)

        self.e_num = CalcButton(t='e', c=0, r=4)
        tangent_text = VarText(self.master, Func('tan', 'tan('), Func('arctan', 'tan^{-1}('))
        self.tangent = CalcButton(vt=tangent_text, c=1, r=4, cmd=self.tangent_cmd)
        sqrt_text = VarText(self.master, Func('sqrt', '\sqrt{'), Func('x^2', '^2'))
        self.sqrt = CalcButton(vt=sqrt_text, c=2, r=4, cmd=self.sqrt_cmd)
        self.one = CalcButton(t='1', c=3, r=4, cmd=self.one_cmd)
        self.two = CalcButton(t='2', c=4, r=4, cmd=self.two_cmd)
        self.three = CalcButton(t='3', c=5, r=4, cmd=self.three_cmd)
        self.minus = CalcButton(t='-', c=6, r=4, cmd=self.minus_cmd)

        #self.rnd = CalcButton(t='RND', c=0, r=5)
        self.exp = CalcButton(t='EXP', c=0, r=5, cmd=self.exp_cmd)
        pow_text = VarText(self.master, Func('x^y', '^'), Func('x^1/y', '\sqrt[x]{'))
        self.pow = CalcButton(vt=pow_text, c=2, r=5)
        self.zero = CalcButton(t='0', c=3, r=5, cmd=self.zero_cmd)
        self.dot = CalcButton(t='.', c=4, r=5, cmd=self.dot_cmd)
        self.equals = CalcButton(t=' = ', c=5, r=5, cmd=self.equal_cmd)
        self.plus = CalcButton(t=' + ', c=6, r=5, cmd=self.plus_cmd)

    def init_bindings(self):
        """
        Defines keybindings for ease-of-use
        """
        self.master.bind('!', self.factorial_cmd)
        self.master.bind('(', self.open_paren_cmd)
        self.master.bind(')', self.close_paren_cmd)
        self.master.bind('<BackSpace>', self.clear_cmd)
        self.master.bind('0', self.zero_cmd)
        self.master.bind('1', self.one_cmd)
        self.master.bind('2', self.two_cmd)
        self.master.bind('3', self.three_cmd)
        self.master.bind('4', self.four_cmd)
        self.master.bind('5', self.five_cmd)
        self.master.bind('6', self.six_cmd)
        self.master.bind('7', self.seven_cmd)
        self.master.bind('8', self.eight_cmd)
        self.master.bind('9', self.nine_cmd)
        self.master.bind('/', self.divide_cmd)
        self.master.bind('*', self.times_cmd)
        self.master.bind('-', self.minus_cmd)
        self.master.bind('.', self.dot_cmd)
        self.master.bind('+', self.plus_cmd)
        self.master.bind('=', self.equal_cmd)
        self.master.bind('<Return>', self.equal_cmd)
        self.master.bind('%', self.percent_cmd)
        self.master.bind('<Down>', self.space_cmd)
        self.master.bind('<space>', self.space_cmd)

    def init_window(self):
        """
        Initializes the window which contains the calculator
        """
        self.master.title('Calculator')

        self.init_grid()

        self.init_display()

        self.init_cmds()

        self.init_buttons()

        self.init_bindings()

def main():
    '''
    Main method for running the Tkinter application
    '''
    root = tk.Tk()
    root.geometry("500x250")
    app = Calculator(root)
    root.mainloop()

if __name__ == "__main__":
    main()
