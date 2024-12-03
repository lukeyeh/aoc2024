#include "list.h"
#include "insertion_sort.h"
#include "map.h"

template <typename List1, typename List2>
struct Difference;

template <>
struct Difference<Nil, Nil> {
  using type = Nil;
};

template <typename H1, typename T1, typename H2, typename T2>
struct Difference<Cons<H1, T1>, Cons<H2, T2>> {
  using type =
      Cons<Int<H1::value - H2::value>, typename Difference<T1, T2>::type>;
};

template <typename List>
struct Sum;

template <>
struct Sum<Nil> {
  static constexpr int64_t value = 0;
};

template <typename H, typename T>
struct Sum<Cons<H, T>> {
  static constexpr int64_t value = H::value + Sum<T>::value;
};

template <typename List1, typename List2>
struct DiffSum {
  using SortedList1 = typename Sort<List1>::type;
  using SortedList2 = typename Sort<List2>::type;
  using Diffs = typename Difference<SortedList1, SortedList2>::type;
  static constexpr int64_t value = Sum<Diffs>::value;
};

template <typename List1, typename List2>
struct Distance {
  using SortedList1 = typename Sort<List1>::type;
  using SortedList2 = typename Sort<List2>::type;
  using Diffs = typename Difference<SortedList1, SortedList2>::type;

  template <typename List>
  struct AbsSum {
    static constexpr int64_t value =
        List::Head::value < 0
            ? -List::Head::value + AbsSum<typename List::Tail>::value
            : List::Head::value + AbsSum<typename List::Tail>::value;
  };

  template <>
  struct AbsSum<Nil> {
    static constexpr int64_t value = 0;
  };

  static constexpr int64_t value = AbsSum<Diffs>::value;
};

template <typename List, typename Map = Empty>
struct CountFrequency;

template <typename Map>
struct CountFrequency<Nil, Map> {
  using type = Map;
};

template <typename H, typename T, typename Map>
struct CountFrequency<Cons<H, T>, Map> {
  using CurrentCount = Get<Map, H>;
  using NewCount = std::conditional_t<std::is_same_v<CurrentCount, Empty>,
                                      Int<1>, Int<CurrentCount::value + 1>>;
  using UpdatedMap = typename InsertMap<Map, H, NewCount>::type;
  using type = typename CountFrequency<T, UpdatedMap>::type;
};

template <typename List1, typename List2>
struct SimilarityScore {
  using RightFreqMap = typename CountFrequency<List2>::type;

  template <typename List>
  struct Calculate;

  template <>
  struct Calculate<Nil> {
    static constexpr int64_t value = 0;
  };

  template <typename H, typename T>
  struct Calculate<Cons<H, T>> {
    using CurrentCount = Get<RightFreqMap, H>;
    static constexpr int64_t freq =
        std::is_same_v<CurrentCount, Empty> ? 0 : CurrentCount::value;
    static constexpr int64_t value = (H::value * freq) + Calculate<T>::value;
  };

  static constexpr int64_t value = Calculate<List1>::value;
};


int main() {
  using List1 = MakeIntList<1,2,3>::type;
  using List2 = MakeIntList<2,4,5>::type;
  static_assert(Distance<List1, List2>::value == 5);
  static_assert(SimilarityScore<List1, List2>::value == 2);
  return 0;
}
