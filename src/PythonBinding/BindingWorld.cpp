#include "World/World.h"
#include "World/WorldSnapshot.h"
#include "World/FieldList.h"
#include "World/Field.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

void InitializeWorld(py::module &m)
{
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
}