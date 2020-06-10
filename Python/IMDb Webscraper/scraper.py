from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.by import By
from selenium.common.exceptions import TimeoutException
from selenium import webdriver
from bs4 import BeautifulSoup
import pandas as pd

def main():
	titles = []
	years = []
	ratings = []
	descriptions = []
	trailers = []
	driver = webdriver.Chrome("/mnt/c/Users/AaronTheNerd/Downloads/chromedriver_win32/chromedriver.exe") # Give Selenium driver
	driver.get("https://www.imdb.com/chart/top/?ref_=nv_mv_250") # Put driver to IMDb's top 250 movies
	content = driver.page_source # Grab HTML source
	soup = BeautifulSoup(content, features="html.parser") # Give BeautifulSoup HTML source
	try:
		WebDriverWait(driver, 10).until(EC.presence_of_element_located((By.CLASS_NAME, 'lister-list'))) # Wait for list to load
	except TimeoutException:
		print "Timeout"
	movie_list = soup.find('tbody', attrs={'class' : 'lister-list'}) # Find the list
	for movie in movie_list.findAll('tr'): # Find each element of the list
		title = movie.find('td', attrs={'class' : 'titleColumn'}) # Find the title section
		year = title.find('span', attrs={'class' : 'secondaryInfo'}) # Find the year in the title section
		rating = movie.find('td', attrs={'class' : 'ratingColumn imdbRating'}) # Find the rating section
		titles.append(title.a.text) # Save title
		years.append(year.text) # Save year
		ratings.append(rating.strong.text) # Save rating
		link = movie.a.get("href", None) # Find link to each movie's page
		driver.get("https://imdb.com/" + link) # Follow link
		individual_content = driver.page_source # Grab HTML source
		individual_soup = BeautifulSoup(individual_content, features="html.parser") # Give BeautifulSoup HTML source
		description = individual_soup.find('div', attrs={'class' : 'summary_text'}) # Grab description
		trailer = "" # Grab trailer link, but trailer may not exist
		try: # Try to grab trailer link
			trailer = "https://imdb.com/" + individual_soup.find('a', attrs={'class' : 'slate_button prevent-ad-overlay video-modal'}).get('href', None)
		except: # Give None if fails
			print "Trailer not found"
			trailer = "None"
		descriptions.append(description.text.strip()) # Save Description
		trailers.append(trailer) # Save Trailer
	df = pd.DataFrame({'Title':titles, 'Year':years, 'Rating':ratings, 'Description':descriptions, 'Trailer':trailers}) # Create dataframe for movies
	df.to_csv('movies.csv', index=False, encoding='utf-8') # Save dataframe


if __name__ == "__main__":
	main()