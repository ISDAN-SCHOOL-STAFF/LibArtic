#include <stdio.h>
#include "my_module.h"
#include <artic.h>

typedef struct {
    t_artic_window* win;
    t_artic_pixelarray* pix;
} t_artic_data;

t_artic_response display(void *data)
{
    t_artic_data *d = (t_artic_data *) data;

    // Blit the pixel array onto itself (if needed)
    artic_blit(d->pix, d->pix, NULL);  // Blitting the same pixel array for simplicity

    // Use the accessor function to set the window's pixelarray
    artic_set_window_pixelarray(d->win, d->pix);

    artic_display(d->win);
    return GO_ON;
}

t_artic_response event_handler(t_artic_event_state state, t_artic_keysym key, void *data)
{
    (void)data;  // Suppress unused parameter warning
    if (state == GO_DOWN && key == BKS_ESCAPE)
        return EXIT_ON_SUCCESS;
    return GO_ON;
}

t_artic_response loop(void *data)
{
    (void) data;
    return GO_ON;
}

int main(void)
{
    t_artic_window *win = new_window("ArticWindow", 800, 600, 0);
    t_artic_pixelarray *pix = new_pixelarray(800, 600);

    int width = artic_get_pixelarray_width(pix);
    int height = artic_get_pixelarray_height(pix);
    uint8_t* pixels = artic_get_pixelarray_pixels(pix);

    // Fill the pixel array with pink color
    for (int i = 0; i < width * height * 4; i += 4)
    {
        pixels[i] = 255;       // R
        pixels[i + 1] = 192;   // G
        pixels[i + 2] = 203;   // B
        pixels[i + 3] = 255;   // A
    }

    // Update the texture with the new pixel data
    artic_update_pixelarray_texture(pix);

    t_artic_data data = {win, pix};

    artic_set_loop_main_function(win, loop);
    artic_set_key_response(win, event_handler);
    artic_set_display_function(win, display);
    artic_loop(win, 60, &data);

    // Clean up
    delete_pixelarray(pix);
    delete_window(win);
    return 0;
}
