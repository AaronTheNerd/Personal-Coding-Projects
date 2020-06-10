function sum = EvenFibonacciNumbers
% Sums all even fibonacci numbers under 4 million
sum = 2;
fibo_nums(1) = 1;
fibo_nums(2) = 2;
index = 3;
current_num = 2;
while current_num < 4e6
    fibo_nums(index) = fibo_nums(index - 1) + fibo_nums(index - 2);
    if mod(fibo_nums(index), 2) == 0
        sum = sum + fibo_nums(index);
    end
    current_num = fibo_nums(index);
    index = index + 1;
end
end

