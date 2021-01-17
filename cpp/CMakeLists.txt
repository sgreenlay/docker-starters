cmake_minimum_required (VERSION 3.8)
project (App)

add_executable(app main.cpp)

find_package(zstd CONFIG REQUIRED)
add_library(zstd INTERFACE IMPORTED)
add_library(libzstd INTERFACE IMPORTED)

target_link_libraries(app PRIVATE libzstd)

find_package(proxygen CONFIG REQUIRED)
target_link_libraries(app PRIVATE proxygen::proxygen proxygen::proxygenhttpserver)