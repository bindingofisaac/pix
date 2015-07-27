CC=g++
SRC=$(wildcard src/*.cpp)
OBJ=$(addprefix obj/,$(notdir $(SRC:.cpp=.o)))
LD_FLAGS=`pkg-config freeimage glew sdl2 --libs` -framework OpenGL
INCLUDES=-I include -std=gnu++11 `pkg-config freeimage glew sdl2 --cflags` -I /usr/local/Cellar/glm/0.9.5.3/include/
DEBUG=-g

all: dir bin/main

dir:
	mkdir -p obj bin

bin/main: $(OBJ)  main.cpp
	$(CC) $(DEBUG) $(LD_FLAGS) $(INCLUDES) -o $@ $^

obj/%.o: src/%.cpp
	$(CC) $(DEBUG) $(INCLUDES) -c -o $@ $<

test:
	./bin/main

clean:
	rm -rf bin obj

docs:
	doxygen
