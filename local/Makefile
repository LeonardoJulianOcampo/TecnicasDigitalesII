#generacion del programa tpo

OBJS = main.o apilada.o atoib.o autofan.o choque.o contrasenia.o lacarrera.o interfaz_salida.o menu.o menu_efectos.o menu_ajustes.o counter.o vel.o teclado.o sirena.o move.o print_efecto.o
CFLAGS = -o 
COMPILER = gcc -g
LFLAGS = -lncurses -lpigpio -lpthread 

tpo: $(OBJS)
	$(COMPILER) $(CFLAGS) tpo $(OBJS) $(LFLAGS) 

main.o: main.c tpo.h
	gcc -c main.c

apilada.o: apilada.c tpo.h
	gcc -c apilada.c

atoib.o: atoib.c tpo.h
	gcc -c atoib.c

autofan.o: autofan.c tpo.h
	gcc -c autofan.c

choque.o: choque.c tpo.h
	gcc -c choque.c

contrasenia.o: contrasenia.c tpo.h
	gcc -c contrasenia.c

efecto.o: efecto.c tpo.h
	gcc -c efecto.c

interfaz_salida.o: interfaz_salida.c tpo.h
	gcc -c interfaz_salida.c

menu.o: menu.c tpo.h
	gcc -c menu.c 

menu_efectos.o: menu_efectos.c tpo.h
	gcc -c menu_efectos.c

menu_ajustes.o: menu_ajustes.c tpo.h
	gcc -c menu_ajustes.c

counter.o: counter.c tpo.h
	gcc -c counter.c

lacarrera.o: lacarrera.c tpo.h
	gcc -c lacarrera.c

vel.o: vel.c tpo.h
	gcc -c vel.c

teclado.o: teclado.c tpo.h
	gcc -c teclado.c

sirena.o: sirena.c tpo.h
	gcc -c sirena.c

move.o: move.c tpo.h
	gcc -c move.c

print_efecto.o: print_efecto.c tpo.h
	gcc -c print_efecto.c

clean: 
	rm -f *.o

