#include "tpo.h"

void rafaga(WINDOW *win){

  uint8_t numero = 0;
  int pigpioInitialized = 0;
  int leds[8];
  int efectos[13][8] = {{0,0,0,1,1,0,0,0},
                        {0,0,1,0,0,1,0,1},
                        {0,1,0,1,1,0,1,0},
                        {1,0,1,0,0,1,0,1},
                        {0,1,0,1,1,0,1,0},
                        {1,0,1,0,0,1,0,1},
                        {0,1,0,1,1,0,1,0},
                        {1,0,1,0,0,1,0,1},
                        {0,1,0,0,0,0,1,0},
                        {1,0,0,0,0,0,0,1},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0}};
  int i = 0;
  int salir = 0;
  int current_time_factor = 10000;

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

  while(!salir && pigpioInitialized){
    
    pthread_mutex_lock(&t_factor_mutex);
    current_time_factor = time_factor;
    salir = s;
    pthread_mutex_unlock(&t_factor_mutex); 

    print_efecto(win,EFECTO_RAFAGA,control_flag);
    wrefresh(win);
    
    itob(0,leds);
    interfaz(leds);


    for(i=0;i<13;i++){    
      
      interfaz(efectos[i]);
      if(delaynprint(time_factor,win,EFECTO_RAFAGA)){salir=1;break;}
       
    } 
  }
  
 
  keep_reading = false;
  pthread_join(thread_id, NULL);

  itob(0,leds);
  interfaz(leds);

  gpioTerminate();
  wrefresh(win);
  nodelay(stdscr,FALSE);
  last_key = ERR;
  salir=0;
  s = 0;
  pthread_cancel(thread_id);
  keep_reading = true;
}
