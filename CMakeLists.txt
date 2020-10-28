cmake_minimum_required (VERSION 2.6)

# Enable C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project("seam-carving")

set(CMAKE_CXX_FLAGS "-Wall -Wshadow -Weffc++")
SET(OpenCV_DIR /home/ecirtam/local-dev/opencv-4.5.0/lib/cmake/opencv4)

#--- Libraries & includes ---
find_package(OpenCV REQUIRED)
include_directories("include", ${OpenCV_INCLUDE_DIRS})

#--- Targets ---

set(exe ${PROJECT_NAME})

file(GLOB sources src/*.cpp)
file(GLOB includes include/*.hpp)
add_executable(${exe} ${sources} ${includes})

target_link_libraries(${exe} ${OpenCV_LIBS})
