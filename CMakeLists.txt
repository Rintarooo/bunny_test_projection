cmake_minimum_required(VERSION 3.0.2)
project(project_pcl_bunny)

## Compile as C++11
# add_compile_options(-std=c++11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -ggdb3 -O0")# -g3
# set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -G")# option, Device side debug: -G

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")# -g3
# set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -O0")
# set(CUDA_NVCC_FLAGS_DEBUG "-G -O0")
# set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} -lineinfo")# -G
# set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} -G")# -G


find_package(OpenCV REQUIRED)
set(CMAKE_CUDA_COMPILER  /usr/local/cuda/bin/nvcc)
find_package(CUDA REQUIRED)

# directories where header files exists
include_directories(
  ${OpenCV_INCLUDE_DIRS}
  ${CUDA_INCLUDE_DIRS}
  # CostVolume/
)


## cuda_add_library() is same as cuda_add_executable() except that a library is created.
# cuda_add_library(cuda_node src/lib_cuda_code.cu src/libe_none_cuda_code.cpp )

## create executable file named "main"

# add_subdirectory(CostVolume/)# add_subdirectory(src/directory)

# cuda_compile(main
#   main.cpp f_load.cpp
#   -G )

cuda_add_executable(main
  main.cpp
  f_load.cpp
  # CostVolume/CostVolume.cpp
  # CostVolume/CostVolume_update.cu
  # OPTIONS -G
)


target_link_libraries(main
  ${OpenCV_LIBRARIES}
  ${CUDA_LIBRARIES}
  # cost_volume_lib
)

cuda_add_executable(sub
  sub.cpp
  f_load.cpp
  # CostVolume/CostVolume.cpp
  # CostVolume/CostVolume_update.cu
  # OPTIONS -G
)

target_link_libraries(sub
  ${OpenCV_LIBRARIES}
  ${CUDA_LIBRARIES}
  # cost_volume_lib
)

# for debug
message("-- CUDA --")
message("Version: " ${CUDA_VERSION})
message("Library: " ${CUDA_CUDA_LIBRARY})
message("Runtime Library: " ${CUDA_CUDART_LIBRARY})
message("include dirs for cuda headers: " ${CUDA_INCLUDE_DIRS})

message("-- OpenCV --")
MESSAGE(WARNING "prefix ${CMAKE_PREFIX_PATH}")    
MESSAGE(WARNING "version ${OpenCV_VERSION}")
MESSAGE(WARNING "install path ${OpenCV_INSTALL_PATH}") 
MESSAGE(WARNING "config path ${OpenCV_CONFIG_PATH}") # look at the output of this message
MESSAGE(WARNING "include dirs ${OpenCV_INCLUDE_DIRS}")
MESSAGE(WARNING "libs ${OpenCV_LIBS}")

