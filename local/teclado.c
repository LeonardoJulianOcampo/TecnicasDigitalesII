#include "tpo.h"


// Función para leer el teclado en un hilo separado
void *read_keyboard(void *arg) {
    while (keep_reading) {
        int ch = getch();

         switch (ch){
          case KEY_F(2): s = 1;                break;
          case KEY_UP  : time_factor = vel(1); break;
          case KEY_DOWN: time_factor = vel(0); break;
          default      :                       break;
        }   
    
    }
    return NULL;
}


