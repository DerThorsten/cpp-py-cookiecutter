
#include <pybind11/pybind11.h>            // Pybind11 import to define Python bindings
#include <xtensor/xmath.hpp>              // xtensor import for the C++ universal functions

#define FORCE_IMPORT_ARRAY
#include <xtensor-python/pyarray.hpp>     // Numpy bindings
#include <xtensor-python/pytensor.hpp>    // Numpy bindings

#include "{{cookiecutter.cpp_root_folder_name}}/{{cookiecutter.package_name}}.hpp"
#include "{{cookiecutter.cpp_root_folder_name}}/{{cookiecutter.package_name}}_config.hpp"


#include <numeric>                        // Standard library import for std::accumulate

double sum_of_sines(xt::pyarray<double>& m)
{
    auto sines = xt::sin(m);  // sines does not actually hold values.
    return std::accumulate(sines.begin(), sines.end(), 0.0);
}

PYBIND11_MODULE({{cookiecutter.py_package_name}}, m)
{
    xt::import_numpy();
    m.doc() = "{{cookiecutter.py_package_name}}: the  {{cookiecutter.package_name}} python bindings";

    m.def("sum_of_sines", sum_of_sines, "Sum the sines of the input values");
}