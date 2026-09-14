cmake_minimum_required(VERSION 3.10)


set(APP_NAME "sistemas_lineales")


project(${APP_NAME})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Eigen3 REQUIRED)
add_executable(${APP_NAME} ${APP_NAME}.cpp)

# Enlaza las librerías
target_link_libraries(${APP_NAME} Eigen3::Eigen)