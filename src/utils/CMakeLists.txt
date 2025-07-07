add_library(utils STATIC Utils.cpp)

target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(utils PUBLIC ${OpenCV_LIBS})
