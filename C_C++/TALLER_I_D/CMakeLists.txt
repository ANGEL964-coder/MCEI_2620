cmake_minimum_required(VERSION 3.10)
project(TallerIntegracion)

# Configurar el estándar de C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Buscar la GNU Scientific Library (GSL)
find_package(GSL REQUIRED)

# Crear el ejecutable (cambia 'ejercicio1.cpp' por el nombre real de tu archivo)
# add_executable(EJERCICIO_1_C EJERCICIO_1_C.cpp)
# add_executable(EJERCICIO_2_C EJERCICIO_2_C.cpp)
add_executable(DIF_NUM DIF_NUM.cpp)

# Enlazar las librerías dinámicas necesarias: gsl, gslcblas y matemáticas (m)
# target_link_libraries(EJERCICIO_1_C GSL::gsl GSL::gslcblas m)
target_link_libraries(DIF_NUM GSL::gsl GSL::gslcblas m)