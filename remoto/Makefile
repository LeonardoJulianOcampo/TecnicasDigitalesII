#generacion del programa tpo-remoto

OBJS = main.o apilada.o autofan.o choque.o contrasenia.o lacarrera.o menu.o menu_efectos.o menu_ajustes.o counter.o vel.o teclado.o sirena.o move.o print_efecto.o serial.o cont_binario.o flash.o
CFLAGS = -o 
COMPILER = gcc -g
LFLAGS = -ltinfo -lncurses -lpthread -lm 

tpo-remoto: $(OBJS)
	$(COMPILER) $(CFLAGS) tpo-remoto $(OBJS) $(LFLAGS) 

main.o: main.c tpo-remoto.h
	gcc -c main.c

apilada.o: apilada.c tpo-remoto.h
	gcc -c apilada.c

autofan.o: autofan.c tpo-remoto.h
	gcc -c autofan.c

choque.o: choque.c tpo-remoto.h
	gcc -c choque.c

contrasenia.o: contrasenia.c tpo-remoto.h
	gcc -c contrasenia.c

efecto.o: efecto.c tpo-remoto.h
	gcc -c efecto.c

interfaz_salida.o: interfaz_salida.c tpo-remoto.h
	gcc -c interfaz_salida.c

menu.o: menu.c tpo-remoto.h
	gcc -c menu.c

menu_efectos.o: menu_efectos.c tpo-remoto.h
	gcc -c menu_efectos.c

menu_ajustes.o: menu_ajustes.c tpo-remoto.h
	gcc -c menu_ajustes.c

counter.o: counter.c tpo-remoto.h
	gcc -c counter.c

lacarrera.o: lacarrera.c tpo-remoto.h
	gcc -c lacarrera.c

vel.o: vel.c tpo-remoto.h
	gcc -c vel.c

teclado.o: teclado.c tpo-remoto.h
	gcc -c teclado.c

sirena.o: sirena.c tpo-remoto.h
	gcc -c sirena.c

move.o: move.c tpo-remoto.h
	gcc -c move.c

cont_binario.o: cont_binario.c tpo-remoto.h
	gcc -c cont_binario.c

flash.o: flash.c tpo-remoto.h
	gcc -c flash.c

print_efecto.o: print_efecto.c tpo-remoto.h
	gcc -c print_efecto.c

serial.o: serial.c tpo-remoto.h
	gcc -c serial.c

clean: 
	rm -f *.o

