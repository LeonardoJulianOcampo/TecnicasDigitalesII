#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>

#define EFECTO_LACARRERA 0
#define EFECTO_CHOQUE    1
#define EFECTO_AUTOFAN   2
#define EFECTO_APILADA   3
#define EFECTO_SIRENA    4
#define EFECTO_MOV       5

#define tiempo 100000
#define elements 6





extern pthread_mutex_t key_mutex;

// Variable global para indicar si el hilo de lectura del teclado debe seguir ejecutándose
extern bool keep_reading;
// Variable global para almacenar la última tecla presionada
extern int last_key;
extern int time_factor;
extern int current_time_factor;
extern uint8_t key; //variable que almacena la tecla presionada durante la ejecución de los efectos
extern int s;   // bandera que cambia de valor cuando se presiona F2. Se usa para romper bucles
extern char key_acceso[elements+1];
extern char time_factor_converted[elements+1];
extern char current_key;


/*funcion de conteo de items en menues*/

int counter(int updown, int reset, int count_max);

/*funcion que muestra el menu principal*/
void menu(void);
/*funcion que muestra menu de efectos */
void menu_efectos(WINDOW *win);
/*funcion que muestra menu de ajustes */
void menu_ajustes(void);
/*funcion que gestiona la contrasenia*/
int contrasenia(void);

/*funcion que gestiona los efectos mostrados en los leds*/
int efectos(int);

/*funcion que detecta si flecha-arriba o flecha-abajo se presionaron para subir o bajar la velocidad*/
void *read_keyboard(void *arg);


/*funcion que maneja los leds haciendo uso de la libreria pigpio*/
void interfaz(int *leds);

/*funciones de efectos*/
void autofan(WINDOW *win);
void choque(WINDOW *win);
void lacarrera(WINDOW *win);
void apilada(WINDOW *win);
void sirena(WINDOW *win);
void mov(WINDOW *win);
void cont_binario(WINDOW *win);
void flashh(WINDOW *win);
/*funcion de control de velocidad por teclado*/

int vel(int up_down);
void *read_keyboard(void *arg);

void print_efecto(WINDOW *win, int op);

int open_port(const char * device, uint32_t baud_rate);
int write_port(int fd, uint8_t * buffer, size_t size);
ssize_t read_port(int fd,uint8_t * buffer, size_t size);



