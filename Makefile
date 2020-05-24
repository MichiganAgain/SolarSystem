main: main.o game.o sphere.o shader.o fileManager.o camera.o shape.o
	g++ --std=c++17 -o main main.o game.o sphere.o shader.o fileManager.o camera.o shape.o -lglfw -lGLEW -lGL

main.o: main.cpp game.hpp
	g++ --std=c++17 -c -o main.o main.cpp

game.o: game.cpp game.hpp sphere.hpp shader.hpp camera.hpp
	g++ --std=c++17 -c -o game.o game.cpp

sphere.o: sphere.cpp sphere.hpp shape.hpp
	g++ --std=c++17 -c -o sphere.o sphere.cpp

shader.o: shader.cpp shader.hpp fileManager.hpp
	g++ --std=c++17 -c -o shader.o shader.cpp

fileManager.o: fileManager.cpp fileManager.hpp
	g++ --std=c++17 -c -o fileManager.o fileManager.cpp

camera.o: camera.cpp camera.hpp
	g++ --std=c++17 -c -o camera.o camera.cpp

shape.o: shape.cpp shape.hpp
	g++ --std=c++17 -c -o shape.o shape.cpp

clean:
	rm *.o
	rm main
