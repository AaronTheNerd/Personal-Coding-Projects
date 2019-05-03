function sum = sum_of3and5under(n)
% Takes the sum of all numbers divisible by 3 or 5 that's below n
sum = 0;
for i = 3:n-1
    if mod(i, 3) == 0 || mod(i, 5) == 0
        sum = sum + i;
    end
end
end

