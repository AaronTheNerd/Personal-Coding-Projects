function sum = SumOfDigits
% This function gives the sum of the digits for 2^1000
    format longG
    digits(350);
    syms num
    num = vpa(2^1000);
    sum = 0;
    for i = 0:floor(log10(num))
        sum = sum + mod(floor(num / 10^i), 10);
    end
end
