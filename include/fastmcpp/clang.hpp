#pragma once

// Work around Clang quirk: https://github.com/llvm/llvm-project/issues/86077
// This must be included before `<exception>` to work correctly, so effectively before any standard library headers.
#if defined( __APPLE__ ) && defined( __clang__ ) && !defined( __apple_build_version__ )
#include <version>
#undef _LIBCPP_AVAILABILITY_HAS_INIT_PRIMARY_EXCEPTION
#define _LIBCPP_AVAILABILITY_HAS_INIT_PRIMARY_EXCEPTION 0
#endif
