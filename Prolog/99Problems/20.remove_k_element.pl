% Problem 20. Remove the K'th element from a list
remove_at(_, [], _, []).
remove_at(H, [H|T], 1, T).
remove_at(Removed, [H|T], Pos, [H|ListmRemoved]):-
    Pos > 1,
    Posm1 is Pos - 1,
    remove_at(Removed, T, Posm1, ListmRemoved).
