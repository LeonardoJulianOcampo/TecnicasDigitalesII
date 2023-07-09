/*no recibe ningun valor. Imprime las opciones disponibles. Cuando se selecciona un valor correcto
 se devuelve ese valor como entero para ser tomado por la funcion 'efecto'
 */



#include <stdio.h>
#include <stdlib.h>

int menu(void){
	
	int op;
	int row, col;
	
	op=1;
	
	while(op!=0){

	system("clear");
	printf("\n***MENU***");	
	
	printf("\n1)Apilada");
	printf("\n2)Auto Fantastico");
	printf("\n3)Choque");
	printf("\n4)Salir");
	scanf("%d",&op);
	
	 switch (op)
	 {
	 case 1: autofan();
	 	op = 0;
		 break;
	 case 2: apilada();
	 	op = 0;
	 	 break;	
	 case 3: choque();
	 	op=0;
		break;
	 default: printf("\nOperacion Invalida");
		 op=0;
		 break;
	 }
		
	}
}
