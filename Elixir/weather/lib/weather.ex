defmodule Weather do
  @moduledoc """
  Documentation for `Weather`.
  """

  defp get_api_key do
    Path.expand("../lib/secret.txt")
    |> File.read()
    |> case do
      {:ok, api_key} -> api_key
      {:error, reason} -> throw(reason)
    end
  end

  defp get_time(unix_timestamp) do
    {:ok, time} = DateTime.from_unix(unix_timestamp)
    time
    |> DateTime.to_time()
    |> (fn time -> "#{time.hour|>Integer.to_string()|>String.pad_leading(2,"0")}:#{time.minute|>Integer.to_string()|>String.pad_leading(2,"0")}:#{time.second|>Integer.to_string()|>String.pad_leading(2,"0")}" end).()
  end

  defp parse_response_body(body) do
    {:ok, decoded_body} = Poison.decode(body)
    main = decoded_body["main"]
    wind = decoded_body["wind"]
    rain = decoded_body["rain"]
    snow = decoded_body["snow"]
    sys = decoded_body["sys"]
    """

    ==================================================
    Current weather in #{decoded_body["name"]}

    Current Temperature: #{main["temp"]} degrees
    Feels Like: #{main["feels_like"]} degrees
    Minimum Temperature: #{main["temp_min"]} degrees
    Maximum Temperature: #{main["temp_max"]} degrees

    Wind Speed: #{wind["speed"]} mph
    """
    |> (fn
      s, g when g != nil -> s <> "Wind Gusts: #{g} mph\n"
      s, _ -> s
    end).(wind["gust"])
    |> (fn
      s, r when r != nil -> s <> "\nHourly Rain Fall: #{r}\n"
      s, _ -> s
    end).(rain["1h"])
    |> (fn
      s, r when r != nil -> s <> "Hourly Snow Fall: #{r}\n"
      s, _ -> s
    end).(snow["1h"])
    |> (fn
      s, t -> s <> "\nSunrise: #{get_time(t)}\n"
    end).(sys["sunrise"] + decoded_body["timezone"])
    |> (fn
      s, t -> s <> "Sunset: #{get_time(t)}\n"
    end).(sys["sunset"] + decoded_body["timezone"])
    |> (fn 
      s -> s <> "==================================================\n"
    end).()
  end

  defp handle_httpoison_response(response) do
    case response do
      {:ok, %HTTPoison.Response{status_code: 200, body: body}} -> body
      {:ok, %HTTPoison.Response{status_code: 404}} -> throw(404)
      {:error, reason} -> throw(reason)
    end
  end

  @doc"""
  Gets a parsed string version of the current weather from the city name
  """
  def get_current_weather_by_city_name(city_name) do
    HTTPoison.get("api.openweathermap.org/data/2.5/weather?q=#{city_name}&units=imperial&appid=#{get_api_key()}")
    |> handle_httpoison_response()
    |> parse_response_body()
  end

  @doc"""
  Gets a parsed string version of the current weather from the zip code
  """
  def get_current_weather_by_zip_code(zip_code) do
    HTTPoison.get("api.openweathermap.org/data/2.5/weather?zip=#{zip_code},us&units=imperial&appid=#{get_api_key()}")
    |> handle_httpoison_response()
    |> parse_response_body()
  end
end
