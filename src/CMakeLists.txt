
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -Wextra -pedantic -m64 -pthread" )

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(${FFTWPP_SOURCE_DIR}/include)

add_library(fftwpp fftw_functions.cpp)


# BOOST
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.54.0 REQUIRED)
include_directories(BEFORE SYSTEM ${Boost_INCLUDE_DIRS})


# FFTW3
find_path (FFTW_INCLUDES fftw3.h)
include_directories(BEFORE SYSTEM ${FFTW_INCLUDES})

find_library (FFTWQ_LIB NAMES fftw3q)
if(FFTWQ_LIB)
    add_definitions(-DFFTWQ)
endif()


# INSTALL
FILE(GLOB headers "${FFTWPP_SOURCE_DIR}/include/*.hpp")

INSTALL(FILES ${headers}
        DESTINATION include
        COMPONENT fftwpp)

INSTALL(TARGETS fftwpp
  RUNTIME DESTINATION bin
   COMPONENT fftwpp
  LIBRARY DESTINATION lib
   COMPONENT fftwpp
  ARCHIVE DESTINATION lib
   COMPONENT fftwpp
)

if(NOT TARGET uninstall)
    add_custom_target(uninstall
    "${CMAKE_COMMAND}" -P "${CMAKE_SOURCE_DIR}/uninstall.cmake"
    )
endif()
