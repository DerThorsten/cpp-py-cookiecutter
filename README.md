# xt-boilerplate
a cookiecutter for C++14 projects with integrated python bindings.



Features:
======
* cpp and python in one project
* unit tests with cpp doctest
* benchmark code with google benchmark
* python bindings with xtensor-python / pybind11
* docs with sphinx breathe and readthedocs support
* google benchmark and cpp doctest are downloaded at cmake-config time via external-projects since these dependencies are just for testing and benchmarking



Todos:
======
* conda recipes are not net in the cookiecutter
* no dedicated unit test system for the python module so far
* no dedicated python documentation so far
* Add documentation how to use the cookiecutter

