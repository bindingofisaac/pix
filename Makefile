CC=g++
SRC=$(wildcard src/*.cpp)
OBJ=$(addprefix obj/,$(notdir $(SRC:.cpp=.o)))
LD_FLAGS=`pkg-config glew sdl2 --libs` -framework OpenGL
INCLUDES=-I include -std=gnu++11 `pkg-config glew sdl2 --cflags`

all: dir bin/main

dir:
	mkdir -p obj bin

bin/main: $(OBJ)  main.cpp
	$(CC) $(LD_FLAGS) $(INCLUDES) -o $@ $^

obj/%.o: src/%.cpp
	$(CC) $(INCLUDES) -c -o $@ $<

test:
	./bin/main

clean:
	rm -rf bin obj
