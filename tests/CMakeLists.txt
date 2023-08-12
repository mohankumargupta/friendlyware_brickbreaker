# Testing
CPMAddPackage("gh:catchorg/Catch2@3.4.0")

#list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)
include(CTest)
#include(Catch)

add_executable(mytests test001.cpp)
target_link_libraries(mytests PRIVATE Catch2::Catch2WithMain)


#catch_discover_tests(mytests)