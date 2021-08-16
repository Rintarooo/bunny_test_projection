cmake_minimum_required(VERSION 3.0.2)
project(project_pcl_bunny)

## Compile as C++11
# add_compile_options(-std=c++11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -ggdb3 -O0")# -g3


find_package(OpenCV REQUIRED)
# set(CMAKE_CUDA_COMPILER  /usr/local/cuda/bin/nvcc)
# find_package(CUDA REQUIRED)

# directories where header files exists
include_directories(
  ${OpenCV_INCLUDE_DIRS}
)
add_executable(main
  qua2rot.cpp
  f_load.cpp
)


target_link_libraries(main
  ${OpenCV_LIBRARIES}
)

message("-- OpenCV --")
MESSAGE(WARNING "version ${OpenCV_VERSION}")
MESSAGE(WARNING "install path ${OpenCV_INSTALL_PATH}") 
MESSAGE(WARNING "config path ${OpenCV_CONFIG_PATH}") # look at the output of this message
MESSAGE(WARNING "include dirs ${OpenCV_INCLUDE_DIRS}")
MESSAGE(WARNING "libs ${OpenCV_LIBS}")

