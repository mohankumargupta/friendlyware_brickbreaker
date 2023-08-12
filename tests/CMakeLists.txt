# Testing
CPMAddPackage("gh:catchorg/Catch2@3.4.0")

list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)

add_executable(mytests test001.cpp)
target_link_libraries(mytests PRIVATE Catch2::Catch2WithMain)



file(GLOB CATCH2_DLLS CONFIGURE_DEPENDS ${Catch2_BINARY_DIR}/src/*.dll ${Catch2_BINARY_DIR}/src/*.a)
file(COPY ${CATCH2_DLLS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_test(boo mytests)
#catch_discover_tests(mytests)
