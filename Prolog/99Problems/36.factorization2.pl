% Problem 36. Factor a number into its prime components
% As 120 = [[2, 3], [3, 1], [5, 1]]
factor(1, []).
factor(N, L):-
    factor(N, 2, L).
factor(1, _, []).
factor(N, Curr, [[Curr, M]|L]):-
    0 is mod(N, Curr),
    multiplicity(N, Curr, M, NNew),
    factor(NNew, Curr, L).
factor(N, 2, L):-
    \+ 0 is mod(N, 2),
    factor(N, 3, L).
factor(N, Curr, L):-
    \+ 0 is mod(N, Curr),
    CurrNew is Curr + 2,
    factor(N, CurrNew, L).

multiplicity(N, D, M, NNew):-
    0 is mod(N, D),
    NCurr is N // D,
    multiplicity(NCurr, D, MNew, NNew),
    M is MNew + 1.
multiplicity(N, D, 0, N):-
    \+ 0 is mod(N, D).