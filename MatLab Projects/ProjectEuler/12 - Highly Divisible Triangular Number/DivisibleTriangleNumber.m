function triangle = DivisibleTriangleNumber
% This function keeps searching for triangle numbers until it is divisble
% by 500 unique factors
    triangles(1) = 1;
    index = 1;
    while ~isHighlyDivisible(triangles(index))
        index = index + 1;
        triangles(index) = index + triangles(index - 1);
    end
    triangle = triangles(index);
    function result = isHighlyDivisible(num)
        count = 0;
        for i = 1:sqrt(num)
            if mod(num, i) == 0
                if num / i == i
                    count = count + 1;
                else
                    count = count + 2;
                end
            end
        end
        if count >= 500
            result = true;
        else
            result = false;
        end
    end
end

