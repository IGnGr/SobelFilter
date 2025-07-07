add_executable(${PROJECT_NAME} SobelFilterApp.cpp main.cpp)




target_include_directories(${PROJECT_NAME} 
PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} 
${CMAKE_SOURCE_DIR}/src/filters 
${CMAKE_SOURCE_DIR}/src/core 
${CMAKE_SOURCE_DIR}/src/utils)


target_link_libraries(${PROJECT_NAME} PRIVATE filters)



# Copy OpenCV DLL 
if (WIN32)
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/vendor/opencv/build/x64/vc16/bin/opencv_world4120d.dll"
      $<TARGET_FILE_DIR:${PROJECT_NAME}>
  )
endif()
