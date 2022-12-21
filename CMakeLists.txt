cmake_minimum_required(VERSION 3.24)
set(projName ithread)
project(${projName} C)

if("${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_BINARY_DIR}")
  message(
    FATAL_ERROR
      "Building from within the libthread source tree is not supported.\n")
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/utils.cmake")
defineinterfaces()

set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

add_library(${projName} STATIC "${PROJECT_ROOT}/src/ithread.c")
target_link_libraries(
  ${projName}
  PRIVATE "${projName}CompileOptions"
  PRIVATE Threads::Threads)
target_include_directories(${projName} PUBLIC "${PROJECT_ROOT}/include/")
set_target_properties(
  ${projName} PROPERTIES PUBLIC_HEADER "${PROJECT_ROOT}/include/ithread.h")

include(GNUInstallDirs)
install(
  TARGETS ${projName}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
