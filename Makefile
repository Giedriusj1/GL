OBJS = control.o main.o objectLoader.o render.o shader.o marchingCubesHelper.o shaderManager.o noise.o list.o objLoader.o obj_parser.o string_extra.o network.o
CC = clang++
DEBUG = -g3
CFLAGS = -Wall -std=c++11 -c $(DEBUG)
LFLAGS = -Wall $(DEBUG) -L/usr/lib64 -lGLEW -lGLU -lGL  -lglut -lpthread


all:  $(OBJS) 
	$(CC) $(LFLAGS) $(OBJS) -o supergl


control.o: 
	$(CC) $(CFLAGS) src/control.cpp

main.o: 
	$(CC) $(CFLAGS) src/main.cpp


objectLoader.o: 
	$(CC)  $(CFLAGS) src/objectLoader.cpp -c

render.o: 
	$(CC) $(CFLAGS)  src/render.cpp -c

shaderManager.o: 
	$(CC) $(CFLAGS)  src/shaderManager.cpp -c


shader.o: 
	$(CC) $(CFLAGS)  src/shader.cpp -c

marchingCubesHelper.o: 
	$(CC) $(CFLAGS)  src/marchingCubesHelper.cpp -c


noise.o: 
	$(CC) $(CFLAGS)  src/noise.cpp -c

list.o: 
	$(CC) $(CFLAGS)  src/objLoader/list.cpp -c -w

objLoader.o: 
	$(CC) $(CFLAGS)  src/objLoader/objLoader.cpp -c -w

obj_parser.o: 
	$(CC) $(CFLAGS)  src/objLoader/obj_parser.cpp -c -w

string_extra.o: 
	$(CC) $(CFLAGS) src/objLoader/string_extra.cpp -c -w

network.o: 
	$(CC) $(CFLAGS) src/network/network.cpp -c -w

clean:
	rm *.o
	rm supergl
