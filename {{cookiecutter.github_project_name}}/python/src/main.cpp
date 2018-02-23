
#include <pybind11/pybind11.h>            // Pybind11 import to define Python bindings
#include <xtensor/xmath.hpp>              // xtensor import for the C++ universal functions

#define FORCE_IMPORT_ARRAY
#include <xtensor-python/pyarray.hpp>     // Numpy bindings
#include <xtensor-python/pytensor.hpp>    // Numpy bindings

#include "{{cookiecutter.cpp_root_folder_name}}/{{cookiecutter.package_name}}.hpp"
#include "{{cookiecutter.cpp_root_folder_name}}/{{cookiecutter.package_name}}_config.hpp"


#include <numeric>                        // Standard library import for std::accumulate

void export_core(pybind11::module &);

PYBIND11_MODULE(_{{cookiecutter.py_package_name}}, py_module)
{
    xt::import_numpy();



    py_module.doc() = "{{cookiecutter.py_package_name}}: the  {{cookiecutter.package_name}} python bindings";

    // defined in py_core.cpp
    export_core(py_module);
}