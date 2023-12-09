#include <algorithm>
#include <functional>

#include <parlay/parallel.h>
#include <parlay/primitives.h>
#include <parlay/sequence.h>

#include "quick_sort_seq.h"

namespace par {

// **************************************************************
// Parallel Quicksort
// **************************************************************
template <typename Range, typename Less>
void qsort(Range in, Range out, Less less) {
  long n = in.size();
  if (n < 1000) {
    parlay::copy(in, out);
    seq::quicksort(out.begin(), out.end(), less);
  } else {
    auto pivot = parlay::sort(
        parlay::tabulate(101, [&](long i) { return in[i * n / 101]; }))[50];
    auto [x, offsets] = parlay::counting_sort(in, 3, [&](auto k) {
      return less(k, pivot) ? 0u : less(pivot, k) ? 2u : 1u;
    });
    auto& split = x;
    long nl = offsets[1];
    long nm = offsets[2];
    parlay::copy(split.cut(nl, nm), out.cut(nl, nm));
    parlay::par_do([&] { qsort(split.cut(0, nl), out.cut(0, nl), less); },
                   [&] { qsort(split.cut(nm, n), out.cut(nm, n), less); });
  }
}

template <typename Range, typename Less = std::less<>>
auto quicksort(Range& in, Less less = {}) {
  long n = in.size();
  using T = typename Range::value_type;
  parlay::sequence<T> out(n);
  qsort(in.cut(0, n), out.cut(0, n), less);
  return out;
}

}  // namespace par