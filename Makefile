CC=gcc
FLAGS=-Wall
EXE=tema2
EXEv=tema2.g

build: $(EXE)

buildv:$(EXEv)

$(EXE): main.o coada.o stiva.o faux.o
	$(CC) $(FLAGS) $^ -o $(EXE)
$(EXEv):main.c coada.c stiva.c faux.c 
	$(CC) $(FLAGS) -g $^ -o $(EXEv)
main.o: main.c functii.h stiva.h coada.h list.h
	$(CC) $< -c $(FLAFS) -o $@
coada.o: coada.c functii.h stiva.h coada.h list.h
	$(CC) $< -c $(FLAGS) -o $@
stiva.o: stiva.c functii.h stiva.h coada.h list.h
	$(CC) $< -c $(FLAGS) -o $@
faux.o: faux.c functii.h list.h
	$(CC) $< -c $(FLAGS) -o $@ 
.PHONY:clean

clean:
	rm -f *.o $(EXE) $(EXEv)
