
cmake_minimum_required(VERSION 3.1)

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

    set(DOCTEST_INCLUDE_DIRS   ${CMAKE_CURRENT_BINARY_DIR}/doctest-src/doctest)

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

target_include_directories(${${PROJECT_NAME}_TEST_TARGET}
     INTERFACE   $<BUILD_INTERFACE:${DOCTEST_INCLUDE_DIRS}>
)
