all: compile link execute

compile:
	g++ -I"SFML/include" -I"src" -c src/main.cpp -o build/main.o

link:
	g++ build/main.o -o build/main.exe -L"SFML/lib" -lsfml-graphics -lsfml-window -lsfml-system

execute:
	./build/main.exe