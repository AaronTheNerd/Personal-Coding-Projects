% Problem 8. Eliminate consecutive duplicates in list
compress([], []).
compress([X], [X]).
compress([X, Y], [X, Y]):-
    \+ X = Y.
compress([X, Y|T], [X|Z]):-
    \+ X = Y,
    compress([Y|T], Z).
compress([H, H|T], Z):-
    compress([H|T], Z).