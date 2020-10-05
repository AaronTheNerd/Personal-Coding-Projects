% Problem 31. Check if a number is prime.
is_prime(P):-
    P =< 3.

is_prime(P):-
    P > 3,
    \+ 0 is mod(P, 2),
    \+ 0 is mod(P, 3),
    is_prime(P, 5).

is_prime(P, I):-
    (I * I) > P.

is_prime(P, I):-
    (I * I) =< P,
    \+ 0 is mod(P, I),
    \+ 0 is mod(P, I + 2),
    is_prime(P, I + 6).
