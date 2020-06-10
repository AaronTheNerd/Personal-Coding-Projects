function sum = FactorialDigitSum(num)
% This function takes a number num and finds the sum of the digits for num
% factorial
    format longG
    digits(200);
    syms factorial_num
    factorial_num = vpa(factorial(num));
    sum = 0;
    for i = 0:floor(log10(factorial_num))
        sum = sum + mod(floor(factorial_num / 10^i), 10);
    end
end
