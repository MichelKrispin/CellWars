#include "Bot/Bot.h"
#include "Bot/PlayerBot.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

// These classes are only used to make inheritance of this classes available in Python
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
        // TODO: Check if _NAME is better to rename the method
        PYBIND11_OVERLOAD( // Maybe use NAME extension
                void,
                PlayerBot,
                MakeTurn,
                Snapshot
        );
    }
};


void InitializeBot(py::module &m)
{
    py::class_<Bot, PyBot>(m, "Bot")
            .def(py::init<>())
            .def("MakeTurn", &Bot::MakeTurn);

    py::class_<PlayerBot, PyPlayerBot>(m, "PlayerBot")
            .def(py::init<>())
            .def("MakeTurn", &PlayerBot::MakeTurn);

}