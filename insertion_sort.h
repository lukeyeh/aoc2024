#ifndef AOC2024_INSERTION_SORT_H_
#define AOC2024_INSERTION_SORT_H_

#include "list.h"

template <typename X, typename List>
struct Insert;

template <typename X>
struct Insert<X, Nil> {
  using type = Cons<X, Nil>;
};

template <typename X, typename H, typename T>
struct Insert<X, Cons<H, T>> {
  using type = std::conditional_t<(X::value <= H::value), Cons<X, Cons<H, T>>,
                                  Cons<H, typename Insert<X, T>::type>>;
};

template <typename List>
struct Sort;

template <>
struct Sort<Nil> {
  using type = Nil;
};

template <typename H, typename T>
struct Sort<Cons<H, T>> {
  using SortedTail = typename Sort<T>::type;
  using type = typename Insert<H, SortedTail>::type;
};

#endif  // AOC2024_INSERTION_SORT_H_
