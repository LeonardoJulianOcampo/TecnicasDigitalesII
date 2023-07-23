#include <ncurses.h>
#include "tpo.h"


// Variable global para indicar si el hilo de lectura del teclado debe seguir ejecutándose
extern bool keep_reading;
// Variable global para almacenar la última tecla presionada
extern int last_key;
extern uint32_t time_factor;
extern int s;

// Función para leer el teclado en un hilo separado
void *read_keyboard(void *arg) {
    while (keep_reading) {
        int ch = getch();
        if (ch != ERR) {
	printw("%d",1);
	    if      (ch == KEY_F(2)) s = 1;
	    else if (ch == KEY_UP)   time_factor = vel(1);
	    else if (ch == KEY_DOWN) time_factor = vel(0);
	    else                     time_factor = time_factor;
	

	}
    }
    return NULL;
}
