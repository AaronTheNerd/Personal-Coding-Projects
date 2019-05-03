function num = SmallestMultipleOf(upper_bound)
% Gives the smallest number that is evenly divisible by the numbers 1 to
% upper_bound
    factors = zeros(1, upper_bound);
    for i = 2:upper_bound
        i_factors = FactorsOf(i);
        dim = size(i_factors);
        for j = 1:dim(2)
            if i_factors(j) > factors(j)
                factors(j) = i_factors(j);
            end
        end
    end
    product = 1;
    for i = 2:upper_bound 
        product = product * i^factors(i);
    end
    num = product;
    function factors = FactorsOf(num)
        factors = zeros(1, num);
        p = 2;
        while num >= p * p
            if mod(num, p) == 0
                factors(p) = factors(p) + 1;
                num = num / p;
            else
                p = p + 1;
            end
        end
        factors(num) = factors(num) + 1;
    end
end

