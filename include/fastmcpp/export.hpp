#pragma once

// FASTMCPP_API: classes and functions defined in src/, exported from the shared library.
// FASTMCPP_CLASS: header-only types whose typeinfo/vtable crosses the library boundary
// (exceptions, interfaces); MSVC compares typeinfo by name, so it is empty there.
#if defined(_WIN32)
#if defined(fastmcpp_core_EXPORTS)
#define FASTMCPP_API __declspec(dllexport)
#else
#define FASTMCPP_API
#endif
#define FASTMCPP_CLASS
#elif defined(FASTMCPP_SHARED)
#define FASTMCPP_API __attribute__((visibility("default")))
#ifdef __clang__
#define FASTMCPP_CLASS __attribute__((type_visibility("default")))
#else
#define FASTMCPP_CLASS __attribute__((visibility("default")))
#endif
#else
#define FASTMCPP_API
#define FASTMCPP_CLASS
#endif
