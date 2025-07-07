add_library(core STATIC Convolution.cpp Convolution.h)

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# core necesita OpenCV para filter2D, etc.
target_link_libraries(core PUBLIC OpenMP::OpenMP_CXX  ${OpenCV_LIBS})


