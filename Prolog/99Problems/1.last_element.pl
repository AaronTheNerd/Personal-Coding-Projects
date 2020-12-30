% Problem 1. Find last element in a list
last_element(_, []):- fail.
last_element(X, [X]).
last_element(X, [_|L]):-
    last_element(X, L).