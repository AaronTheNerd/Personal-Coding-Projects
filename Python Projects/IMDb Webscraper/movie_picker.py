import pandas as pd
import random
import textwrap

def main():
  data = pd.read_excel('/mnt/d/Personal-Coding-Projects/Python Projects/IMDb Webscraper/movies.xlsx') # Load the Excel Workbook
  choice = random.randint(0, 249) # Choose a random number (0 - 249)
  movie = data.iloc[choice, 0:5]  # Grab title, rating, description, trailer, and release year
  # pretty print
  print "====================================================================================="
  print "Title:", movie[0]
  print "Year:", movie[1]
  print "Rating:", movie[2]
  print "Place:", choice+1
  description = "\n".join(textwrap.wrap("Description: " + movie[3], 85))
  print description
  print "Trailer:", movie[4]
  print "====================================================================================="

if __name__ == "__main__":
  main()