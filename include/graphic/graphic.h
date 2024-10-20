#ifndef GRAPHIC_H
#define GRAPHIC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef enum {
    GO_ON,
    EXIT_ON_SUCCESS
} t_artic_response;

typedef enum {
    GO_DOWN,
    GO_UP
} t_artic_event_state;

typedef enum {
    BKS_ESCAPE = 36  // Adjust the value to match SFML's key code for Escape
    // Add other keys as needed
} t_artic_keysym;

// Forward declarations
typedef struct t_artic_window t_artic_window;
typedef struct t_artic_pixelarray t_artic_pixelarray;

// Function pointers
typedef t_artic_response (*t_artic_loop_func)(void *data);
typedef t_artic_response (*t_artic_event_func)(t_artic_event_state state, t_artic_keysym key, void *data);
typedef t_artic_response (*t_artic_display_func)(void *data);

// Function prototypes
t_artic_window* new_window(const char* title, int width, int height, int fullscreen);
t_artic_pixelarray* new_pixelarray(int width, int height);
void delete_window(t_artic_window* win);
void delete_pixelarray(t_artic_pixelarray* pix);
void artic_set_loop_main_function(t_artic_window* win, t_artic_loop_func func);
void artic_set_key_response(t_artic_window* win, t_artic_event_func func);
void artic_set_display_function(t_artic_window* win, t_artic_display_func func);
void artic_loop(t_artic_window* win, int fps, void* data);
void artic_blit(t_artic_pixelarray* dest, t_artic_pixelarray* src, void* unused);
void artic_display(t_artic_window* win);

// Accessor functions for t_artic_pixelarray
int artic_get_pixelarray_width(t_artic_pixelarray* pix);
int artic_get_pixelarray_height(t_artic_pixelarray* pix);
uint8_t* artic_get_pixelarray_pixels(t_artic_pixelarray* pix);
void artic_update_pixelarray_texture(t_artic_pixelarray* pix);

// Function to set the window's pixelarray
void artic_set_window_pixelarray(t_artic_window* win, t_artic_pixelarray* pix);

#ifdef __cplusplus
}
#endif

#endif /* GRAPHIC_H */
