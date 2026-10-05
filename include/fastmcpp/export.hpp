#pragma once

// Marks the API exported from the fastmcpp_core DLL (CMake defines fastmcpp_core_EXPORTS while
// building it as a shared library); other platforms keep their default symbol visibility.
#if defined(_WIN32) && defined(fastmcpp_core_EXPORTS)
#define FASTMCPP_API __declspec(dllexport)
#else
#define FASTMCPP_API
#endif
