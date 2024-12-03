cc_library(
  name = "list",
  hdrs = ["list.h"],
)

cc_library(
  name = "insertion_sort",
  deps = [":list"],
  hdrs = ["insertion_sort.h"],
)

cc_library(
  name = "map",
  hdrs = ["map.h"],
)

cc_binary(
  name = "day1_main",
  deps = [
    ":map",
    ":list",
    ":insertion_sort",
  ],
  srcs = ["day1_main.cc"],
)
