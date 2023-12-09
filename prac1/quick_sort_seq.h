#include <iostream>

namespace seq {

// **************************************************************
// Sequential Quicksort
// **************************************************************
template <typename RandomIt, typename Less>
RandomIt partition(RandomIt first, RandomIt last, Less less) {
  auto pivot = std::prev(last, 1);
  auto i = first;
  for (auto j = first; j != pivot; ++j) {
    // bool format
    if (less(*j, *pivot)) {
      std::swap(*i++, *j);
    }
  }
  std::swap(*i, *pivot);
  return i;
}

template <typename RandomIt, typename Less = std::less<>>
void quicksort(RandomIt first, RandomIt last, Less less = {}) {
  if (std::distance(first, last) > 1) {
    RandomIt bound = seq::partition(first, last, less);
    quicksort(first, bound, less);
    quicksort(bound + 1, last, less);
  }
}

}  // namespace seq