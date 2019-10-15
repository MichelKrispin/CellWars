#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "World/World.h"
#include "World/WorldSnapshot.h"
#include "World/FieldList.h"
#include "World/Field.h"
#include "Bot/Bot.h"
#include "Bot/PlayerBot.h"
#include "Bot/Utilities.h"

// Documentation at https://pybind11.readthedocs.io/en/stable/index.html
namespace py = pybind11;

// Note: To build the python binding: Go into the terminal and either type:
// > python setup.py build
// > python setup.py install
//
// or type
// > pip install .

class PyBot : public Bot {
public:
    using Bot::Bot;

    void MakeTurn(const WorldSnapshot& Snapshot) override
    {
        PYBIND11_OVERLOAD( // Maybe use NAME extension
            void,
            Bot,
            MakeTurn,
            Snapshot
        );
    }
};

class PyPlayerBot : public PlayerBot {
public:
    using PlayerBot::PlayerBot;

    void MakeTurn(const WorldSnapshot& Snapshot) override
    {
        PYBIND11_OVERLOAD( // Maybe use NAME extension
            void,
            PlayerBot,
            MakeTurn,
            Snapshot
        );
    }
};

PYBIND11_MODULE(CellWars, m) {
    m.doc() = R"pbdoc(
        CellWars python binding plugin
        -----------------------

        .. currentmodule:: CellWars

        .. autosummary::
           :toctree: _generate
    )pbdoc";

    m.def("round_up", &RoundUp);


    py::class_<Bot, PyBot>(m, "Bot")
        .def(py::init<>())
        .def("MakeTurn", &Bot::MakeTurn);

    py::class_<PlayerBot, PyPlayerBot>(m, "PlayerBot")
        .def(py::init<>())
        .def("MakeTurn", &PlayerBot::MakeTurn);


    py::class_<World>(m, "World")
        .def(py::init<>())
        //.def("play", (void (World::*)(Bot**)) &World::Play, "Play with 2,3 or 4 bots")
        .def("play", (void (World::*)(PlayerBot*,PlayerBot*)) &World::Play, "Play with 2 bots");

    py::class_<WorldSnapshot>(m, "WorldSnapshot")
        .def_property_readonly("fields",     &WorldSnapshot::GetFields)
        .def_property_readonly("turn",       &WorldSnapshot::GetTurn)
        .def_property_readonly("team_count", &WorldSnapshot::GetCount)
        .def("get_adjacent_field_of", &WorldSnapshot::GetAdjacentFieldOf);

    py::class_<FieldList>(m, "FieldList")
        .def(py::init<>())
        .def_property_readonly("size", &FieldList::GetSize)
        .def_property_readonly("as_list", &FieldList::GetPythonList);


    py::class_<Field>(m, "Field")
        .def_property_readonly("cell_count", &Field::GetCellCount)
        .def_property_readonly("position", &Field::GetPosition)
        .def_property_readonly("position_as_grid", &Field::GetPositionAsGrid)
        .def("split_cells", &Field::SplitCells);


    py::enum_<DIRECTION>(m, "Direction")
        .value("left",  DIRECTION::LEFT)
        .value("right", DIRECTION::RIGHT)
        .value("down",  DIRECTION::DOWN)
        .value("up",    DIRECTION::UP)
        .export_values();


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
