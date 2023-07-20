/*no recibe ningun valor. Imprime las opciones disponibles. Cuando se selecciona un valor correcto
 se devuelve ese valor como entero para ser tomado por la funcion 'efecto'
 */



#include <stdio.h>
#include <stdlib.h>

int menu(void){
	
	int op;
	int row, col;
	
	op=1;
	
	while(op != -1){

	system("clear");
	printf("\n***MENU***");	
	
	printf("\n1)Apilada");
	printf("\n2)Auto Fantastico");
	printf("\n3)Choque");
	printf("\n4)Salir\n");
	scanf("%d",&op);
	
	 switch (op)
	 {
	 case 1: apilada();
	 	op = 0;
		 break;
	 case 2: autofan();
	 	op = 0;
	 	 break;	
	 case 3: choque();
	 	op=0;
		break;

	 case 4: 
		settings();
	 	op = 0;
		break;
	
	case 5: 
		op = -1;

	default: printf("\nOperacion Invalida");
		 break;
	 }
		
	 if (op == -1)
		 break;

	}
}
