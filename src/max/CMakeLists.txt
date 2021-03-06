project(max)

# aux_source_directory(. max_src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx")

FIND_PACKAGE( OpenMP REQUIRED)

if(OPENMP_FOUND)
message("OPENMP FOUND")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}${OpenMP_EXE_LINKER_FLAGS}")
endif()

FIND_PACKAGE(CUDA REQUIRED)
if (NOT CUDA_FOUND)
  message(STATUS "CUDA not found. Project will not be built.")
endif(NOT CUDA_FOUND)

SET(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS};-gencode arch=compute_61,code=sm_61;)
include_directories("${CUDA_INCLUDE_DIRS}")


# build a cuda library
file(GLOB CUDA_SRC
  ./*.cu
  ./*.cuh
)
cuda_add_library(${PROJECT_NAME}_CUDA SHARED ${CUDA_SRC})
target_link_libraries(${PROJECT_NAME}_CUDA common_CUDA)

file(GLOB CXX_SRC
  ${PROJECT_NAME}.cpp
  ${PROJECT_NAME}.hpp
)

add_library(${PROJECT_NAME}_LIB STATIC ${CXX_SRC})


include_directories(${CMAKE_SOURCE_DIR}/src)
add_executable(${PROJECT_NAME} ${PROJECT_NAME}_main.cpp)

# link the max with cuda lib
target_link_libraries(${PROJECT_NAME} 
  ${PROJECT_NAME}_CUDA
  ${PROJECT_NAME}_LIB
  common_LIB)