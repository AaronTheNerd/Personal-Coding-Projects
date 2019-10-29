def main():
  weeks = [39.86, 33.11, 30.45, 36.39, 33.10, 0, 7.94, 36.49, 37.59, 27.36, 32.54, 25.83, 31.14, 26.34, 25.86, 28.21, 26.08, 27.65, 27.08, 8.00, 10.26, 18.46, 17.87, 25.73, 26.37, 9.30, 37.94, 22.71, 0, 33.56, 28.47, 29.19, 13.36, 22.35, 22.07, 21.90, 21.17, 22.83, 29.66, 21.53, 21.37, 21.89, 22.34, 24.16, 14.26, 17.31, 0.00, 37.79, 32.39, 26.65, 27.97, 0.00, 31.68, 32.10, 38.90, 32.04, 0.00, 30.71, 37.42]
  hour_average = 100
  week = 0
  while hour_average >= 10:
    hour_average = year_average(weeks)
    if week % 4 == 0:
      weeks.append(8)
    else:
      weeks.append(0)
    week = week + 1
  print("You made it %d weeks" %week)

def year_average(weeks):
  total_hours = 0
  for week in weeks[-52:]:
    total_hours += week
  return total_hours / 52

if __name__ == "__main__":
  main()