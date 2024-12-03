load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
  name = "com_google_absl",
  urls = ["https://github.com/abseil/abseil-cpp/archive/14b8a4eac3e5a7b97ba4cc7b7dadf2a85aae8215.zip"],
  strip_prefix = "abseil-cpp-14b8a4eac3e5a7b97ba4cc7b7dadf2a85aae8215",
  sha256 = "c3b96c590e2dd090443288142e40e750d115be540cde124a7aa57da16301ee0e",
)

http_archive(
  name = "bazel_skylib",
  urls = ["https://github.com/bazelbuild/bazel-skylib/releases/download/1.2.1/bazel-skylib-1.2.1.tar.gz"],
  sha256 = "f7be3474d42aae265405a592bb7da8e171919d74c16f082a5457840f06054728",
)

http_archive(
  name = "com_google_googletest",
  urls = ["https://github.com/google/googletest/archive/5df0241ea4880e5a846775d3efc8b873f7b36c31.zip"],
  strip_prefix = "googletest-5df0241ea4880e5a846775d3efc8b873f7b36c31",
  sha256 = "ab8890fba4068efad5edd214dfb46c6b0c6af84feef06dde433d5607334de718"
)

http_archive(
    name = "com_github_google_benchmark",
    urls = ["https://github.com/google/benchmark/archive/3d85343d65832d05b4dcd6666640e0e38b981c33.zip"],
    strip_prefix = "benchmark-3d85343d65832d05b4dcd6666640e0e38b981c33",
    sha256 = "bde8a76919b57d5ddea96c60f7fc32a42b2158f53f95fc9bc3a3d8889ee30416"
)

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")


# Hedron's Compile Commands Extractor for Bazel
# https://github.com/hedronvision/bazel-compile-commands-extractor
http_archive(
    name = "hedron_compile_commands",
    url = "https://github.com/hedronvision/bazel-compile-commands-extractor/archive/33658bab23a4858b513d767480b43d3d8fb6a3d1.tar.gz",
    strip_prefix = "bazel-compile-commands-extractor-33658bab23a4858b513d767480b43d3d8fb6a3d1",
    sha256 = "d699c5e3a82b811d7051e833b1808358256a9c52285a43e6a3abb76c809ab03f"
)
load("@hedron_compile_commands//:workspace_setup.bzl", "hedron_compile_commands_setup")
hedron_compile_commands_setup()
load("@hedron_compile_commands//:workspace_setup_transitive.bzl", "hedron_compile_commands_setup_transitive")
hedron_compile_commands_setup_transitive()
load("@hedron_compile_commands//:workspace_setup_transitive_transitive.bzl", "hedron_compile_commands_setup_transitive_transitive")
hedron_compile_commands_setup_transitive_transitive()
load("@hedron_compile_commands//:workspace_setup_transitive_transitive_transitive.bzl", "hedron_compile_commands_setup_transitive_transitive_transitive")
hedron_compile_commands_setup_transitive_transitive_transitive()
