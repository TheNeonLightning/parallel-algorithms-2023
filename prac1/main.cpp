#include <iostream>
#include <string>
#include <random>

#include <parlay/io.h>
#include <parlay/primitives.h>
#include <parlay/random.h>
#include <parlay/sequence.h>
#include <parlay/internal/get_time.h>

#include "quick_sort_par.h"

// **************************************************************
// Driver
// **************************************************************
int main(int argc, char* argv[]) {
  long n = 100'000'000;
  long max = 10000;
  long runs = 5;
  bool checkCorrectness = false;

  if (argc > 1) {
    try { n = std::stol(argv[1]); }
    catch (...) { std::cout << "argv[1] - expected size of array" << std::endl; return 1; }
  }
  if (argc > 2) {
    try { max = std::stol(argv[2]); }
    catch (...) { std::cout << "argv[2] - expected max value" << std::endl; return 1; }
  }
  if (argc > 3) {
    try { runs = std::stol(argv[3]); }
    catch (...) { std::cout << "argv[3] - expected number of test runs" << std::endl; return 1; }
  }
  if (argc > 4) {
    try { checkCorrectness = std::stol(argv[4]); }
    catch (...) { std::cout << "argv[3] - expected checkCorrectness boolean as number" << std::endl; return 1; }
  }
  std::cout << "Test params: n = " << n
            << "; max = " << max
            << "; runs = " << runs
            << "; checkCorrectness = " << checkCorrectness
            << std::endl;

  parlay::random_generator gen;
  std::uniform_int_distribution<long> dis(0, max);

  for (int run = 0; run < runs; ++run) {
    // generate random long values
    parlay::sequence<long> data = parlay::tabulate(n, [&] (long i) {
      auto r = gen[i * (run + 1)];
      return dis(r);
    });
    parlay::sequence<long> result_seq(data);
    parlay::sequence<long> data_copy(data);

    auto start_seq = std::chrono::steady_clock::now();
    seq::quicksort(result_seq.begin(), result_seq.end(), [](long x, long y) {return x < y;});
    auto stop_seq = std::chrono::steady_clock::now();
    auto time_seq = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(stop_seq - start_seq).count());

    auto start_par = std::chrono::steady_clock::now();
    parlay::sequence<long> result_par = par::quicksort(data_copy);
    auto stop_par = std::chrono::steady_clock::now();
    auto time_par = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(stop_par - start_par).count());

    if (checkCorrectness) {
      for (int index = 1; index < n; ++index) {
        if (result_seq[index - 1] > result_seq[index] ||
            result_par[index - 1] > result_par[index]) {
          std::cout << "Incorrect sorting!";
          return 1;
        }
      }
    }

    std::cout << "time_seq = " << time_seq << "ms; "
              << "time_par = " << time_par << "ms; "
              << "seq/par coef = " << time_seq / time_par << ';'
              << std::endl;
  }

  return 0;
}

