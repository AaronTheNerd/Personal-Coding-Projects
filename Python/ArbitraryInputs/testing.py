'''
This file is used to help me better understand how to use an arbitrary
amount of inputs in a Python function
'''

import math

class Stats(object):
    '''
    This is a collection of methods for calculations
    '''

    def __init__(self):
        return

    @staticmethod
    def sum(*nums):
        '''
        Computes the sum of all inputs
        '''
        sum_ = 0
        for num in nums:
            sum_ += num
        return sum_

    @staticmethod
    def average(*nums):
        '''
        Computes the average of all inputs
        '''
        if not nums:
            return 0
        return Stats.sum(*nums)/len(nums)

    @staticmethod
    def min(*nums):
        '''
        Computes the minimum of all inputs
        '''
        min_ = float('inf')
        for num in nums:
            if num < min_:
                min_ = num
        return min_

    @staticmethod
    def max(*nums):
        '''
        Computes the maximum of all inputs
        '''
        max_ = -float('inf')
        for num in nums:
            if num > max_:
                max_ = num
        return max_

    @staticmethod
    def mode(*nums):
        '''
        Computes the most frequent number of all inputs
        '''
        max_freq = 1
        num_freqs = dict()
        for num in nums:
            if num_freqs.get(num) is None:
                num_freqs[num] = 1
            else:
                new_freq = num_freqs.get(num) + 1
                num_freqs[num] = new_freq
                if new_freq > max_freq:
                    max_freq = new_freq
        if max_freq == 1:
            return None
        return [num for num, freq in num_freqs.items() if freq == max_freq]

    @staticmethod
    def range(*nums):
        '''
        Computes the range of all inputs
        '''
        return Stats.max(*nums) - Stats.min(*nums)

    @staticmethod
    def product(*nums):
        '''
        Computes the product of all inputs
        '''
        if not nums:
            return 0
        product = 1
        for num in nums:
            product *= num
        return product

    @staticmethod
    def std_dev_sample(*nums):
        '''
        Computes the sample standard deviation of all inputs
        '''
        sum_of_squares = Stats.sum(*[num**2 for num in nums])
        squared_sum = Stats.sum(*nums)**2
        size = len(nums)
        sigma_squared = (1/(size - 1)) * (sum_of_squares - (squared_sum / size))
        return math.sqrt(sigma_squared)

    @staticmethod
    def std_dev_pop(*nums):
        '''
        Computes the population standard deviation of all inputs
        '''
        size = len(nums)
        average = Stats.average(*nums)
        nums_ = [(num - average) ** 2 for num in nums]
        sum_ = Stats.sum(*nums_)
        sigma_squared = (1 / size) * sum_
        return math.sqrt(sigma_squared)

    @staticmethod
    def median(*nums):
        '''
        Computes the median of all inputs
        '''
        nums_ = list(nums)
        nums_.sort()
        size = len(nums)
        if size % 2 == 0:
            return Stats.average(nums_[(size - 1) // 2], nums_[size // 2])
        return nums_[(size - 1) // 2]



class Print(object):
    @staticmethod
    def my_print(*stuff, sep=' ', end=''):
        string = ''
        for thing in stuff:
            string += str(thing) + sep
        string = string.rstrip(sep)
        string += end
        print(string)



def main():
    '''
    Performs tests of all methods in Stats
    '''
    nums = (7, 3, 2, 8, 5, 9, 10, 2, 3, 8)
    print("Sum:", Stats.sum(*nums))
    print("Average:", Stats.average(*nums))
    print("Minimum:", Stats.min(*nums))
    print("Maximum:", Stats.max(*nums))
    print("Range:", Stats.range(*nums))
    print("Mode:", Stats.mode(*nums))
    print("Product:", Stats.product(*nums))
    print("Standard Deviation (Sample):", Stats.std_dev_sample(*nums))
    print("Standard Deviation (Population):", Stats.std_dev_pop(*nums))
    print("Median:", Stats.median(*nums))
    print("3 * 5 * 17 * 343 * 9 =", Stats.product(3, 5, 17, 343, 9))
    Print.my_print('stuff:', 4, 7, 5, 6)
    Print.my_print('dog', 'cat', 'yup', 5, sep=' psh ')
    Print.my_print('there', 'are', '3', 'lines', 'after', 'this', end='\n\n\n')
    Print.my_print("Here's a list with multiple lines:")
    Print.my_print('banana', 'apple', 'orange', sep='\n')



if __name__ == "__main__":
    main()
