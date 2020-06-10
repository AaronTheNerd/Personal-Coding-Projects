function sum = SumOfPrimesUnder(upper_bound)
% This function will find the sum of every prime from 2 to the upper bound
    primes = ones(1, upper_bound);
    primes(1) = 0;
    sum = 0;
    for i = 2:upper_bound
        if primes(i) == 1
            sum = sum + primes(i);
            for j = (i^2):(i):(upper_bound)
                primes(j) = 0;
            end
        end
    end
    save primes.mat primes
end

