% Problem 21. Insert an element at a given position into a list.
insert_at(X, L, 1, [X|L]).
insert_at(X, [H|L], Pos, [H|T]):-
    Pos > 1,
    Posm1 is Pos - 1,
    insert_at(X, L, Posm1, T).