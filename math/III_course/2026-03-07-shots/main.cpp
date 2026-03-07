#include <iostream>
#include <concepts>

template<std::integral ShotType, std::floating_point ProbType>
bool validate_input(ShotType shots, ProbType probability)
{
  if (probability < 0 || probability > 1)
  {
    std::cout << "Ймовірність повинна належати інтервалу 0 <= p <= 1\n";
    return false;
  }

  if (shots <= 0)
  {
    std::cout << "Кількість пострілів повинна бути додатною\n";
    return false;
  }

  if (shots > std::numeric_limits<ShotType>::max())
  {
    std::cout << "Перевищено максимально допустиме значення\n";
    return false;
  }

  return true;
}

double expected_hits(const int shots, const double probability)
{
  return shots * probability;
}

void prompt_loop()
{
  while (true)
  {
    std::string input;

    std::cout << "Введіть ймовірність або exit для завершення: \n";
    std::cin >> input;

    if (input == "exit")
      break;

    const double probability = std::stod(input);

    std::cout << "Введіть кількість пострілів: \n";
    int shots;
    std::cin >> shots;

    if (!validate_input(shots, probability))
      continue;

    const double result = expected_hits(shots, probability);

    std::cout << "Очікувана кількість влучень: "
              << result << std::endl;
  }
}

int main()
{
  prompt_loop();
  return 0;
}