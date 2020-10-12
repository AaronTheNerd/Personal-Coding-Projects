% Problem 22. Create a list containing all integers within a given range.
range(X, X, [X]).
range(X, Y, [X|T]):-
    X < Y,
    Xp1 is X + 1,
    range(Xp1, Y, T).