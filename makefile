game:main.o
	g++ main.o -o game -lsfml-graphics -lsfml-window -lsfml-system

main.o:main.cpp
	g++ -c main.cpp

.PHONY: all run

all:
	make -s
	make -s run

run:
	./game

