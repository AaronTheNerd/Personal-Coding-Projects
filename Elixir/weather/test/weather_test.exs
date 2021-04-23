defmodule WeatherTest do
  use ExUnit.Case
  doctest Weather

  test "gets current weather by city" do
    IO.puts Weather.get_current_weather_by_city_name("Cincinnati")
    IO.puts Weather.get_current_weather_by_city_name("New York City")
  end

  test "gets current weather by zip code" do
    IO.puts Weather.get_current_weather_by_zip_code(29212)
  end

end
