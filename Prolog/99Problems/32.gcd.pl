% Problem 32. Find the GCD of two numbers
gcd(N, 0, N).
gcd(N1, N2, GCD):-
    N2New is mod(N1, N2),
    gcd(N2, N2New, GCD).