% Problem 3. Find Kth element in list
find_k_element(_, [], _):- fail.
find_k_element(X, [X|_], 1).
find_k_element(X, [_|L], K):-
    Km1 is K - 1,
    find_k_element(X, L, Km1).