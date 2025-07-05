
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE "SobelFilter.cpp" "SobelFilter.h" "GaussianBlur.h"  "GaussianBlur.cpp" "Convolution.h")
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})
target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCV_INCLUDE_DIRS})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/vendor/opencv/build/x64/vc16/bin/opencv_world4120d.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)