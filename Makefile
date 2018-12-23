# valid makes:
#	'make' : makes all
#	'make clean' : deletes all files specified by OUT and OBJ

# $< == first dependency, $^ == all dependencies, $@ == target

# declaring paths for source files

SRC = $(wildcard src/*.c src/*.cpp)
DEP = $(wildcard src/*.h src/*.hpp)


OBJ := $(patsubst src/%.cpp, obj/%.o, $(SRC))
OBJ := $(patsubst src/%.c, obj/%.o, $(OBJ))


CC = g++
CFLAGS = -c -IC:/mingwdev/opengl/include
INCLUDE = -IC:/mingwdev/opengl/include
LFLAGS = -LC:/mingwdev/lib -LC:/mingwdev/opengl/lib -lmingw32 -lopengl32 -lglew32 -lglfw3dll
MAIN = SixLegends

.PHONY: clean

# our main build rules
all: $(MAIN)

# target : dependencies
# 	recipe
$(MAIN): $(OBJ)
	$(CC) $^ $(LFLAGS) -o $(MAIN)


# compile source files to /obj/ (no linking)
# if a header changes, src will recompile
obj/%.o: src/%.c $(DEP)
	$(CC) $< $(CFLAGS) -o $@

obj/%.o: src/%.cpp $(DEP)
	$(CC) $< $(CFLAGS) -o $@
	
clean:
	rm -f $(OBJ) $(MAIN).exe 

