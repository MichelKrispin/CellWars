#include "Window.h"
#include <SFML/Graphics.hpp>
#include "Configuration.h"

Window::Window()
{
    _Window = new sf::RenderWindow(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Cell Wars");
}

Window::~Window()
{
}

void Window::Display(const FieldList* Fields)
{
    // Looping trough all of the Fields
    for (int i = 0; i < 2; ++i) // 2 for team size
    {
        for (FieldListIterator iterator = Fields[i].Begin();
             iterator != Fields[i].End();
             iterator.Next())
        {
            Field* current = iterator.Get();
            // How strong the field should be rendered
            current->getCellCount();
            // Where it should be rendered
        }
    }
}
