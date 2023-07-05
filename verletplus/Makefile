all: compile link

compile:
	g++ -I"SFML/include" -c src/main.cpp -o build/main.o

link:
	g++ build/main.o -o build/main.exe -L"SFML/lib" -lsfml-graphics -lsfml-window -lsfml-system