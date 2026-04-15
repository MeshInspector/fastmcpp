include(CMakeFindDependencyMacro)

find_dependency(httplib)
find_dependency(nlohmann_json)

include("${CMAKE_CURRENT_LIST_DIR}/fastmcpp_core.cmake")
