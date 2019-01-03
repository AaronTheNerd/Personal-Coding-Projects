# Written by Aaron Barge
# Copyright 2019
# Completed on January 3rd, 2019
# Sarcastic tip calculator

price = None
while price is None:
    # Some positive floating-point number
    try:
        price = float(input("What was the price? "))
    except:
        price = None
        print "Real funny"
        continue
    if price <= 0:
        print "Sure thing, man"
        price = None
    elif price > 100:
        print "Someone's not a cheap date"

# Some rating between 1 - 5
service = None
while service is None:
    try:
        service = int(input("How would you rate the service between 1 and 5? "))
    except:
        service = None
        print "mhm"
        continue
    if service < 1:
        print "That's pretty mean"
        service = 1
    elif service > 5:
        print "That's great!"
        service = 5
service = service - 1 # Turning service into an index

tip_list = [.07, .10, .15, .20, .25]
tip = price * tip_list[service]
print "You should pay $" + str(tip) + " as a tip"
print "For a total of $" + str(tip + price)