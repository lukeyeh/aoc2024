#ifndef AOC2024_MAP_H_
#define AOC2024_MAP_H_

#include <cstdint>
#include <type_traits>

template <typename K, typename V>
struct KVPair {
  using Key = K;
  using Value = V;
};

// Node in hashmap
template <typename KV, typename Next>
struct Node {
  using KeyValue = KV;
  using NextNode = Next;
};

struct Empty {
  static constexpr int64_t value = 0;
};

// HashMap operations
template <typename Map, typename K>
struct Get {
  using type = Empty;
  static constexpr int64_t value = 0;
};

template <typename KV, typename Next, typename K>
struct Get<Node<KV, Next>, K> {
  using CurrentValue =
      std::conditional_t<std::is_same_v<typename KV::Key, K>,
                         typename KV::Value, typename Get<Next, K>::type>;

  using type = CurrentValue;
  static constexpr int64_t value = CurrentValue::value;
};

template <typename Map, typename K, typename V>
struct InsertMap;

template <typename K, typename V>
struct InsertMap<Empty, K, V> {
  using type = Node<KVPair<K, V>, Empty>;
};

template <typename KV, typename Next, typename K, typename V>
struct InsertMap<Node<KV, Next>, K, V> {
  using type =
      std::conditional_t<std::is_same_v<typename KV::Key, K>,
                         Node<KVPair<K, V>, Next>,
                         Node<KV, typename InsertMap<Next, K, V>::type>>;
};


#endif  // AOC2024_MAP_H_

