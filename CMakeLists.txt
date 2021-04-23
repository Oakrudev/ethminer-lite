cmake_minimum_required(VERSION 3.14)
project(ethminer-lite)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  # Latest release as of April 2021
    URL https://github.com/google/googletest/archive/refs/tags/release-1.10.0.zip
)

INCLUDE_DIRECTORIES(include)
add_library(Keccak src/keccak-1600.cpp)
add_executable(Keccak_test test/keccak_test.cpp)

target_link_libraries(
	Keccak_test
	Keccak
	gtest_main
	gmock_main
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)
gtest_discover_tests(Keccak_test)
