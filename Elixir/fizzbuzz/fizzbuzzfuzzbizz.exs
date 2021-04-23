# Copyright 2021
# Written by Aaron Barge

helper = fn
    (s, n, m, s1) when rem(n, m) == 0 -> s <> s1
    (s, _, _, _) -> s
end

fizzbuzz = fn n ->
    ""
    |> helper.(n, 3, "fizz")
    |> helper.(n, 5, "buzz")
    |> helper.(n, 7, "fuzz")
    |> helper.(n, 11, "bizz")
    |> (fn
            s when s == "" -> to_string(n)
            s -> s
        end).()
end

fizzbuzz_ = fn
    (0, 0, 0, 0, _) -> "fizzbuzzfuzzbizz"
    (0, 0, 0, _, _) -> "fizzbuzzfuzz"
    (0, 0, _, 0, _) -> "fizzbuzzbizz"
    (0, _, 0, 0, _) -> "fizzfuzzbizz"
    (_, 0, 0, 0, _) -> "buzzfuzzbizz"
    (0, 0, _, _, _) -> "fizzbuzz"
    (0, _, 0, _, _) -> "fizzfuzz"
    (0, _, _, 0, _) -> "fizzbizz"
    (_, 0, 0, _, _) -> "buzzfuzz"
    (_, 0, _, 0, _) -> "buzzbizz"
    (_, _, 0, 0, _) -> "fuzzbizz"
    (0, _, _, _, _) -> "fizz"
    (_, 0, _, _, _) -> "buzz"
    (_, _, 0, _, _) -> "fuzz"
    (_, _, _, 0, _) -> "bizz"
    (_, _, _, _, n) -> to_string(n)
end

fizzbuzz_ = fn n ->
    fizzbuzz_.(rem(n, 3), rem(n, 5), rem(n, 7), rem(n, 11), n)
end

main = fn n ->
    {:ok, file} = File.open("fizzbuzzfuzzbizz_test.csv", [:write])
    Enum.each(1..n, fn n -> IO.binwrite(file, "#{fizzbuzz.(n)},#{fizzbuzz_.(n)}\n") end)
end

main.(10000)
