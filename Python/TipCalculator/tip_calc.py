'''
Written by Aaron Barge
Copyright 2019
This is a simple, sarcastic tip calculator
'''

PRICE = None
while PRICE is None:
    # Some positive floating-point number
    try:
        PRICE = float(input("What was the price? "))
    except ValueError:
        PRICE = None
        print("Real funny")
        continue
    if PRICE <= 0:
        print("Sure thing, man")
        PRICE = None
    elif PRICE > 100:
        print("Someone's not a cheap date")

# Some rating between 1 - 5
SERVICE = None
while SERVICE is None:
    try:
        SERVICE = int(input("How would you rate the service between 1 and 5? "))
    except ValueError:
        SERVICE = None
        print("mhm")
        continue
    if SERVICE < 1:
        print("That's pretty mean")
        SERVICE = 1
    elif SERVICE > 5:
        print("That's great!")
        SERVICE = 5
SERVICE = SERVICE - 1 # Turning service into an index

TIP_LIST = [.07, .10, .15, .20, .25]
TIP = PRICE *TIP_LIST[SERVICE]
print("You should pay $" + str(round(TIP)) + " as a tip")
print("For a total of $" + str(round(TIP + PRICE)))
