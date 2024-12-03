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

// Check if list is valid after removing one element
template <typename List>
struct CheckListWithRemoval {
  template <size_t N, typename L>
  struct CheckRemovalAt {
    using RemovedList = typename RemoveAt<L, N>::type;
    static constexpr bool value =
        (GetTrend<RemovedList>::value == Trend::Increasing ||
         GetTrend<RemovedList>::value == Trend::Decreasing) &&
        CheckAdjacentDiffs<RemovedList>::value;
  };

  template <size_t N>
  struct CheckAllRemovals {
    static constexpr bool value =
        (N >= Length<List>::value)
            ? false
            : CheckRemovalAt<N, List>::value || CheckAllRemovals<N + 1>::value;
  };

  template <>
  struct CheckAllRemovals<Length<List>::value> {
    static constexpr bool value = false;
  };

  static constexpr bool value = CheckAllRemovals<0>::value;
};

template <typename Lists>
struct CountValidListsWithRemovals {
  static constexpr int64_t value = 0;
};

template <typename List, typename T>
struct CountValidListsWithRemovals<Cons<List, T>> {
  static constexpr bool valid = CheckListWithRemoval<List>::value;
  static constexpr int64_t value =
      (valid ? 1 : 0) + CountValidListsWithRemovals<T>::value;
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
  static_assert(CountValidListsWithRemovals<TestLists>::value == 4);
}
