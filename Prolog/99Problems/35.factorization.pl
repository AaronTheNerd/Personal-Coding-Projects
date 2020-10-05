% Problem 35. Factor a number into its prime components
factor(1, []).
factor(N, L):-
    factor(N, 2, L).
factor(1, _, []).
factor(N, Curr, [Curr|L]):-
    0 is mod(N, Curr),
    NNew is N // Curr,
    factor(NNew, Curr, L).
factor(N, 2, L):-
    \+ 0 is mod(N, 2),
    factor(N, 3, L).
factor(N, Curr, L):-
    \+ 0 is mod(N, Curr),
    CurrNew is Curr + 2,
    factor(N, CurrNew, L).