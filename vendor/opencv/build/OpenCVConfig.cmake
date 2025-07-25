# ===================================================================================
#  The OpenCV CMake configuration file
#
#             ** File generated automatically, do not modify **
#
#  Usage from an external project:
#    In your CMakeLists.txt, add these lines:
#
#    FIND_PACKAGE(OpenCV REQUIRED)
#    TARGET_LINK_LIBRARIES(MY_TARGET_NAME ${OpenCV_LIBS})
#
#    Or you can search for specific OpenCV modules:
#
#    FIND_PACKAGE(OpenCV REQUIRED core imgcodecs)
#
#    If the module is found then OPENCV_<MODULE>_FOUND is set to TRUE.
#
#    This file will define the following variables:
#      - OpenCV_LIBS                     : The list of libraries to link against.
#      - OpenCV_INCLUDE_DIRS             : The OpenCV include directories.
#      - OpenCV_COMPUTE_CAPABILITIES     : The version of compute capability
#      - OpenCV_VERSION                  : The version of this OpenCV build: "4.12.0"
#      - OpenCV_VERSION_MAJOR            : Major version part of OpenCV_VERSION: "4"
#      - OpenCV_VERSION_MINOR            : Minor version part of OpenCV_VERSION: "12"
#      - OpenCV_VERSION_PATCH            : Patch version part of OpenCV_VERSION: "0"
#      - OpenCV_VERSION_STATUS           : Development status of this build: ""
#
#    Advanced variables:
#      - OpenCV_SHARED
#
# ===================================================================================
#
#    Windows pack specific options:
#      - OpenCV_STATIC
#      - OpenCV_CUDA

if(CMAKE_VERSION VERSION_GREATER 2.6)
  get_property(OpenCV_LANGUAGES GLOBAL PROPERTY ENABLED_LANGUAGES)
  if(NOT ";${OpenCV_LANGUAGES};" MATCHES ";CXX;")
    enable_language(CXX)
  endif()
endif()

if(NOT DEFINED OpenCV_STATIC)
  # look for global setting
  if(NOT DEFINED BUILD_SHARED_LIBS OR BUILD_SHARED_LIBS)
    set(OpenCV_STATIC OFF)
  else()
    set(OpenCV_STATIC ON)
  endif()
endif()

if(NOT DEFINED OpenCV_CUDA)
  # if user' app uses CUDA, then it probably wants CUDA-enabled OpenCV binaries
  if(CUDA_FOUND)
    set(OpenCV_CUDA ON)
  endif()
endif()

function(check_one_config RES)
  set(${RES} "" PARENT_SCOPE)
  if(NOT OpenCV_RUNTIME OR NOT OpenCV_ARCH)
    return()
  endif()
  set(candidates)
  if(OpenCV_STATIC)
    list(APPEND candidates "${OpenCV_ARCH}/${OpenCV_RUNTIME}/staticlib")
  endif()
  if(OpenCV_CUDA)
    list(APPEND candidates "gpu/${OpenCV_ARCH}/${OpenCV_RUNTIME}/lib")
  endif()
  if(OpenCV_CUDA AND OpenCV_STATIC)
    list(APPEND candidates "gpu/${OpenCV_ARCH}/${OpenCV_RUNTIME}/staticlib")
  endif()
  list(APPEND candidates "${OpenCV_ARCH}/${OpenCV_RUNTIME}/lib")
  foreach(c ${candidates})
    set(p "${OpenCV_CONFIG_PATH}/${c}")
    if(EXISTS "${p}/OpenCVConfig.cmake")
      set(${RES} "${p}" PARENT_SCOPE)
      return()
    endif()
  endforeach()
endfunction()

get_filename_component(OpenCV_CONFIG_PATH "${CMAKE_CURRENT_LIST_FILE}" DIRECTORY)

if((NOT DEFINED CMAKE_SYSTEM_PROCESSOR OR CMAKE_SYSTEM_PROCESSOR STREQUAL "")
    AND NOT OPENCV_SUPPRESS_MESSAGE_MISSING_CMAKE_SYSTEM_PROCESSOR)
  message(WARNING "OpenCV: CMAKE_SYSTEM_PROCESSOR is not defined. Perhaps CMake toolchain is broken")
endif()
if(NOT DEFINED CMAKE_SIZEOF_VOID_P
    AND NOT OPENCV_SUPPRESS_MESSAGE_MISSING_CMAKE_SIZEOF_VOID_P)
  message(WARNING "OpenCV: CMAKE_SIZEOF_VOID_P is not defined. Perhaps CMake toolchain is broken")
endif()

if(DEFINED OpenCV_ARCH AND DEFINED OpenCV_RUNTIME)
  # custom overridden values
elseif(MSVC)
  # see Modules/CMakeGenericSystem.cmake
  if("${CMAKE_GENERATOR}" MATCHES "(Win64|IA64)")
    set(OpenCV_ARCH "x64")
  elseif("${CMAKE_GENERATOR_PLATFORM}" MATCHES "ARM64")
    set(OpenCV_ARCH "ARM64")
  elseif("${CMAKE_GENERATOR}" MATCHES "ARM")
    set(OpenCV_ARCH "ARM")
  elseif("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
    set(OpenCV_ARCH "x64")
  else()
    set(OpenCV_ARCH x86)
  endif()

  if(MSVC_VERSION EQUAL 1400)
    set(OpenCV_RUNTIME vc8)
  elseif(MSVC_VERSION EQUAL 1500)
    set(OpenCV_RUNTIME vc9)
  elseif(MSVC_VERSION EQUAL 1600)
    set(OpenCV_RUNTIME vc10)
  elseif(MSVC_VERSION EQUAL 1700)
    set(OpenCV_RUNTIME vc11)
  elseif(MSVC_VERSION EQUAL 1800)
    set(OpenCV_RUNTIME vc12)
  elseif(MSVC_VERSION EQUAL 1900)
    set(OpenCV_RUNTIME vc14)
  elseif(MSVC_VERSION MATCHES "^191[0-9]$")
    set(OpenCV_RUNTIME vc15)
    check_one_config(has_VS2017)
    if(NOT has_VS2017)
      set(OpenCV_RUNTIME vc14) # selecting previous compatible runtime version
    endif()
  elseif(MSVC_VERSION MATCHES "^192[0-9]$")
    set(OpenCV_RUNTIME vc16)
    check_one_config(has_VS2019)
    if(NOT has_VS2019)
      set(OpenCV_RUNTIME vc15) # selecting previous compatible runtime version
      check_one_config(has_VS2017)
      if(NOT has_VS2017)
        set(OpenCV_RUNTIME vc14) # selecting previous compatible runtime version
      endif()
    endif()
  elseif(MSVC_VERSION MATCHES "^19[34][0-9]$")
    set(OpenCV_RUNTIME vc17)
    check_one_config(has_VS2022)
    if(NOT has_VS2022)
     set(OpenCV_RUNTIME vc16)
     check_one_config(has_VS2019)
     if(NOT has_VS2019)
       set(OpenCV_RUNTIME vc15) # selecting previous compatible runtime version
       check_one_config(has_VS2017)
       if(NOT has_VS2017)
         set(OpenCV_RUNTIME vc14) # selecting previous compatible runtime version
       endif()
     endif()
    endif()
  endif()
elseif(MINGW)
  set(OpenCV_RUNTIME mingw)

  if(CMAKE_SYSTEM_PROCESSOR MATCHES "amd64.*|x86_64.*|AMD64.*")
    set(OpenCV_ARCH x64)
  else()
    set(OpenCV_ARCH x86)
  endif()
endif()

check_one_config(OpenCV_LIB_PATH)

if(NOT OpenCV_FIND_QUIETLY)
  message(STATUS "OpenCV ARCH: ${OpenCV_ARCH}")
  message(STATUS "OpenCV RUNTIME: ${OpenCV_RUNTIME}")
  message(STATUS "OpenCV STATIC: ${OpenCV_STATIC}")
endif()

if(OpenCV_LIB_PATH AND EXISTS "${OpenCV_LIB_PATH}/OpenCVConfig.cmake")
  include("${OpenCV_LIB_PATH}/OpenCVConfig.cmake")

  if(NOT OpenCV_FIND_QUIETLY)
    message(STATUS "Found OpenCV ${OpenCV_VERSION} in ${OpenCV_LIB_PATH}")
    if(NOT OpenCV_LIB_PATH MATCHES "/staticlib")
      get_filename_component(_OpenCV_LIB_PATH "${OpenCV_LIB_PATH}/../bin" ABSOLUTE)
      file(TO_NATIVE_PATH "${_OpenCV_LIB_PATH}" _OpenCV_LIB_PATH)
      message(STATUS "You might need to add ${_OpenCV_LIB_PATH} to your PATH to be able to run your applications.")
      if(OpenCV_LIB_PATH MATCHES "/gpu/")
        string(REPLACE "\\gpu" "" _OpenCV_LIB_PATH2 "${_OpenCV_LIB_PATH}")
        message(STATUS "GPU support is enabled so you might also need ${_OpenCV_LIB_PATH2} in your PATH (it must go after the ${_OpenCV_LIB_PATH}).")
      endif()
    endif()
  endif()
else()
  if(NOT OpenCV_FIND_QUIETLY)
    message(WARNING
"Found OpenCV Windows Pack but it has no binaries compatible with your configuration.
You should manually point CMake variable OpenCV_DIR to your build of OpenCV library."
    )
  endif()
  set(OpenCV_FOUND FALSE)
endif()
