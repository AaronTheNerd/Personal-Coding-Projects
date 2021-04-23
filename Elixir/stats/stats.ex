require Integer
defmodule Stats do
    @moduledoc """
    This is a module which implement some statistical analysis.
    """

    @doc """
        Sums the items in `xs`.

        ## Examples

            iex> Stats.sum([1,2,3,4])
            10

    """
    def sum(xs) when is_list(xs) do
        Enum.reduce(xs, fn(x, s) -> x + s end)
    end

    @doc """
        Calculates the average of `xs`.

        ## Examples

            iex> Stats.avg([1,2,3,4])
            2.5
            
    """
    def avg(xs) when is_list(xs) do
        Stats.sum(xs) / length(xs)
    end

    @doc """
        Finds the min in `xs`.

        ## Examples

            iex> Stats.min([1,2,3,4])
            1
            
    """
    def min(xs) when is_list(xs) do
        Enum.min(xs)
    end

    @doc """
        Finds the max in `xs`.

        ## Examples

            iex> Stats.max([1,2,3,4])
            4
            
    """
    def max(xs) when is_list(xs) do
        Enum.max(xs)
    end

    @doc """
        Finds the range of `xs`.

        ## Examples

            iex> Stats.range([1,2,3,4])
            3
            
    """
    def range(xs) when is_list(xs) do
        xs
        |> Enum.min_max()
        |> (fn {n_, x_} -> x_ - n_ end).()
    end

    @doc """
        Calculates the product of all items in `xs`.

        ## Examples

            iex> Stats.mult([1,2,3,4])
            24
            
    """
    def mult(xs) when is_list(xs) do
        Enum.reduce(xs, fn(x, p) -> x * p end)
    end

    @doc """
        Finds the most frequent item in `xs`.

        ## Examples

            iex> Stats.mode([1,2,3,4,1])
            1
            
    """
    def mode(xs) when is_list(xs) do
        xs
        |> Enum.reduce(%{}, fn(x, m) -> # Turn list into map of frequencies
            Map.update(m, x, 1, fn c -> c + 1 end)
        end)
        |> Enum.reduce(fn ({k, v}, {mk, mv}) -> # Find number, frequency pair with the largest frequency
            if v > mv, do: {k, v}, else: {mk, mv}
        end)
        |> (fn {m, _} -> m end).() # Grab number from number, frequency pair
    end

    @doc """
        Finds the median of `xs`.

        ## Examples

            iex> Stats.median([1,2,3,4])
            2.5
            
    """
    def median(xs) when is_list(xs) do
        len = length(xs)
        xs
        |> Enum.sort()
        |> (fn sorted_xs ->
            case Integer.is_even(len) do
                true -> 
                    Stats.avg([
                        Enum.at(sorted_xs, div(len - 1, 2)),
                        Enum.at(sorted_xs, div(len, 2))
                    ])
                _ -> Enum.at(sorted_xs, div(len - 1, 2))
            end
        end).()
    end
end # endmodule Stats