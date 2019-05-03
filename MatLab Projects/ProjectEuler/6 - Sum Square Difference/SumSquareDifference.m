function difference = SumSquareDifference(upper_bound)
% This function finds the difference between the sum of squares up to the
% upperbound and the square of the sums up to the upperbound
    difference = SquareOfSums(upper_bound) - SumOfSquares(upper_bound);
    function sum = SumOfSquares(upper_bound)
        sum = (upper_bound * (upper_bound + 1) * (2 * upper_bound + 1)) / 6;
    end
    function sum = SquareOfSums(upper_bound)
        sum = (upper_bound * (upper_bound + 1)) / 2;
        sum = sum ^ 2;
    end
end

