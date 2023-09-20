all: compile link execute

compile:
	g++ -std=c++20 -I"SFML/include" -I"src" -c src/main.cpp -o build/main.o

link:
	g++ build/main.o -o build/main -L"SFML/lib" -lsfml-graphics -lsfml-window -lsfml-system

execute:
	./build/main
