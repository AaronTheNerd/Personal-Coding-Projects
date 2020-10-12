t(_, nil, nil).
t(_, nil, _).
t(_, _, nil).
t(_, _, _).

istree(Res):-
    catch((Res, write('Yes\n')),
        error(_, _),
        format('No\n')).