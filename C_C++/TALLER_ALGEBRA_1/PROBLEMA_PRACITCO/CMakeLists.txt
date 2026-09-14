cmake_minimum_required(VERSION 3.10)

# 1. PON AQUÍ EL NOMBRE DE TU ARCHIVO (sin el .cpp)
set(APP_NAME "resultados")

project(${APP_NAME})

# C++14 es suficiente para manejar Eigen y la lectura de archivos (fstream)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Buscar Eigen3
find_package(Eigen3 REQUIRED)

# Crear el ejecutable
add_executable(${APP_NAME} ${APP_NAME}.cpp)

# Enlazar la librería
target_link_libraries(${APP_NAME} Eigen3::Eigen)