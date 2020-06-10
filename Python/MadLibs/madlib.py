def main():
  '''
  This project is a way to design your own madlib style prompt
  '''
  # Step 1: get paragraph
  paragraph = getText()

  # Step 2: remove all adjectives, verbs, nouns
  mad_lib = removeText(paragraph)

  # Step 3: Ask user for replacement words based off description
  new_paragraph = fill_prompt(mad_lib)
  print(new_paragraph)

def getText():
  return "I ran quickly"

def removeText(paragraph):
  return "I <verb_past> <adverb>"

def fill_prompt(mad_lib):
  '''
  Won't currently handle punctuation
  '''
  new_paragraph = ""
  for word in mad_lib.split():
    new_word = word
    if word == "<verb_present>":
      new_word = input("Present tense verb: ")
    elif word == "<verb_past>":
      new_word = input("Past tense verb: ")
    elif word == "<verb_future>":
      new_word = input("Future tense verb: ")
    elif word == "<adverb>":
      new_word = input("Adverb: ")
    elif word == "<adjective>":
      new_word = input("Adjective: ")
    elif word == "<noun>":
      new_word = input("Noun: ")
    new_paragraph += new_word + " "
  return new_paragraph

if __name__ == "__main__":
  main()