cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

project (calc)

  find_package(LLVM REQUIRED HINTS "${LLVM_CMAKE_PATH}")
  list(APPEND CMAKE_MODULE_PATH ${LLVM_DIR})
    message(STATUS "1_2::------------------------------------------${LLVM_CMAKE_PATH}--::${LLVM_DIR}")

include(AddLLVM)
include(CheckIncludeFile)
include(CheckIncludeFileCXX)
include(CheckLibraryExists)
include(CheckCXXCompilerFlag)

find_package(LLVM REQUIRED CONFIG)
message("Found LLVM ${LLVM_PACKAGE_VERSION}, build type ${LLVM_BUILD_TYPE}")
list(APPEND CMAKE_MODULE_PATH ${LLVM_DIR})
include(DetermineGCCCompatible)
include(ChooseMSVCCRT)

add_definitions(${LLVM_DEFINITIONS})
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})
include_directories("${LLVM_BINARY_DIR}/include" "${LLVM_INCLUDE_DIR}")
set(TINYLANG_BUILT_STANDALONE 1)

link_directories("${LLVM_LIBRARY_DIR}")

llvm_map_components_to_libnames(llvm_libs Core)

if(LLVM_COMPILER_IS_GCC_COMPATIBLE)
  if(NOT LLVM_ENABLE_RTTI)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
  endif()
  if(NOT LLVM_ENABLE_EH)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")
  endif()
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")
    message(STATUS "1_4::------------------------------------------${CMAKE_MODULE_PATH}")

include(AddCalc)


add_subdirectory (src)
