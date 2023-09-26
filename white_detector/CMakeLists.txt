cmake_minimum_required(VERSION 3.0)
project(WhiteAreaCropping)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Create the executable
add_executable(white_area_cropping main.cpp)

# Link OpenCV libraries
target_link_libraries(white_area_cropping ${OpenCV_LIBS})

# Set Rpath to the QUIRC library directory
set(CMAKE_INSTALL_RPATH /usr/local/lib)