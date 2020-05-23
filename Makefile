main: main.o game.o
	g++ --std=c++17 -o main main.o game.o -lglfw -lGLEW -lGL

main.o: main.cpp game.hpp
	g++ --std=c++17 -c -o main.o main.cpp

game.o: game.cpp game.hpp
	g++ --std=c++17 -c -o game.o game.cpp

clean:
	rm *.o
	rm main
