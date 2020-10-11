cmake_minimum_required(VERSION 3.16.3)
project(HW-1)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror ")

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

set(INCLUDES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/project/include)
set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/project/src)
set(TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/project/tests)

include_directories("${GTEST_INCLUDE_DIRS}")
include_directories(${SOURCES_DIR})


add_executable(main.out
        ${SOURCES_DIR}/main.c
        ${SOURCES_DIR}/music.c
        ${INCLUDES_DIR}/music.h)
target_include_directories(main.out PUBLIC ${INCLUDES_DIR})

add_executable(tests.out
        ${TESTS_DIR}/tests.cpp
        ${SOURCES_DIR}/music.c
        ${INCLUDES_DIR}/music.h)
target_include_directories(tests.out PUBLIC ${INCLUDES_DIR})

target_link_libraries(tests.out
        ${GTEST_LIBRARIES}
        Threads::Threads)

enable_testing()
add_test(tests "./tests")
