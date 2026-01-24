#ifndef COUNTER_HEADER
#define COUNTER_HEADER
#include <atomic>
#include <cstddef>

template <typename T> class Counter {
public:
  Counter() { ++count; }
  Counter(const Counter &) { ++count; }
  ~Counter() { --count; }

  static size_t get_count() { return count.load(); }

private:
  static inline std::atomic<size_t> count{0};
};
#endif