#include "tpo-remoto.h"

pthread_mutex_t key_mutex = PTHREAD_MUTEX_INITIALIZER;


// Función para leer el teclado en un hilo separado
void *read_keyboard(void *arg) {
    while (keep_reading) {
        int ch = getch();
	switch(ch){

		case KEY_F(2)  : 
				pthread_mutex_lock(&key_mutex);
				key = '4';
				pthread_mutex_unlock(&key_mutex);
				s = 1;
				break;
		case KEY_UP    :
				pthread_mutex_lock(&key_mutex);
				key = '1';
				time_factor = vel(0);
				pthread_mutex_unlock(&key_mutex);
				break;
		case KEY_DOWN  : 
				pthread_mutex_lock(&key_mutex);	
				key = '2';
				time_factor = vel(1); 
				pthread_mutex_unlock(&key_mutex);
				break;
		default        :         
				pthread_mutex_lock(&key_mutex); 
				key = '0';
				pthread_mutex_unlock(&key_mutex);
				 break;
	
	}

    }
    return NULL;
}



