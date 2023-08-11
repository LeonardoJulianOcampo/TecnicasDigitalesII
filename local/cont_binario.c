#include "tpo.h"


void sos(WINDOW *win){
  
  int numero = 0;
  int pigpioInitialized = 0;
  int efecto [16][8] = {{0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {1,1,1,1,1,1,1,1},
                        {0,0,0,0,0,0,0,0},
                        {1,1,1,1,1,1,1,1},
                        {0,0,0,0,0,0,0,0},
                        {1,1,1,1,1,1,1,1},
                        {0,0,0,0,0,0,0,0},
                        {1,1,1,1,1,1,1,1},
                        {1,1,1,1,1,1,1,1},
                        {1,1,1,1,1,1,1,1},
                        {0,0,0,0,0,0,0,0},
                        {1,1,1,1,1,1,1,1},
                        {1,1,1,1,1,1,1,1},
                        {1,1,1,1,1,1,1,1},
                        {0,0,0,0,0,0,0,0}};
  int i;                        
  int leds[8];
  int salir = 0;
  int current_time_factor = 10000;

  keep_reading = true;

  if(gpioInitialise()>=0)
    pigpioInitialized = 1;
  else
    pigpioInitialized = 0;

  nodelay(stdscr,TRUE);
  
  pthread_t thread_id;
  

  if (control_flag)
    pthread_create(&thread_id, NULL, read_keyboard, NULL);
  else 
    pthread_create(&thread_id, NULL, port_thread, NULL);

  itob(0,leds);
  interfaz(leds);

  while(!salir && pigpioInitialized){

    print_efecto(win,EFECTO_SOS,control_flag);
    wrefresh(win);
    
    pthread_mutex_lock(&t_factor_mutex);
    current_time_factor = time_factor;
    salir = s;
    pthread_mutex_unlock(&t_factor_mutex); 
   
    print_efecto(win,EFECTO_SOS,control_flag);
    wrefresh(win);


    for (i=0;i<16;i++){
         interfaz(efecto[i]);
         if(delaynprint(time_factor,win,EFECTO_SOS)){salir=1;break;}
    }
  }

  itob(0,leds);
  interfaz(leds);

  keep_reading = false;
  pthread_join(thread_id, NULL);

  gpioTerminate();
  wrefresh(win);
  nodelay(stdscr,FALSE);
  last_key = ERR;
  s=0;
  salir = 0;
  pthread_cancel(thread_id);
  keep_reading = true;
}
