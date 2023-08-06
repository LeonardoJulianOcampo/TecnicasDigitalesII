#generacion del programa tpo

OBJS = main.o apiladav2.o atoib.o autofan.o choque.o contrasenia.o lacarrera.o interfaz_salida.o menu.o menu_efectos.o menu_ajustes.o counter.o vel.o teclado.o sirena.o move.o print_efecto.o read_s_port.o serial.o s_cntl_mode.o menu_efectos_remoto.o
CFLAGS = -Wall -Wextra -ggdb -o  
COMPILER = gcc 
LFLAGS = -lncurses -lpigpio -lpthread 

tpo: $(OBJS)
	$(COMPILER) $(CFLAGS) tpo $(OBJS) $(LFLAGS) 

main.o: main.c tpo.h
	gcc -c -ggdb main.c

apiladav2.o: apiladav2.c tpo.h
	gcc -c -ggdb apiladav2.c

atoib.o: atoib.c tpo.h
	gcc -c -ggdb atoib.c

autofan.o: autofan.c tpo.h
	gcc -c -ggdb autofan.c

choque.o: choque.c tpo.h
	gcc -c -ggdb choque.c

contrasenia.o: contrasenia.c tpo.h
	gcc -c -ggdb contrasenia.c

efecto.o: efecto.c tpo.h
	gcc -c -ggdb efecto.c

interfaz_salida.o: interfaz_salida.c tpo.h
	gcc -c -ggdb interfaz_salida.c

menu.o: menu.c tpo.h
	gcc -c -ggdb menu.c 

menu_efectos.o: menu_efectos.c tpo.h
	gcc -c -ggdb menu_efectos.c

menu_efectos_remoto.o: menu_efectos_remoto.c tpo.h
	gcc -c -ggdb menu_efectos_remoto.c

menu_ajustes.o: menu_ajustes.c tpo.h
	gcc -c -ggdb menu_ajustes.c

counter.o: counter.c tpo.h
	gcc -c -ggdb counter.c

lacarrera.o: lacarrera.c tpo.h
	gcc -c -ggdb lacarrera.c

vel.o: vel.c tpo.h
	gcc -c -ggdb vel.c

teclado.o: teclado.c tpo.h
	gcc -c -ggdb teclado.c

sirena.o: sirena.c tpo.h
	gcc -c -ggdb sirena.c

move.o: move.c tpo.h
	gcc -c -ggdb move.c

print_efecto.o: print_efecto.c tpo.h
	gcc -c -ggdb print_efecto.c

read_s_port.o: read_s_port.c tpo.h
	gcc -c -ggdb read_s_port.c

serial.o: serial.c tpo.h
	gcc -c -ggdb serial.c

s_cntl_mode.o: s_cntl_mode.c tpo.h
	gcc -c -ggdb s_cntl_mode.c

clean: 
	rm -f *.o

