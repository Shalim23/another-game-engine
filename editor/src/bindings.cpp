#include <pybind11/pybind11.h>
import age_engine;

namespace py = pybind11;

PYBIND11_MODULE(age_editor, m) {
    m.doc() = "AGE (Another Game Engine) Editor Python bindings";

    // You can add Python bindings here as you develop the editor
    // Example:
    // py::class_<EditorWindow>(m, "EditorWindow")
    //     .def(py::init<>())
    //     .def("run", &EditorWindow::run)
    //     .def("close", &EditorWindow::close);
}
