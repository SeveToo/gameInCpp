all: compile run	

compile:
	g++ -c src/main.cpp -c src/Game.cpp -c src/Player.cpp -c src/Coin.cpp -I"C:\Users\SeveTo\Documents\libraries\SFML64\include"
	g++ main.o game.o player.o coin.o -o main -L"C:\Users\SeveTo\Documents\libraries\SFML64\lib" -lsfml-graphics -lsfml-window -lsfml-system

run: 
	./main.exe