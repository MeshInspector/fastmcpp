# fastmcpp (MeshInspector fork)

This is MeshInspector's fork of [0xeb/fastmcpp](https://github.com/0xeb/fastmcpp), a C++ port of the Python [fastmcp](https://github.com/jlowin/fastmcp) library. It is used by [MeshLib](https://github.com/MeshInspector/MeshLib).

**For documentation, features, examples and the API, see the [original repository](https://github.com/0xeb/fastmcpp).** This README only lists how the fork differs from it.

## Base

The fork branched from upstream at [`9afa99f`](https://github.com/0xeb/fastmcpp/commit/9afa99f86) (2026-03-18, fastmcpp 3.1.0). Later upstream changes (parity with fastmcp 3.3 / 3.4, streamable-HTTP CORS and DELETE, `FASTMCPP_ENABLE_OPENSSL`, the `_meta` passthrough fix, ...) are **not** merged here.

## Differences from upstream

### Build and packaging
- The library can be installed with CMake: `install()` exports the `fastmcpp::fastmcpp_core` target and a `fastmcppConfig.cmake` for `find_package(fastmcpp)`.
- `nlohmann_json` and `cpp-httplib` are found with `find_package` instead of being fetched with `FetchContent`.
- New option `FASTMCPP_DEPS_ADD_SUBDIRECTORY` (default `OFF`): take both dependencies' headers from sibling directories (`../nlohmann-json`, `../cpp-httplib`) instead of `find_package`.
- The version is hard-coded in `include/fastmcpp/version.hpp`, not passed from CMake.
- The `fastmcpp` CLI executable is built only with `FASTMCPP_BUILD_TESTS`.
- On non-MSVC compilers `fastmcpp_core` is compiled with `-fvisibility=hidden -fvisibility-inlines-hidden`, matching consumers built with hidden visibility (avoids ld64 weak-symbol warnings).

### Compiler compatibility
- Fixes for GCC 11, Visual Studio 2022, older Xcode, Clang and Apple Silicon builds.
- A libc++ workaround (`include/fastmcpp/clang.hpp`), injected as a precompiled header under Clang and AppleClang on Apple platforms.
- Compatibility with newer cpp-httplib versions.

### Behavior
- `std::filesystem` is used through its non-throwing (`std::error_code`) overloads.

### API additions
- `SseServerWrapper::add_route(method, path, handler)` registers custom HTTP routes (`GET`, `POST`, `PUT`, `DELETE`) next to the built-in `/sse` and `/messages` endpoints. It must be called before `start()`. Tested in `tests/server/sse_add_route.cpp`.

## License

Same as upstream, see [LICENSE](LICENSE).
