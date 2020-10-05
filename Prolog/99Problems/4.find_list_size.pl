% Problem 4. Find the size of a list
find_list_size([], 0).
find_list_size([_|L], N):-
    find_list_size(L, Nm1),
    N is 1 + Nm1.