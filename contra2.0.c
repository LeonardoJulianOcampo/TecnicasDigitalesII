#include <stdio.h>
#include <string.h>
#include <termios.h>


#define CLAVE "abcd"
#define FD_STDIN 0
#define LONGITUD 80

int main() {
	char clave[LONGITUD + 1];
	struct termios t_old, t_new;
	int intento = 0;
	int ingresa = 0;
	char caracter;
	int i = 0;

	tcgetattr(FD_STDIN, &t_old);
	t_new = t_old;
	t_new.c_lflag &= ~(ECHO | ICANON);

	tcsetattr(FD_STDIN,TCSANOW,&t_new);	    
    
    do {
        i = 0;
        printf("\nIntroduzca la clave por favor\n");
        printf("CLAVE: ");
        while (caracter = getchar()) {
            if (caracter == 10) {
                clave[i] = '\0';
                break;
                
            } else if (caracter == 8) {
                if (i > 0) {
                    i--;
                    printf("\b \b");
                }
                
            } else {
                if (i < LONGITUD) {
                    printf("*");
                    clave[i] = caracter;
                    i++;
                }
            }
        }
        
        if (strcmp(clave, CLAVE) == 0) {
            ingresa = 1;
            
        } else {
            printf("\nClave incorrecta. %d/3 Intento",intento+1);
            intento++;
            getchar();
        }
        
    } while (intento < 3 && ingresa == 0);
    
    if (ingresa == 1) {
        printf("\n\t***Ingreso al sistema***\n");
        
    } else {
        printf("\n\tDemasiados intentos!\n");
    }

	tcsetattr(FD_STDIN,TCSANOW, &t_old);

    return 0;
}
