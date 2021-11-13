#include <vector>
#include <array>
#include <iostream>
#include <random>
#include <algorithm>

#define TYPE u_short
#define SIZE 1000000

template<class T>
bool IsPrime(T num)
{
  bool is_prime = true;
  if (num <= 1)
  {
    is_prime = false;
  }
  else
  {
    for (T i = 2; i <= sqrt(num); i++)
    {
      if (num % i == 0)
        is_prime = false;
    }
  }
  return is_prime;
}

std::array<TYPE, SIZE> main_array;

std::vector<TYPE> prime_vector;

int main()
{
  // Fill array with random numbers
  std::random_device rd;     // Instance of an engine
  std::mt19937_64 gen(rd()); // Generates random integers
  std::for_each(main_array.begin(), main_array.end(), [&gen](auto &iter)
                { iter = gen(); });

  for (auto iter : main_array)
  {
    if (IsPrime(iter))
    {
      prime_vector.push_back(iter);
    }
  }

  // Output vector
  unsigned long long prime_sum = std::accumulate(prime_vector.begin(), prime_vector.end(), 0);
  /*
  std::for_each(prime_vector.begin(), prime_vector.end(), [](auto iter)
                { std::cout << iter << " "; });
                std::cout << std::endl
  */
  std::cout << "Sum: " << prime_sum << std::endl;

  return 0;
}