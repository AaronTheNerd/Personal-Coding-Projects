# Written by Aaron Barge
# Copyright 2019
import io, random, os
answers = []
file_path = os.path.abspath(__file__) + "/../Answers.txt"
def getAnswers():
  global file_path
  global answers
  try:
    file = open(file_path, 'r')
    for line in file:
      answers.append(line)
    file.close()
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
  global file_path
  while True:
    print("Concentrate on your Question")
    print("Type 'no' if you no longer need my help")
    print("Type 'idea' if you have a good idea for an answer")
    text = input("Press enter when ready ")
    if text == 'no':
      break
    elif text == 'idea':
      new_answer = input("What is your idea? ")
      file = open(file_path, 'a')
      file.write(new_answer + '\n')
      file.close()
      print("That is a brilliant idea!\n")
    else:
      getAnswer()

if __name__ == "__main__":
  main()
