cmake_minimum_required(VERSION 3.15)
# project(cmake_and_cuda languades CXX CUDA)
project(oneWeekend)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)
# find_package( CUDA REQUIRED )


# include_directories(/usr/local/cuda /usr/local/cuda/include)
# link_directories(/usr/local/cuda /usr/local/cuda/lib /usr/local/cuda/lib64)

add_executable (oneWeekend main.cpp)
target_link_libraries (oneWeekend Eigen3::Eigen)