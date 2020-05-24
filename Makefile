objects = main.o game.o sphere.o shader.o fileManager.o camera.o shape.o textures.o cube.o lightSource.o

main: $(objects)
	g++ --std=c++17 -o main $(objects) -lglfw -lGLEW -lGL

main.o: main.cpp game.hpp
	g++ --std=c++17 -c -o main.o main.cpp

game.o: game.cpp game.hpp sphere.hpp shader.hpp camera.hpp textures.hpp cube.hpp lightSource.o
	g++ --std=c++17 -c -o game.o game.cpp

sphere.o: sphere.cpp sphere.hpp shape.hpp textures.hpp shader.hpp
	g++ --std=c++17 -c -o sphere.o sphere.cpp

shader.o: shader.cpp shader.hpp fileManager.hpp
	g++ --std=c++17 -c -o shader.o shader.cpp

fileManager.o: fileManager.cpp fileManager.hpp
	g++ --std=c++17 -c -o fileManager.o fileManager.cpp

camera.o: camera.cpp camera.hpp
	g++ --std=c++17 -c -o camera.o camera.cpp

shape.o: shape.cpp shape.hpp textures.hpp shader.hpp
	g++ --std=c++17 -c -o shape.o shape.cpp

textures.o: textures.cpp textures.hpp
	g++ --std=c++17 -c -o textures.o textures.cpp

cube.o: cube.cpp cube.hpp shape.hpp shader.hpp textures.hpp
	g++ --std=c++17 -c -o cube.o cube.cpp

lightSource.o: lightSource.cpp lightSource.hpp shape.hpp cube.hpp sphere.hpp shader.hpp textures.hpp
	g++ --std=c++17 -c -o lightSource.o lightSource.cpp

clean:
	rm *.o
	rm main
