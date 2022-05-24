cmake_minimum_required(VERSION 3.4.3)
set(CMAKE_CXX_STANDARD 17)
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  project(Tinylang)
    message(STATUS "1_1::------------${CMAKE_SOURCE_DIR}-----------------${CMAKE_CURRENT_SOURCE_DIR}-------------${LLVM_CMAKE_PATH}")

  find_package(LLVM REQUIRED HINTS "${LLVM_CMAKE_PATH}")
  list(APPEND CMAKE_MODULE_PATH ${LLVM_DIR})
    message(STATUS "1_2::------------------------------------------${LLVM_CMAKE_PATH}--::${LLVM_DIR}")

  include(AddLLVM)
  include(HandleLLVMOptions)

  include_directories("${LLVM_BINARY_DIR}/include" "${LLVM_INCLUDE_DIR}")
  link_directories("${LLVM_LIBRARY_DIR}")
    message(STATUS "1_3::------------------------------------------${LLVM_BINARY_DIR}--::${LLVM_INCLUDE_DIR}")
  set(TINYLANG_BUILT_STANDALONE 1)
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")
    message(STATUS "1_4::------------------------------------------${CMAKE_MODULE_PATH}")
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR AND NOT MSVC_IDE)
  message(FATAL_ERROR "In-source builds are not allowed. ")
endif()

set(TINYLANG_VERSION_STRING "0.1")
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/include/tinylang/Basic/Version.inc.in
  ${CMAKE_CURRENT_BINARY_DIR}/include/tinylang/Basic/Version.inc)

include(AddTinylang)

include_directories(BEFORE
  ${CMAKE_CURRENT_BINARY_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  )

add_subdirectory(lib)
add_subdirectory(tools)