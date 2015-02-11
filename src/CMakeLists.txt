
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -m64 -pthread" )

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(${FFTWPP_SOURCE_DIR}/include)

add_library(fftwpp fftw_functions.cpp)

execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion
                OUTPUT_VARIABLE GCC_VERSION)
string(STRIP ${GCC_VERSION} GCC_VERSION)
message("-- GCC version == ${GCC_VERSION}")
if (GCC_VERSION VERSION_GREATER 4.6 OR GCC_VERSION VERSION_EQUAL 4.6)
    message("-- GCC version >= 4.6, activating __float128.")
    add_definitions(-DQUADMATH)
    target_link_libraries(fftwpp quadmath)

    message("-- GCC version >= 4.6, activating flto.")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -flto" )
endif()

if (GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7)
    message("-- GCC version >= 4.7, using -std=c++11  -fext-numeric-literals .")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11  -fext-numeric-literals" )
else()
    message("-- GCC version < 4.7, using -std=c++0x.")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x" )
endif()

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
