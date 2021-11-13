#include <array>     // std::array
#include <iostream>  // std::cout
#include <random>    // std::random_device, std::mt19937_64
#include <algorithm> // std::for_each
#include <thread>    // std::thread

#define TYPE u_short // data type on compile-time
#define SIZE 1000    // size of main array

#define THREAD_COUNT 2

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

// Global variables
std::array<TYPE, SIZE> main_array; // Main array, that filling by random numbers
unsigned long long prime_sum = 0;  // Sums up all prime numbers
int iter = 0;                      // Iterator for main array

int turn;
bool interested[THREAD_COUNT]{};

void PetersonLock(int process)
{
  int other = 1 - process;
  interested[process] = true;
  turn = process;
  while(turn == process && interested[other] == true);
}

void PetersonUnlock(int process)
{
  interested[process] = false;
}

// Function in thread
void PetersonThread(int thread_number)
{
  while(iter < main_array.size())
  {
    PetersonLock(thread_number);
    std::cout << "Thread#" << thread_number << " locked thread_busy, iter = " << iter << std::endl;
    if(iter < main_array.size())
    {
      if (IsPrime(main_array.at(iter)))
      {
        prime_sum = main_array.at(iter);
      }
      ++iter;
    }
    PetersonUnlock(thread_number);
  }
}

int main()
{
  // Fill array with random numbers
  std::random_device rd;     // Instance of an engine
  std::mt19937_64 gen(rd()); // Generates random integers
  std::for_each(main_array.begin(), main_array.end(), [&gen](auto &iter)
                { iter = gen(); }); // Fill each number by generator(gen)

  std::thread thread1 = std::thread(PetersonThread, 0); // Start thread 0
  std::thread thread2 = std::thread(PetersonThread, 1); // Start thread 1

  while(iter < main_array.size()); // Wait until threads finish counting

  std::cout << "Sum: " << prime_sum << std::endl; // Output sum

  // Let thread finish properly
  thread1.join();
  thread2.join();

  return 0;
}