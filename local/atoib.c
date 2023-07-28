/*funcion que convierte un entero a binario y luego cada digito se almacena en un elemento de un arreglo de 8 elementos*/

void itob(int numero, int* matrix){
int i,j,aux;
	
  for(i=7;i>=0;i--){
		aux = numero%2;
		if(numero>1)
			matrix[i]=aux;
		if(numero==0)
			matrix[i]=0;
		if(numero==1)
			matrix[i]=numero;
		numero=numero/2;
	}
}
