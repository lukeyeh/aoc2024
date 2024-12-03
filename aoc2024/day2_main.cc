#include "list.h"

template <typename List>
struct CheckAdjacentDiffs;

template <>
struct CheckAdjacentDiffs<Nil> {
  static constexpr bool value = true;
};

template <typename H>
struct CheckAdjacentDiffs<Cons<H, Nil>> {
  static constexpr bool value = true;
};

template <typename H1, typename H2, typename T>
struct CheckAdjacentDiffs<Cons<H1, Cons<H2, T>>> {
  static constexpr int64_t diff =
      H1::value > H2::value ? H1::value - H2::value : H2::value - H1::value;
  static constexpr bool valid = diff >= 1 && diff <= 3;
  static constexpr bool value = valid && CheckAdjacentDiffs<Cons<H2, T>>::value;
};

enum class Trend { Increasing = 0, Decreasing = 1, Neither = 2 };

template <typename List>
struct IsIncreasing;

template <>
struct IsIncreasing<Nil> {
  static constexpr bool value = true;
};

template <typename H>
struct IsIncreasing<Cons<H, Nil>> {
  static constexpr bool value = true;
};

template <typename H1, typename H2, typename T>
struct IsIncreasing<Cons<H1, Cons<H2, T>>> {
  static constexpr bool value =
      (H1::value < H2::value) && IsIncreasing<Cons<H2, T>>::value;
};

template <typename List>
struct IsDecreasing;

template <>
struct IsDecreasing<Nil> {
  static constexpr bool value = true;
};

template <typename H>
struct IsDecreasing<Cons<H, Nil>> {
  static constexpr bool value = true;
};

template <typename H1, typename H2, typename T>
struct IsDecreasing<Cons<H1, Cons<H2, T>>> {
  static constexpr bool value =
      (H1::value > H2::value) && IsDecreasing<Cons<H2, T>>::value;
};

template <typename List>
struct GetTrend {
  static constexpr Trend value = IsIncreasing<List>::value   ? Trend::Increasing
                                 : IsDecreasing<List>::value ? Trend::Decreasing
                                                             : Trend::Neither;
};

template <typename List1, typename List2>
struct CheckLists {
  static constexpr bool list1_trend =
      GetTrend<List1>::value == Trend::Increasing ||
      GetTrend<List1>::value == Trend::Decreasing;

  static constexpr bool list2_trend =
      GetTrend<List2>::value == Trend::Increasing ||
      GetTrend<List2>::value == Trend::Decreasing;

  static constexpr bool list1_diffs = CheckAdjacentDiffs<List1>::value;
  static constexpr bool list2_diffs = CheckAdjacentDiffs<List2>::value;

  static constexpr bool value =
      (list1_trend && list1_diffs) && (list2_trend && list2_diffs);
};

template <typename Lists>
struct CountValidLists {
  static constexpr int64_t value = 0;
};

template <typename List, typename T>
struct CountValidLists<Cons<List, T>> {
  static constexpr bool valid = (GetTrend<List>::value == Trend::Increasing ||
                                 GetTrend<List>::value == Trend::Decreasing) &&
                                CheckAdjacentDiffs<List>::value;

  static constexpr int64_t value = (valid ? 1 : 0) + CountValidLists<T>::value;
};

int main(int argc, char* argv[]) {
  using TestLists = MakeList<            //
      MakeIntList<7, 6, 4, 2, 1>::type,  //
      MakeIntList<1, 2, 7, 8, 9>::type,  //
      MakeIntList<9, 7, 6, 2, 1>::type,  //
      MakeIntList<1, 3, 2, 4, 5>::type,  //
      MakeIntList<8, 6, 4, 4, 1>::type,  //
      MakeIntList<1, 3, 6, 7, 9>::type   //
      >::type;
  static_assert(CountValidLists<TestLists>::value == 2);
}
