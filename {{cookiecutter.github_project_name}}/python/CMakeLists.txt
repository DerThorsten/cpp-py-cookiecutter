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



#################################
# INSTALL THE PYTHON MODULE
#################################

IF(NOT DEFINED PYTHON_MODULE_INSTALL_DIR OR PYTHON_MODULE_INSTALL_DIR MATCHES "^$")


    execute_process(
      COMMAND "${PYTHON_EXECUTABLE}" -c "if True:
        from distutils import sysconfig as sc
        print(sc.get_python_lib(prefix='', plat_specific=True))"
      OUTPUT_VARIABLE PYTHON_SITE
      OUTPUT_STRIP_TRAILING_WHITESPACE)

    execute_process(
      COMMAND "${PYTHON_EXECUTABLE}" -c "from __future__ import print_function; from distutils.sysconfig import get_python_lib; print(get_python_lib())"
      OUTPUT_VARIABLE PYTHON_SITE
      OUTPUT_STRIP_TRAILING_WHITESPACE)

    SET(PYTHON_MODULE_INSTALL_DIR ${PYTHON_SITE})

ENDIF()

SET(PYTHON_MODULE_INSTALL_DIR ${PYTHON_MODULE_INSTALL_DIR}
    CACHE PATH "where to install the Nifty Python package" FORCE)

# this is the install path relative to CMAKE_INSTALL_PREFIX,
# use this in INSTALL() commands to get packaging right
FILE(RELATIVE_PATH PYTHON_MODULE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX} ${PYTHON_MODULE_INSTALL_DIR})

install(TARGETS  ${${PROJECT_NAME}_PYTHON_INTERFACE_TARGET} DESTINATION ${PYTHON_MODULE_INSTALL_DIR})