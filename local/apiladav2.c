/***********************************************************************************************
 * la funcion cambia su comportamiento dependiendo del flag de seleccion de control remoto o   *
 * local. Cuando se selecciona el modo local time_factor depende del teclado. Cuando se        *
 * selecciona el modo remoto time factor proviene de la función read_s_port que se ejecuta de  *
 * forma concurrente en un hilo secundario. Esta, modifica el valor de time_factor para los    *
 * delays de cada animación                                                                    *
 ***********************************************************************************************/

#include "tpo.h"

bool keep_reading = true;

int last_key = ERR;
uint32_t time_factor = 10000;
int s = 0;
int n = 7;
int tecla;

bool delaynprint(uint32_t delay_time, WINDOW *win){

  int i = 0;

  while(i<=delay_time/1000){
    if(s==1) return true;
    print_efecto(win,3,control_flag);
    mvwprintw(win,16,2,"delay_time:%06d",delay_time);
    wrefresh(win);
    gpioDelay(1000);
    i++;
  }
  return false;
}


void apilada(WINDOW *win){
  int i,k;
  int avalue=1;
  int out=0;
  int mask=0;
  int pigpioInitialized = 0;
  int leds[8];
  int count = 0;
  uint32_t time=70000;

  itob(out,leds);
  
  if(gpioInitialise()>=0)
    pigpioInitialized = 1;
  else{
    pigpioInitialized = 0;
  }

  nodelay(stdscr,TRUE);

  pthread_t thread_id;

  if(control_flag){
    pthread_create(&thread_id,NULL,read_keyboard,NULL);
  }
  else{
    pthread_create(&thread_id,NULL,port_thread,NULL);
  }
  
  interfaz(leds);
  s = 0;

  while(!s && pigpioInitialized){
     
    //print_efecto(win,3,control_flag);
    wrefresh(win); 
    n = 7;
    out = 0;
  
    itob(out,leds);
    interfaz(leds);

    tecla = getch();
    if(tecla == KEY_F(2) || time_factor == 999999) {s=1; continue;} 

    for(int j = 0; j<=7;j++){
    
    avalue = 128;
    mask = 0;
    count = 0;
      
    

        while(count<n){
            
            itob(out | avalue,leds);
            interfaz(leds);
            if(delaynprint(time_factor,win)){s=1;break;}
            
            avalue = avalue >> 1;
            count ++;

        }
        n --;
        count = 0;
        out = out | avalue;
        
        itob(out,leds);
        interfaz(leds);
        if(delaynprint(time_factor,win)){s=1;break;}

        mask = avalue;
      
        itob(out & ~mask,leds);
        interfaz(leds);
        if(delaynprint(time_factor,win)){s=1;break;}

        out = out | mask;

        itob(out,leds);
        interfaz(leds);
        if(delaynprint(time_factor,win)){s=1;break;}

        }
  } //fin while(!s && pigPioInitialized)
  
  keep_reading = false;
  pthread_join(thread_id,NULL);
  pthread_cancel(thread_id);


  itob(0,leds);
  interfaz(leds);
  gpioTerminate();
  wrefresh(win);
  nodelay(stdscr,FALSE);
  keep_reading = true;
  last_key = ERR;
  s = 0;

} //fin funcion void apilada(WINDOW * win)
