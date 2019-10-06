#ifndef _WINDOWEVENT_H
#define _WINDOWEVENT_H

enum class WindowEvent
{
    /** \brief Nothing important happened. */
    Nothing,
    /** \brief Indicates that the window should be killed. */
    Kill,
    /** \brief Pause the game. */
    Pause,
    /** \brief Unpause/Playe the game. */
    Play,
    /** \brief Just do one step/turn forward. */
    StepForward
};

#endif
