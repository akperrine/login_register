cmake_minimum_required(VERSION 3.13.4)

project(LoginRegister)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} 
    PUBLIC external/SqlApi/include
)
target_link_directories(${PROJECT_NAME} 
PRIVATE ${CMAKE_SOURCE_DIR}/external/SqlApi/
PRIVATE ${CMAKE_SOURCE_DIR}/external/LibPq
)
target_link_libraries(${PROJECT_NAME} sqlapi pq)