cmake_minimum_required(VERSION 3.12)
project(hw2 C)
project(tests CXX)


set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
# set(CMAKE_C_FLAGS "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")
# set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")
set(THREADS_PREFER_PTHREAD_FLAG ON)


add_compile_options(--coverage)
add_link_options(--coverage)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)







set(INPUT input.c)
add_library(input_lib STATIC ${INPUT})

set(NAIVE_TRANSPOSE naive_transpose.c)
add_library(naive_transpose_lib STATIC ${NAIVE_TRANSPOSE})

set(PARALLEL_TRANSPOSE parallel_transpose.c)
add_library(parallel_transpose_lib MODULE ${PARALLEL_TRANSPOSE})




find_package(Threads REQUIRED)
add_executable(hw2 main.c)
target_link_libraries(hw2 input_lib naive_transpose_lib dl)


find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


add_executable(test_input test_input.cpp)
target_link_libraries(test_input input_lib ${GTEST_LIBRARIES} pthread)


add_executable(test_naive_transpose test_naive_transpose.cpp)
target_link_libraries(test_naive_transpose naive_transpose_lib ${GTEST_LIBRARIES} pthread)



add_executable(test_parallel_transpose test_parallel_transpose.cpp)
target_link_libraries(test_parallel_transpose dl ${GTEST_LIBRARIES} pthread)
# add_executable(test_naive_transpose naive_transpose_lib test_naive_transpose.cpp)
# target_link_libraries(test_naive_transpose ${GTEST_LIBRARIES} pthread)


# # add_executable(tests test_input.cpp test_naive_transpose.cpp)
# # target_link_libraries(tests ${GTEST_LIBRARIES} pthread)
# # target_link_libraries(tests input dl)




# enable_testing()
# add_test(test_input ${EXECUTABLE_OUTPUT_PATH}/test_input)
# add_test(test_naive_transpose ${EXECUTABLE_OUTPUT_PATH}/test_naive_transpose)

# add_definitions(-fprofile-arcs -ftest-coverage)
# target_link_libraries(test_input -fprofile-arcs)
# target_link_libraries(test_naive_transpose -fprofile-arcs)

