cmake_minimum_required(VERSION 3.1)

project(qotd CXX C)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

find_package(Threads REQUIRED)

add_library(${PROJECT_NAME}_core src/client_socket.cpp src/server.cpp)
target_include_directories(${PROJECT_NAME}_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME}_core ${CMAKE_THREAD_LIBS_INIT})

add_executable(${PROJECT_NAME} src/qotd.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_core)

add_executable(${PROJECT_NAME}_echo src/echo.cpp)
target_link_libraries(${PROJECT_NAME}_echo ${PROJECT_NAME}_core)

