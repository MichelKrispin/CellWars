#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "Bot/Bot.h"
#include "Bot/PlayerBot.h"

// Documentation at https://pybind11.readthedocs.io/en/stable/index.html
namespace py = pybind11;

// ------------
// Declarations
// Source in BindingUtilities.cpp
void InitializeUtilities(py::module &m);

// Source in BindingBot.cpp
void InitializeBot(py::module &m);
class PyBot : public Bot {
public: void MakeTurn(const WorldSnapshot& Snapshot) override;
};
class PyPlayerBot : public PlayerBot {
public: void MakeTurn(const WorldSnapshot& Snapshot) override;
};

// Source in BindingWorld.cpp
void InitializeWorld(py::module &m);
// ------------

// Note: To build the python binding: Go into the terminal and either type:
// > python setup.py build
// > python setup.py install
//
// or type
// > pip install .


PYBIND11_MODULE(CellWars, m) {
    // Docs
    m.doc() = R"pbdoc(
        CellWars python binding plugin
        -----------------------

        .. currentmodule:: CellWars

        .. autosummary::
           :toctree: _generate
    )pbdoc";

    InitializeUtilities(m);
    InitializeBot(m);
    InitializeWorld(m);

    // Test function to see if everything works
    m.def("subtract", [](int i, int j) { return i - j; }, R"pbdoc(
        Subtract two numbers

        Some other explanation about the subtract function.
    )pbdoc");

#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}
