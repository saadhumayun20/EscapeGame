OBJ = main.o connect.o client.o collisions.o escape.o flyer.o hero.o hollow.o 
EXE = a5
CC = gcc -Wall -g

$(EXE):	$(OBJ)
	$(CC) -o $(EXE) $(OBJ)

main.o: main.c defs.h
	$(CC) -c main.c

connect.o: connect.c defs.h
	$(CC) -c connect.c

client.o: client.c defs.h
	$(CC) -c client.c

collision.o: collision.c defs.h
	$(CC) -c collision.c

escape.o: escape.c defs.h
	$(CC) -c escape.c

flyer.o: flyer.c defs.h
	$(CC) -c flyer.c

hero.o: hero.c defs.h
	$(CC) -c hero.c

hollow.o: hollow.c defs.h
	$(CC) -c hollow.c

clean:
	rm -f $(EXE) $(OBJ)

