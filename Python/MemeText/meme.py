'''
MemeText
Written by Aaron Barge
Copyright 2020

This code has one simple purpose, it takes text that has been copied and
returns the text as such:

Original:
Hi, my name is Aaron

New:
hI, mY NaMe iS AaRoN
'''

def to_meme(text):
	ret = ""
	cap = False
	for char in text:
		if cap:
			ret += char.upper()
		else:
			ret += char.lower()
		if char.isalpha():
			cap = not cap
	return ret

def main():
	text = "there's an app for that"
	print(text)
	print(to_meme(text))

if __name__ == "__main__":
	main()