cmake_minimum_required(VERSION 3.17)
project(EvaluationPI C)

set(CMAKE_C_STANDARD 11)

add_executable(EvaluationPI main.c)


find_package(OpenMP)
if(OpenMP_C_FOUND)
    target_link_libraries(EvaluationPI PUBLIC OpenMP::OpenMP_C)
endif()