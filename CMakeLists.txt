# CMakeList.txt : CMake project for SobelFilter, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("SobelFilter")

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

find_package(OpenCV REQUIRED PATHS "${CMAKE_SOURCE_DIR}/vendor/opencv/build/x64/vc16/lib")


# buscar OpenMP (opcional)
find_package(OpenMP)


# Add source to this project's executable.
add_subdirectory(src)




if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SobelFilter PROPERTY CXX_STANDARD 20)
endif()

