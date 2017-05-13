LINUX = 1
DEBUG = 1
NAME = permcpp

cpp_src := $(wildcard src/cpp/*.cpp)
cpp_obj := $(cpp_src:%.cpp=%.o)
java_src := $(wildcard src/java/permgame/*.java)
java_obj := $(java_src:src/java/permgame/%.java=permgame/%.class)
puz_src := $(wildcard puzzles/*.txt)
puz_obj := $(puz_src:%.txt=%.puz)

WIN_LINKS = src/glew.c -lm -lmingw32 -lSDL2main -lSDL2 -lglew32 -lopengl32 -lglu32 -DGLEW_STATIC
LIN_LINKS = -lm -lSDL2 -lSDL2_image -lSDL2_mixer -lGL -lGLU -lGLEW

O0_FLAGS = -O0 -g -Wall -Wall -Wextra
O3_FLAGS = -O3

WIN_FLAGS = -Wl,-subsystem,windows
LIN_FLAGS =

WIN_EXE = bin\${NAME}.exe
LIN_EXE = bin/${NAME}

OPT_FLAGS = $(O0_FLAGS)
OS_FLAGS = $(LIN_FLAGS)

CPP_FLAGS = $(OPT_FLAGS) $(OS_FLAGS) -std=c++0x
CPP_LINKS = $(LIN_LINKS)
CPP_EXE = $(LIN_EXE)

all: cpp java js

# C++
cpp: ${CPP_EXE} puzzles

${CPP_EXE}: $(cpp_obj)
	g++ -o ${CPP_EXE} $(cpp_obj) ${CPP_LINKS} ${CPP_FLAGS}

$(cpp_obj): %.o: %.cpp
	g++ ${CPP_FLAGS} -c -o $@ $<

# Java
java: $(java_obj) puzzles

$(java_obj): permgame/%.class: src/java/permgame/%.java
	javac -d . -cp src/java/ $<

# JS
js: bin/game.js puzzles

bin/game.js: src/js/game.js buildjs.py puzzles
	python buildjs.py

# Puzzles
puzzles: puzzlelist.txt

puzzlelist.txt: genpuzzles.py compile_puzzle.py $(puz_obj)
	python genpuzzles.py

$(puz_obj): %.puz: %.txt
	python compile_puzzle.py $< > $@

# Doc
doc:
	rm -rf html latex
	doxygen doxygen.txt

# Clean
clean:
	rm -rf ${CPP_EXE} src/cpp/*.o permgame puzzlelist.txt puzzles/*.puz bin/js.html bin/game.js

clean-all: clean
	rm -rf html latex
