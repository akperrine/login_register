cmake_minimum_required(VERSION 3.13.4)

project(LoginRegister)

add_executable(${PROJECT_NAME} main.cpp)

set(POSTGRESQL_DIR ${PostgreSQL_INCLUDE_DIR})

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${POSTGRESQL_DIR}/include
)
target_link_directories(${PROJECT_NAME} 
PRIVATE ${POSTGRESQL_DIR}/lib
)
target_link_libraries(${PROJECT_NAME} pq )