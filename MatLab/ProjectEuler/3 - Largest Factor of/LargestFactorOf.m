function largest_factor = LargestFactorOf(num)
% Finds the largest prime factor of num
p = 2;
while num >= p * p
    if mod(num, p) == 0
        num = num / p;
    end
    p = p + 1;
end
largest_factor = num;
end

