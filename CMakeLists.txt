
cmake_minimum_required(VERSION 3.16.3)

project(Node)


set(CMAKE_BUILD_TYPE Debug)
include_directories(/headers)
add_executable ( Node main.cpp )

# find_package (Eigen3 3.3 REQUIRED NO_MODULE)
 
# target_link_libraries (RadarTest Eigen3)

# target_include_directories(RadarTest )


#target_link_libraries ( sitk_example ${SimpleITK_LIBRARIES} )

