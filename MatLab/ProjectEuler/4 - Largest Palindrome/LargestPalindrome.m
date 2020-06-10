function Palindrome = LargestPalindrome
% Find the largest palindrome that can be written as the product of two
% 3-digit numbers
    format longG
    max_palindrome = 0;
    p1 = 999;
    while p1 > 99
        p2 = 999;
        while p2 >= p1
            if p1 * p2 > max_palindrome && isPalindrome(p1 * p2)
                max_palindrome = p1 * p2;
            end
            p2 = p2 - 1;
        end
        p1 = p1 - 1;
    end
    Palindrome = max_palindrome;
    function boolean = isPalindrome(num)
        str = num2str(num);
        if str == reverse(str)
            boolean = true;
        else
            boolean = false;
        end
    end
end

