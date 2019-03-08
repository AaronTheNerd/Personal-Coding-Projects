# Written by Aaron Barge
# Copyright 2019
# I don't know what it is but change returners have always eluded me
# I think it has something to do with floating point rounding errors
# But I think this works
def main():
    cost = None
    while cost is None:
        try:
            cost = float(input("How much did your items cost? "))
        except ValueError:
            print("I think we got ourselves a comedian")
            cost = None
    paid = None
    while paid is None:
        try:
            paid = float(input("How much did you pay? "))
        except ValueError:
            print("Definitely a comedian")
            paid = None
    if cost > paid:
        print("Well you need to pay more to start")
        return
    elif cost == paid:
        print("You paid the perfect amount!")
        return
    else:
        cash = {"100's":100.00,
                "50's":50.00,
                "20's":20.00,
                "10's":10.00,
                "5's":5.00,
                "1's": 1.00,
                "Quarter":0.25,
                "Dime":0.1,
                "Nickel":0.05,
                "Penny":0.01}
        change = paid - cost
        print("You should get: " + str(round(change, 2)) + " or:")
        change = change_to_cash(change, cash)
        print(change)
def change_to_cash(change, cash):
    index = 0
    ret_cash = cash.copy()
    for item in cash:
        ret_cash[item] = 0
    while change != 0:
        while round(change,2) >= round(list(cash.values())[index], 2):
            if index < len(cash):
                ret_cash[list(ret_cash.keys())[index]] = ret_cash[list(ret_cash.keys())[index]] + 1
                change = change - list(cash.values())[index]
            else:
                break
        index = index + 1
        if index >= len(cash):
            break
    return ret_cash

if __name__ == "__main__":
    main()