% Problem 6. Check if list is a palindrome
palindrome([]).
palindrome(L):-
    reverse_list(L, RevL),
    L = RevL.

reverse_list([], []).
reverse_list([H|T], Y):-
    reverse_list(T, X),
    append(X, [H], Y).