function num = LongestCollatzStreak
    longest_streak = 0;
    for i = 2:1e6
        streak = collatz(i, 1);
        if streak > longest_streak
            longest_streak = streak;
        end
    end
    num = longest_streak;
    function streak = collatz(num, curr_streak)
        if num == 1
            streak = curr_streak;
            return;
        end
        if mod(num, 2) == 0
            streak = collatz(num / 2, curr_streak + 1);
        else
            streak = collatz(3 * num + 1, curr_streak + 1);
        end
    end
end

