/*funcion de conteo de items en menues*/

int counter(int updown);

/*funcion que muestra el menu principal*/
int menu(void);

/*funcion que gestiona la contrasenia*/
int contrasenia(void);

/*funcion que gestiona los efectos mostrados en los leds*/
int efecto(int);

/*funcion que detecta si flecha-arriba o flecha-abajo se presionaron para subir o bajar la velocidad*/


/*funcion que convierte un entero a binario y luego almacena cada digito en un elemento de un array de 8 elementos*/
void itob(int numero, int *matrix);

/*funcion que maneja los leds haciendo uso de la libreria pigpio*/
void interfaz(int *leds);

/*funcion para ejecutar el efecto de autofantastico*/
void autofan(void);

void choque(void);
void lacorrida(void);
void apilada(void);

