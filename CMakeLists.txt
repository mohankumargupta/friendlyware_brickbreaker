cmake_minimum_required(VERSION 3.27)

project(cmake_sdl)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")


# Download CPM
set(CPM_DOWNLOAD_VERSION 0.38.2)
set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")

if (NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
file(DOWNLOAD 
    https://github.com/cpm-cmake/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake
    ${CPM_DOWNLOAD_LOCATION}
)
endif()
include(${CPM_DOWNLOAD_LOCATION})


#CPMAddPackage("gh:aseprite/freetype2#master")
#if (freetype2_ADDED)
#  add_library(Freetype::Freetype ALIAS freetype)
#endif()

# SDL3
CPMAddPackage("gh:libsdl-org/SDL#main")
CPMAddPackage("gh:libsdl-org/SDL_ttf#main")
CPMAddPackage("gh:libsdl-org/SDL_Mixer#main")




# CPMAddPackage(
#   NAME SDL3_mixer
#   GIT_TAG main
#   GITHUB_REPOSITORY "libsdl-org/SDL_Mixer"
#   DOWNLOAD_ONLY TRUE
# )

#if (SDL3_mixer_ADDED)
  # quick and dirty target definitions
  # might need extra configuration and install commands to work properly
#  file(GLOB SDL3_mixer_SOURCES "${SDL2_mixer_SOURCE_DIR}/*.c")
#  add_library(SDL3_mixer ${SDL3_mixer_SOURCES})
#  target_link_libraries(SDL3_mixer SDL3::SDL3)
#  target_include_directories(SDL3_mixer PUBLIC ${SDL3_mixer_SOURCE_DIR})
#endif()

#add_subdirectory(vendor/SDL EXCLUDE_FROM_ALL)
#add_subdirectory(vendor/SDL_mixer EXCLUDE_FROM_ALL)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE src/main.cpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 SDL3_ttf::SDL3_ttf SDL3_mixer::SDL3_mixer)

# Testing
CPMAddPackage("gh:catchorg/Catch2@3.4.0")
list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
enable_testing()
add_executable(tests tests/test001.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
catch_discover_tests(tests)



