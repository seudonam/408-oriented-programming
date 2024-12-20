#include <cassert>
#include <utility>

namespace ns {
template <class T> struct shared_ptr {
  T *ptr;
  int *refcnt;
  shared_ptr(T *ptr) : ptr{ptr}, refcnt{new int(1)} {}
  shared_ptr(shared_ptr &other) : ptr{other.ptr}, refcnt{other.refcnt} {
    (*refcnt)++;
  }
  shared_ptr &operator=(shared_ptr &rhs) {
    destruct();
    ptr = rhs.ptr;
    refcnt = rhs.refcnt;
    (*refcnt)++;
    return *this;
  }
  shared_ptr(shared_ptr &&other) = delete;
  shared_ptr &operator=(shared_ptr &&rhs) = delete;
  ~shared_ptr() { destruct(); }
  void destruct() {
    if (*refcnt > 1)
      (*refcnt)--;
    else {
      delete refcnt;
      delete ptr;
    }
  }
};

template <class T> struct unique_ptr {
  T *ptr;
  unique_ptr(T *ptr) : ptr{ptr} {}
  unique_ptr(unique_ptr &) = delete;
  unique_ptr &operator=(unique_ptr &) = delete;
  unique_ptr(unique_ptr &&other) : ptr{other.ptr} { other.ptr = nullptr; };
  unique_ptr &operator=(unique_ptr &&rhs) {
    ptr = rhs.ptr;
    rhs.ptr = nullptr;
    return *this;
  }
  ~unique_ptr() { delete ptr; }
};
} // namespace ns

int main() {
  ns::shared_ptr<int> sp(new int(0));
  assert(*sp.refcnt == 1);
  {
    ns::shared_ptr<int> sq = sp;
    assert(*sq.refcnt == 2);
    ns::shared_ptr<int> sr(sq);
    assert(*sr.refcnt == 3);
  }
  assert(*sp.refcnt == 1);

  ns::unique_ptr<int> up(new int(0));
  ns::unique_ptr<int> uq = std::move(up);
  ns::unique_ptr<int> ur(std::move(uq));
}