cmake_minimum_required(VERSION 3.10)
project(IFP)


set(CMAKE_CXX_STANDARD 11)
list(APPEND CMAKE_PREFIX_PATH "/opt/root")
find_package(ROOT REQUIRED COMPONENTS MathCore Hist Tree)
include(${ROOT_USE_FILE})

add_executable(Kondesator main.cpp kondensator.cpp)

target_link_libraries(Kondesator ${ROOT_LIBRARIES})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)