% Problem 33. Determine if 2 numbers are coprime
coprime(N1, N2):-
    gcd(N1, N2, 1).

gcd(N, 0, N).
gcd(N1, N2, GCD):-
    N2New is mod(N1, N2),
    gcd(N2, N2New, GCD).