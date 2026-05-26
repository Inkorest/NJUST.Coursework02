cmake_minimum_required(VERSION 3.15)
project(MyProject C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-Wall -Wextra -g)
else()
    add_compile_options(-O3)
endif()

file(GLOB SRC_LIST CONFIGURE_DEPENDS "src/*.c")

add_executable(StudentManageSystem ${SRC_LIST})

target_include_directories(StudentManageSystem PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
