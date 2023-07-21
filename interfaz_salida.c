/*funcion que toma un arreglo de 8 elementos y enciende o apaga los leds de salida dependiendo del valor de estos elementos*/

#define LED1 24
#define LED2 25
#define LED3 8
#define LED4 7
#define LED5 12
#define LED6 16
#define LED7 20
#define LED8 21
#include<pigpio.h>


void interfaz(int *leds){
	gpioWrite(LED1,leds[0]);
	gpioWrite(LED2,leds[1]);
	gpioWrite(LED3,leds[2]);
	gpioWrite(LED4,leds[3]);
	gpioWrite(LED5,leds[4]);
	gpioWrite(LED6,leds[5]);
	gpioWrite(LED7,leds[6]);
	gpioWrite(LED8,leds[7]);
}
