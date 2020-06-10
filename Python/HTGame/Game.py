# Written by Aaron Barge
# Copyright 2019
# A little context
# Original Problem:
#   Bob and Alice each picked a sequence of heads and tails: 
#   Bob chose HTTTH
#   Alice chose TTTTH
#   A fair coin is flipped until one of the two sequences shows up as five consecutive flips
#   at which point that player wins.
#   For instance, if the flips are HHTHTTTH, then Bob wins.
#   What is Alice's probability of winning?
# This problem was posted in the mathematics building at my university
# My girlfriend and I thought about which person would win
# I explained that the answer should be 50% since it's random
# She thought the question was much more difficult but guessed that Bob would have a higher probability of winning
# since HTTTH is more common than TTTTH
# My solution, write a program to run it to determine what the chance of winning is.
# The answer I recieved was consistent through multiple tests. Alice wins ~53% of the time.
# If I had to guess the odds are 17/32 that Alice wins
import random, time
class Person(object):
    def __init__(self, name, choice):
        self.name = name
        self.choice = choice
        self.wins = 0
    def hasWon(self):
        print(self.name + " has won!")
        self.wins = self.wins + 1
    def print(self, num_of_rounds):
        print(self.name + " has won " + str(round(self.wins / num_of_rounds * 100, 2)) + "% of the time")
class Game(object):
    def __init__(self, player1, player2):
        self.gameOver = False
        self.flips = ""
        self.player1 = player1
        self.player2 = player2
    def play(self):
        self.flips = ""
        self.gameOver = False
        while not self.gameOver:
            rand = random.randint(0,1)
            self.flips = self.flips + ("H" if rand is 1 else "T")
            if len(self.flips) >= 5:
                if self.flips[-5:] == self.player1.choice:
                    self.player1.hasWon()
                    self.gameOver = True
                    print(self.flips)
                elif self.flips[-5:] == self.player2.choice:
                    self.player2.hasWon()
                    self.gameOver = True
                    print(self.flips)
    def printStats(self, num_of_rounds):
        self.player1.print(num_of_rounds)
        self.player2.print(num_of_rounds)

bob = Person("Bob", "HTTTH")
alice = Person("Alice", "TTTTH")
game = Game(bob, alice)
num_of_rounds = 10000
startTime = time.time()
for rounds in range(num_of_rounds):
    game.play()
endTime = time.time()
game.printStats(num_of_rounds)
print("Took " + str(round(endTime - startTime, 1)) + " secs to calculate")