
include_directories(${FFTWigner_SOURCE_DIR}/fftwpp/include)
add_library(fftwpp fftw_functions.cpp)

target_link_libraries(fftwpp ${FFTW_THR_LIB} ${FFTW_LIB}  ${FFTWL_THR_LIB} ${FFTWL_LIB}  ${FFTWF_THR_LIB} ${FFTWF_LIB})

if(FFTWQ_LIB)
    target_link_libraries(fftwpp ${FFTWQ_THR_LIB} ${FFTWQ_LIB})
endif()

FILE(GLOB headers "${FFTWigner_SOURCE_DIR}/fftwpp/include/*.hpp")

INSTALL(FILES ${headers}
        DESTINATION include
        COMPONENT fftwpp)

INSTALL(TARGETS fftwpp
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  COMPONENT fftwpp
)
