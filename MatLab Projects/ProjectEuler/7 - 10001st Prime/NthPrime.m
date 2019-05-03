function prime = NthPrime(n)
% Finds the nth prime number
    global primes;
    primes = zeros(1, n);
    primes(1) = 2;
    for index = 2:n
        guess = primes(index - 1) + 1;
        while ~isPrime(guess)
            guess = guess + 1;
        end
        primes(index) = guess;
    end
    dim = size(primes);
    prime = primes(dim(2));
    function boolean = isPrime(guess)
        i = 1;
        num = primes(i);
        while num ~= 0
            if mod(guess, num) == 0
                boolean = false;
                return;
            end
            i = i + 1;
            num = primes(i);
        end
        boolean = true;
    end
end

