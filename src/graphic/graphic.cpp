#include "graphic/graphic.hpp"

extern "C" {

// Function implementations

t_artic_window* new_window(const char* title, int width, int height, int fullscreen)
{
    t_artic_window* win = new t_artic_window();
    sf::Uint32 style = fullscreen ? sf::Style::Fullscreen : sf::Style::Default;
    win->window = new sf::RenderWindow(sf::VideoMode(width, height), title, style);
    win->loop_func = nullptr;
    win->event_func = nullptr;
    win->display_func = nullptr;
    win->pixelarray = nullptr;
    return win;
}

void delete_window(t_artic_window* win)
{
    if (win)
    {
        if (win->window)
        {
            win->window->close();
            delete win->window;
        }
        delete win;
    }
}

t_artic_pixelarray* new_pixelarray(int width, int height)
{
    t_artic_pixelarray* pix = new t_artic_pixelarray();
    pix->width = width;
    pix->height = height;
    pix->pixels = new sf::Uint8[width * height * 4];  // RGBA
    std::memset(pix->pixels, 0, width * height * 4);
    pix->texture.create(width, height);
    pix->sprite.setTexture(pix->texture);
    return pix;
}

void delete_pixelarray(t_artic_pixelarray* pix)
{
    if (pix)
    {
        delete[] pix->pixels;
        delete pix;
    }
}

void artic_set_loop_main_function(t_artic_window* win, t_artic_loop_func func)
{
    if (win)
        win->loop_func = func;
}

void artic_set_key_response(t_artic_window* win, t_artic_event_func func)
{
    if (win)
        win->event_func = func;
}

void artic_set_display_function(t_artic_window* win, t_artic_display_func func)
{
    if (win)
        win->display_func = func;
}

void artic_blit(t_artic_pixelarray* dest, t_artic_pixelarray* src, void* unused)
{
    if (!dest || !src)
        return;

    // Copy pixel data
    std::memcpy(dest->pixels, src->pixels, dest->width * dest->height * 4);
    dest->texture.update(dest->pixels);
    dest->sprite.setTexture(dest->texture);
}

void artic_display(t_artic_window* win)
{
    if (!win || !win->window)
        return;

    win->window->clear();
    if (win->pixelarray)
    {
        win->window->draw(win->pixelarray->sprite);
    }
    win->window->display();
}

void artic_loop(t_artic_window* win, int fps, void* data)
{
    if (!win || !win->window)
        return;

    sf::Clock clock;
    sf::Time timePerFrame = sf::seconds(1.f / fps);

    while (win->window->isOpen())
    {
        sf::Time elapsed = clock.restart();

        // Handle events
        sf::Event event;
        while (win->window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                win->window->close();
                return;
            }
            else if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
            {
                if (win->event_func)
                {
                    t_artic_event_state state = (event.type == sf::Event::KeyPressed) ? GO_DOWN : GO_UP;
                    t_artic_keysym key = static_cast<t_artic_keysym>(event.key.code);
                    t_artic_response resp = win->event_func(state, key, data);
                    if (resp == EXIT_ON_SUCCESS)
                    {
                        win->window->close();
                        return;
                    }
                }
            }
        }

        // Call the loop function
        if (win->loop_func)
        {
            t_artic_response resp = win->loop_func(data);
            if (resp == EXIT_ON_SUCCESS)
            {
                win->window->close();
                return;
            }
        }

        // Call the display function
        if (win->display_func)
        {
            t_artic_response resp = win->display_func(data);
            if (resp == EXIT_ON_SUCCESS)
            {
                win->window->close();
                return;
            }
        }

        // Limit the frame rate
        sf::Time sleepTime = timePerFrame - clock.getElapsedTime();
        if (sleepTime > sf::Time::Zero)
            sf::sleep(sleepTime);
    }
}

// Accessor functions for t_artic_pixelarray
int artic_get_pixelarray_width(t_artic_pixelarray* pix)
{
    if (!pix)
        return 0;
    return pix->width;
}

int artic_get_pixelarray_height(t_artic_pixelarray* pix)
{
    if (!pix)
        return 0;
    return pix->height;
}

uint8_t* artic_get_pixelarray_pixels(t_artic_pixelarray* pix)
{
    if (!pix)
        return nullptr;
    return pix->pixels;
}

void artic_update_pixelarray_texture(t_artic_pixelarray* pix)
{
    if (!pix)
        return;
    pix->texture.update(pix->pixels);
    pix->sprite.setTexture(pix->texture);
}

void artic_set_window_pixelarray(t_artic_window* win, t_artic_pixelarray* pix)
{
    if (!win)
        return;
    win->pixelarray = pix;
}

} // extern "C"
