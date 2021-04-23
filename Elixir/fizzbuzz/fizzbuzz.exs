# Copyright 2021
# Written by Aaron Barge
fizzbuzz = fn n ->
    ""
    |> (fn
            s when rem(n, 3) == 0 -> s <> "fizz"
            s -> s
        end).()
    |> (fn
            s when rem(n, 5) == 0 -> s <> "buzz"
            s -> s
        end).()
    |> (fn
            s when s == "" -> to_string(n)
            s -> s
        end).()
end

fizzbuzz_ = fn
    (0, 0, _) -> "fizzbuzz"
    (0, _, _) -> "fizz"
    (_, 0, _) -> "buzz"
    (_, _, n) -> to_string(n)
end

fizzbuzz_ = fn n ->
    fizzbuzz_.(rem(n, 3), rem(n, 5), n)
end

main = fn n ->
    Enum.each(1..n, fn n -> IO.puts fizzbuzz.(n) end)
end

main.(100)
