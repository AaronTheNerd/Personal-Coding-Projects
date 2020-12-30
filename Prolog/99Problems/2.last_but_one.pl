% Problem 2. Find the last but one element
last_but_one(_, []):- fail.
last_but_one(_, [_]):- fail.
last_but_one(X, [X,_]).
last_but_one(X, [_|L]):-
    last_but_one(X, L).