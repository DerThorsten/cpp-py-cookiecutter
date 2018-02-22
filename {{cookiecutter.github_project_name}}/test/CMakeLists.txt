############################################################################
# Copyright (c) 2016, Johan Mabille, Sylvain Corlay and Wolf Vollprecht    #
#                                                                          #
# Distributed under the terms of the BSD 3-Clause License.                 #
#                                                                          #
# The full license is in the file LICENSE, distributed with this software. #
############################################################################

cmake_minimum_required(VERSION 3.1)

# if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
#     project(xtensor-test)

#     find_package(xtensor REQUIRED CONFIG)
#     set(XTENSOR_INCLUDE_DIR ${xtensor_INCLUDE_DIRS})
# endif ()

# message(STATUS "Forcing tests build type to Release")
# set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)

# include(CheckCXXCompilerFlag)

# string(TOUPPER "${CMAKE_BUILD_TYPE}" U_CMAKE_BUILD_TYPE)

# if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Intel")
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -Wunused-parameter -Wextra -Wreorder -Wconversion -Wsign-conversion")
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wold-style-cast -Wunused-variable")
#     #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -Wunused-parameter -Wextra -Wreorder -Wconversion")
#     CHECK_CXX_COMPILER_FLAG("-std=c++14" HAS_CPP14_FLAG)

#     if (HAS_CPP14_FLAG)
#         set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
#     else()
#         message(FATAL_ERROR "Unsupported compiler -- xtensor requires C++14 support!")
#     endif()
# endif()

# if(MSVC)
#     add_definitions(-D_CRT_SECURE_NO_WARNINGS)
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc /MP /bigobj")
#     set(CMAKE_EXE_LINKER_FLAGS /MANIFEST:NO)
# endif()

if(DOWNLOAD_DOCTEST OR DOCTEST_SRC_DIR)

    if(DOWNLOAD_DOCTEST)
        # Download and unpack doctest at configure time
        configure_file(downloadDoctest.cmake.in doctest-download/CMakeLists.txt)
    else()
        # Copy local source of doctest at configure time
        configure_file(copyDoctest.cmake.in doctest-download/CMakeLists.txt)
    endif()
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                    RESULT_VARIABLE result
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doctest-download )
    if(result)
        message(FATAL_ERROR "CMake step for doctest failed: ${result}")
    endif()
    execute_process(COMMAND ${CMAKE_COMMAND} --build .
                    RESULT_VARIABLE result
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doctest-download )
    if(result)
        message(FATAL_ERROR "Build step for doctest failed: ${result}")
    endif()

    # # Add doctest directly to our build. This defines
    # # the DOCTEST and DOCTEST_main targets.
    # add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/doctest-src
    #                  ${CMAKE_CURRENT_BINARY_DIR}/doctest-build)

    set(DOCTEST_INCLUDE_DIRS   ${CMAKE_CURRENT_BINARY_DIR}/doctest-src/doctest)
    set(DOCTEST_BOTH_LIBRARIES  DOCTEST_main DOCTEST)
else()
    find_package(DOCTEST REQUIRED)
endif()

find_package(Threads)

include_directories(${PROJECT_INCLUDE_DIR})
include_directories(${DOCTEST_INCLUDE_DIRS})



file(GLOB_RECURSE ${PROJECT_NAME}_TESTS  *.cpp)
list(REMOVE_ITEM ${PROJECT_NAME}_TESTS main.cpp)





set(${PROJECT_NAME}_TEST_TARGET test_${PROJECT_NAME})



add_executable( ${${PROJECT_NAME}_TEST_TARGET}
    main.cpp
    ${${PROJECT_NAME}_TESTS}
)

message(STATUS "DOC" ${DOCTEST_SOURCE_DIR})
target_include_directories(${${PROJECT_NAME}_TEST_TARGET}
     INTERFACE   $<BUILD_INTERFACE:${DOCTEST_INCLUDE_DIRS}>
)


# if(DOWNLOAD_DOCTEST OR DOCTEST_SRC_DIR)
#     add_dependencies(${XTENSOR_TARGET} DOCTEST_main)
# endif()
# target_link_libraries(${XTENSOR_TARGET} ${DOCTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
# add_custom_target(xtest COMMAND test_xtensor DEPENDS ${XTENSOR_TARGET})

