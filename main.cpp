#include <vector>
#include <array>
#include <iostream>
#include <random>
#include <algorithm>
#include <thread>

#define TYPE u_short
#define SIZE 10

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
unsigned long long prime_sum = 0;

bool turn = true;
int i = 0;

void Thread(bool control_boolean)
{
  while(i < main_array.size() - 1)
  {
    while(turn != control_boolean && i < main_array.size()) {}
    std::cout << "Im in " << ((control_boolean) ? ("true ") : ("false ")) << "controlled thread with i = " << i << std::endl;
    if (IsPrime(main_array.at(i)))
    {
      prime_sum = main_array.at(i);
    }
    ++i;
    turn = !control_boolean;
  }
}

int main()
{
  // Fill array with random numbers
  std::random_device rd;     // Instance of an engine
  std::mt19937_64 gen(rd()); // Generates random integers
  std::for_each(main_array.begin(), main_array.end(), [&gen](auto &iter)
                { iter = gen(); });

  std::thread thread1 = std::thread(Thread, true);
  std::thread thread2 = std::thread(Thread, false);

  thread1.join();
  thread2.join();

  while(i < main_array.size());

  std::cout << "Sum: " << prime_sum << std::endl;

  return 0;
}