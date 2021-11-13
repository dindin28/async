#include <array>     // std::array
#include <iostream>  // std::cout
#include <random>    // std::random_device, std::mt19937_64
#include <algorithm> // std::for_each
#include <thread>    // std::thread

#define TYPE u_short // Define common data type
#define SIZE 10      // Size of main array

// Templated function to check if number is prime
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

std::array<TYPE, SIZE> main_array; // Main array, that filling by random numbers
unsigned long long prime_sum = 0;  // Sums up all prime numbers
bool turn = true;                  // Turn swither for thread
int iter = 0;                      // Iterator for main array

void StrictThread(bool control_boolean)
{
  while(iter < main_array.size())
  {
    while(turn != control_boolean) {}
    std::cout << "Im in " << ((control_boolean) ? ("true ") : ("false "))
              << "controlled thread with i = " << iter << std::endl;
    if(iter < main_array.size()){
      if (IsPrime(main_array.at(iter)))
      {
        prime_sum = main_array.at(iter);
      }
      ++iter;
      turn = !control_boolean;
    }
  }
}

int main()
{
  // Fill array with random numbers
  std::random_device rd;     // Instance of an engine
  std::mt19937_64 gen(rd()); // Generates random integers
  std::for_each(main_array.begin(), main_array.end(), [&gen](auto &iter)
                { iter = gen(); }); // Fill each number by generator(gen)

  std::thread thread1 = std::thread(StrictThread, true);  // Start thread 1
  std::thread thread2 = std::thread(StrictThread, false); // Start thread 2

  // Let threads finish properly
  thread1.join();
  thread2.join();

  while(iter < main_array.size()); // Wait until threads finish counting

  std::cout << "Sum: " << prime_sum << std::endl; // Output sum

  return 0;
}