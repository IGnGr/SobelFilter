add_library(utils STATIC Utils.h Utils.cpp)

target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(utils PUBLIC OpenMP::OpenMP_CXX ${OpenCV_LIBS})
