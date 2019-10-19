#include "Bot/Utilities.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

void InitializeUtilities(py::module &m)
{
    m.def("round_up", &RoundUp);
}