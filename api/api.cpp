#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "person.h"
#include "my_greet.h"
#include "my_math.h"

namespace py = pybind11;

PYBIND11_MODULE(pybind11_example, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring

    m.def("greet", &greet, "A function which greets the user.", py::arg("name"));
    m.def("hello", &hello, "A function which says hello to the user.", py::arg("name"));
    m.def("goodbye", &goodbye, "A function which says goodbye to the user.", py::arg("name"));
    
    m.def("calc_e", &calc_e, "A function which calculates e.", py::arg("n"));
    m.def("calc_pi", &calc_pi, "A function which calculates pi.", py::arg("n"));
    m.def("calc_sqrt", &calc_sqrt, "A function which calculates the square root of a number.", py::arg("n"));

    py::class_<Student>(m, "Student")
        .def(py::init<const string &, int>(), py::arg("name"), py::arg("age"))
        .def("getAge", &Student::getAge)
        .def("setAge", &Student::setAge, py::arg("age"))
        .def("getName", &Student::getName)
        .def("setName", &Student::setName, py::arg("name"))
        .def("__repr__", &Student::display)
    ;
}
