cmake_minimum_required(VERSION 3.1...3.29)

project(bitemelol VERSION 0.0.1)

set_property(GLOBAL PROPERTY CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PROJECT_SOURCE_FILES
        main.cpp
)

include_directories(include)

find_package(docpp REQUIRED)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE
        docpp::docpp
)
