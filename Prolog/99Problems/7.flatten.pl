% Problem 7. Flatten a nested list
flatten([], []).
flatten([X], [X]):-
    \+ is_list(X).
flatten([X], Y):-
    flatten(X, Y).
flatten([H|T], [H|Y]):-
    \+ is_list(H),
    flatten(T, Y).
flatten([H|T], YFlat):-
    append(H, T, Y),
    flatten(Y, YFlat).