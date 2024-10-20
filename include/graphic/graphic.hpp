#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

#include "graphic.h"
#include <SFML/Graphics.hpp>
#include <cstring>

// Definitions of the structures
struct t_artic_window {
    sf::RenderWindow* window;
    t_artic_loop_func loop_func;
    t_artic_event_func event_func;
    t_artic_display_func display_func;
    t_artic_pixelarray* pixelarray;
};

struct t_artic_pixelarray {
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Uint8* pixels;  // RGBA pixel data
    int width;
    int height;
};

#endif /* GRAPHIC_HPP */
