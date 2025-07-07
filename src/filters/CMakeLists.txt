add_library(filters STATIC "GaussianBlur.cpp"  "SobelFilter.cpp" "HorizontalSobelConvolution.h" "VerticalSobelConvolution.h" )


target_include_directories(filters PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


target_link_libraries(filters PUBLIC OpenMP::OpenMP_CXX core utils ${OpenCV_LIBS})
