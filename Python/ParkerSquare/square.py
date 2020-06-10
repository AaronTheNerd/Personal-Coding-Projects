# Written by Aaron Barge
# Copyright 2020
# Goal: Find a 3x3 Parker Square
# A Parker Square is a magic square where all the numbers are also squares

def main():
    square = [[1, 1, 1], [1, 1, 1], [1, 1, 1]]
    nums = []
    for i in range(100000):
        nums.append((i + 1) ** 2)
    print(nums)
    # Check the last number
    # Try to find 3 unique numbers where
    # the last number - that number = some ** 2

if __name__ == "__main__":
    main()