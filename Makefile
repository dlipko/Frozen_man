# Это комментарий, который говорит, что переменная CC указывает компилятор, используемый для сборки
CC=g++
#Это еще один комментарий. Он поясняет, что в переменной CFLAGS лежат флаги, которые передаются компилятору
CFLAGS=-c 
SFML_FLAGS=-lsfml-graphics -lsfml-window -lsfml-system

all: new_year_game

new_year_game: main.o Enemy.o Enemies.o Entity.o map.o player.o Snowball.o Snowballs.o 
	$(CC) main.o Enemies.o Enemy.o Entity.o map.o player.o Snowball.o Snowballs.o -o new_year_game $(SFML_FLAGS)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

Enemy.o : Enemy.cpp
	$(CC) $(CFLAGS) Enemy.cpp

Enemies.o: Enemies.cpp
	$(CC) $(CFLAGS) Enemies.cpp

Entity.o: Entity.cpp
	$(CC) $(CFLAGS) Entity.cpp

map.o: map.cpp
	$(CC) $(CFLAGS) map.cpp

player.o: player.cpp
	$(CC) $(CFLAGS) player.cpp

Snowball.o: Snowball.cpp
	$(CC) $(CFLAGS) Snowball.cpp

Snowballs.o: Snowballs.cpp
	$(CC) $(CFLAGS) Snowballs.cpp

clean:
	rm -rf *.o new_year_game