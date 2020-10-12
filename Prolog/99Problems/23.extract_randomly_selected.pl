% Problem 23. Extract a given number of randomly selected elements from a list.
rnd_select(_, 0, []).
rnd_select(L, Num, [Rand|T]):-
    Num > 0,
    Numm1 is Num - 1,
    length(L, LLength),
    LLengthp1 is LLength + 1,
    random(1, LLengthp1, RandPos),
    remove_at(Rand, L, RandPos, LmRand),
    rnd_select(LmRand, Numm1, T).

remove_at(_, [], _, []).
remove_at(H, [H|T], 1, T).
remove_at(Removed, [H|T], Pos, [H|ListmRemoved]):-
    Pos > 1,
    Posm1 is Pos - 1,
    remove_at(Removed, T, Posm1, ListmRemoved).

