function product = SpecialTriplet
% This function finds the pythagorean triplet, a^2 + b^2 = c^2, such that 
% a + b + c = 1000 and gives a * b * c
    for a = 1:998
        for b = 1:999-a
            for c = 1:1000-a-b
                if a^2 + b^2 == c^2 && a + b + c == 1000
                    disp("a = " + a + ", b = " + b + ", c = " + c);
                    product = a * b * c;
                    return;
                end
            end
        end
    end
end

