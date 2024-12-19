#include "vector.hh"
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <print>

template <class T> int FSearch(const T &key, const ns::vector<T> &A) {
  assert(std::ranges::is_sorted(A));
  int lo = 0, hi = A.size() - 1;
  int alpha = 0, beta = 1, x;
  do {
    x = alpha + beta;
    alpha = beta;
    beta = x;
  } while (x < hi);

  while (lo <= hi) {
    while (beta > hi - lo) {
      x = beta - alpha;
      beta = alpha;
      alpha = x;
    }
    int pivot = lo + beta;
    if (key < A[pivot])
      hi = pivot - 1;
    else if (key > A[pivot])
      lo = pivot + 1;
    else
      return pivot;
  }
  return -1;
}

int main() {
  std::srand(std::time(nullptr));
  ns::vector<int> vec{1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
  int num = std::rand() % vec.back();
  std::print("number\t{}\n", num);
  for (auto &e : vec)
    std::print("{}\t", e);
  std::print("\n");

  int r{FSearch<int>(num, vec)};
  if (r != -1) {
    for (int i = 0; i < r; ++i)
      std::print("\t");
    std::print("{}", vec[r]);
  } else
    std::print("{}", r);
  std::print("\n");
}