% Problem 5. Reverse a list
reverse_list([], []).
reverse_list([H|T], Y):-
    reverse_list(T, X),
    append(X, [H], Y).