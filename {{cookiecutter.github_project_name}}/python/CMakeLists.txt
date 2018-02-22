include_directories(${PROJECT_INCLUDE_DIR})

find_package(xtensor REQUIRED)
include_directories(${xtensor_INCLUDE_DIRS})

find_package(xtensor-python REQUIRED)
include_directories(${xtensor-python_INCLUDE_DIRS})

find_package(pybind11 REQUIRED)
include_directories(${pybind11_INCLUDE_DIRS})

find_package(NUMPY REQUIRED)
include_directories(${PYTHON_NUMPY_INCLUDE_DIR})

file(GLOB_RECURSE ${PROJECT_NAME}_PYTHON_SRC_FILES 
     RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

list(REMOVE_ITEM ${PROJECT_NAME}_PYTHON_SRC_FILES  main.cpp)


set(${PROJECT_NAME}_PYTHON_INTERFACE_TARGET python_interface_${PROJECT_NAME})


pybind11_add_module( ${${PROJECT_NAME}_PYTHON_INTERFACE_TARGET} main.cpp
    ${${PROJECT_NAME}_PYTHON_SRC_FILES})


set_target_properties(${${PROJECT_NAME}_PYTHON_INTERFACE_TARGET} PROPERTIES OUTPUT_NAME {{cookiecutter.py_package_name}} )