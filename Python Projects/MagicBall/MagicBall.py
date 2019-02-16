# Written by Aaron Barge
# Copyright 2019
import io, random
answers = []
def getAnswers():
  global answers
  try:
    file = open("C:/Users/AaronTheNerd/Documents/Personal-Coding-Projects/Python Projects/MagicBall/Answers.txt", 'r')
    for line in file:
      answers.append(line)
    return True
  except:
    print("Answers failed to load")
    return False

def getAnswer():
  global answers
  if len(answers) > 0:
    print(answers[random.randrange(len(answers))])
  else:
    if getAnswers():
      getAnswer()

def main():
  while True:
    print("Concentrate on your Question")
    print("Type 'no' if you no longer need my help")
    text = input("Press enter when ready ")
    if text != 'no':
      getAnswer()
    else:
      break

if __name__ == "__main__":
  main()
