function sum = AllNonAbundantSums
% This functions finds the sum of all the numbers which cannot be written
% as the sum of two abundant numbers. In this function, I used a
% 2xupper_limit matrix to save if a number is abundant and whether or not
% is has been checked, the first row being whether it is abundant and the
% second being if it has been checked.
    upper_limit = 28123;
    global abundant_numbers
    abundant_numbers = zeros(2, upper_limit);
    sum = 0;
    for num = 1:upper_limit
        is_addable = 0;
        for adder_1 = 1:num/2
            adder_2 = num - adder_1;
            if abundant_numbers(2, adder_1) == 0
                abundant_numbers(2, adder_1) = 1;
                abundant_numbers(1, adder_1) = isAbundant(adder_1);
            end
            if abundant_numbers(2, adder_2) == 0
                abundant_numbers(2, adder_2) = 1;
                abundant_numbers(1, adder_2) = isAbundant(adder_2);
            end
            if abundant_numbers(1, adder_1) == 1 && abundant_numbers(1, adder_2) == 1
                is_addable = 1;
                break;
            end
        end
        if is_addable == 0
            sum = sum + num;
        end
    end
    
    save abundant_numbers.mat abundant_numbers
    
    function result = isAbundant(n)
        abundance = 0;
        for i = 1:sqrt(n)
            if mod(n, i) == 0
                if i == 1
                    abundance = abundance + i;
                elseif n / i == i
                    abundance = abundance + i;
                else
                    abundance = abundance + i + n/i;
                end
            end
        end
        if abundance > n
            result = 1;
        else
            result =  0;
        end
    end
end

