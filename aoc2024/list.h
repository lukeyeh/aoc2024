#ifndef AOC2024_LIST_H_
#define AOC2024_LIST_H_

#include <cstddef>
#include <cstdint>
#include <type_traits>

struct Nil;

template <typename H, typename T>
struct Cons {
  using Head = H;
  using Tail = T;
};

template <typename... Ts>
struct MakeList;

template <>
struct MakeList<> {
  using type = Nil;
};

template <typename T, typename... Rest>
struct MakeList<T, Rest...> {
  using type = Cons<T, typename MakeList<Rest...>::type>;
};

template <typename List>
struct Length;

template <>
struct Length<Nil> {
  static constexpr size_t value = 0;
};

template <typename H, typename T>
struct Length<Cons<H, T>> {
  static constexpr size_t value = 1 + Length<T>::value;
};

template <typename List, size_t N>
struct At;

template <typename H, typename T>
struct At<Cons<H, T>, 0> {
  using type = H;
};

template <typename H, typename T, std::size_t N>
struct At<Cons<H, T>, N> {
  using type = typename At<T, N - 1>::type;
};

template <int64_t N>
using Int = std::integral_constant<int64_t, N>;

template <int64_t... Ns>
struct MakeIntList;

template <>
struct MakeIntList<> {
  using type = Nil;
};

template <int64_t N, int64_t... Rest>
struct MakeIntList<N, Rest...> {
  using type = Cons<Int<N>, typename MakeIntList<Rest...>::type>;
};

#endif  // AOC2024_LIST_H_
