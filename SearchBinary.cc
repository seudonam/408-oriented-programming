#include "vector.hh"
#include <algorithm>
#include <cassert>
#include <concepts>
#include <cstdlib>
#include <ctime>
#include <print>

// 折半查找
template <typename compar>
  requires std::totally_ordered<compar>
int bisectionSearch(const compar &key, const ns::vector<compar> &a) {
  assert(std::ranges::is_sorted(a));
  int lo(0), hi(a.size() - 1);
  while (lo <= hi) {
    int mid{lo + (hi - lo) / 2};
    if (key < a[mid])
      hi = mid - 1;
    else if (key > a[mid])
      lo = mid + 1;
    // key == a[mid]
    else
      return mid;
  }
  return -1;
}

// 线性查找
template <typename compar>
int linearSearch(const compar &key, const ns::vector<compar> &a) {
  for (int i(0), sz(a.size()); i < sz; ++i)
    if (key == a[i])
      return i;
  return -1;
}

// 大于等于查找目标的最小元素
template <typename compar>
  requires std::totally_ordered<compar>
int rightBisection(const compar &key, const ns::vector<compar> &a) {
  assert(std::ranges::is_sorted(a));
  int lo(0), hi(a.size() - 1);
  while (lo < hi) {
    int mid{(lo + hi) >> 1};
    if (key <= a[mid])
      hi = mid;
    // key > a[mid]
    else
      lo = mid + 1;
  }
  assert(lo == hi);
  return hi;
}

// 小于等于查找目标的最大元素
template <typename compar>
  requires std::totally_ordered<compar>
int leftBisection(const compar &key, const ns::vector<compar> &a) {
  assert(std::ranges::is_sorted(a));
  int lo(0), hi(a.size() - 1);
  while (lo < hi) {
    int mid = (lo + hi + 1) >> 1;
    if (key >= a[mid])
      lo = mid;
    // key < a[mid]
    else
      hi = mid - 1;
  }
  assert(lo == hi);
  return lo;
}

int main() {
  std::srand(std::time(nullptr));
  ns::vector<int> vec{1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
  int num = std::rand() % vec.back();
  std::print("number\t{}\n", num);
  for (auto &e : vec)
    std::print("{}\t", e);
  std::print("\n");

  int r{bisectionSearch<int>(num, vec)};
  if (r != -1) {
    for (int i = 0; i < r; ++i)
      std::print("\t");
    std::print("{}", vec[r]);
  } else
    std::print("{}", r);
  std::print("\n");

  int s{linearSearch<int>(num, vec)};
  if (s != -1) {
    for (int i = 0; i < s; ++i)
      std::print("\t");
    std::print("{}", vec[s]);
  } else
    std::print("{}", r);
  std::print("\n");

  int t{rightBisection<int>(num, vec)};
  for (int i = 0; i < t; ++i)
    std::print("\t");
  std::print("{}", vec[t]);
  std::print("\n");

  int u{leftBisection<int>(num, vec)};
  for (int i = 0; i < u; ++i)
    std::print("\t");
  std::print("{}", vec[u]);
  std::print("\n");
}