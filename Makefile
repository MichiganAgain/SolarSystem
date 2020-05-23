main: main.o game.o sphere.o
	g++ --std=c++17 -o main main.o game.o sphere.o -lglfw -lGLEW -lGL

main.o: main.cpp game.hpp
	g++ --std=c++17 -c -o main.o main.cpp

game.o: game.cpp game.hpp sphere.hpp
	g++ --std=c++17 -c -o game.o game.cpp

sphere.o: sphere.cpp sphere.hpp shape.hpp
	g++ --std=c++17 -c -o sphere.o sphere.cpp

clean:
	rm *.o
	rm main
