# CMakeList.txt : CMake project for SobelFilter, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)


# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("SobelFilter")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

find_package(OpenCV REQUIRED PATHS "${CMAKE_SOURCE_DIR}/vendor/opencv/build/x64/vc16/lib")

# Add source to this project's executable.
add_subdirectory(vendor)
add_subdirectory(src)




get_property(all_targets GLOBAL PROPERTY TARGETS)
   message(STATUS "All targets: ${all_targets}")


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SobelFilter PROPERTY CXX_STANDARD 20)
endif()


#OpenMP
#find_package(OpenMP)
#if(OpenMP_CXX_FOUND)
#    target_link_libraries(${PROJECT_NAME} PUBLIC OpenMP::OpenMP_CXX)
#endif()




# TODO: Add tests and install targets if needed.
