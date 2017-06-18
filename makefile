LINUX = 1
DEBUG = 1
NAME = permcpp

cpp_src := $(wildcard src/cpp/*.cpp)
cpp_obj := $(cpp_src:%.cpp=%.o)
java_src := $(wildcard src/java/permgame/*.java)
java_obj := $(java_src:src/java/permgame/%.java=permgame/%.class)
js_src := $(wildcard src/js/*.js)
puz_src := $(wildcard puzzles/*.txt)
puz_obj := $(puz_src:%.txt=%.puz)
puz_png := $(puz_src:puzzles/%.txt=bin/images/%.png)

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

all: puzzles cpp java js map

# C++
cpp: puzzles ${CPP_EXE}

${CPP_EXE}: $(cpp_obj)
	g++ -o ${CPP_EXE} $(cpp_obj) ${CPP_LINKS} ${CPP_FLAGS}

$(cpp_obj): %.o: %.cpp
	g++ ${CPP_FLAGS} -c -o $@ $<

# Java
java: puzzles $(java_obj)

$(java_obj): permgame/%.class: src/java/permgame/%.java
	javac -d . -cp src/java/ $<

# JS
js: puzzles map bin/js.html bin/game.js

bin/js.html: src/js/index.html
	cp src/js/index.html bin/js.html

bin/game.js: $(js_src) build_js.py puzzles
	python build_js.py

# Puzzles
puzzles: puzzlelist.txt

puzzlelist.txt: genpuzzles.py $(puz_obj)
	python genpuzzles.py

$(puz_obj): %.puz: %.txt compile_puzzle.py
	python compile_puzzle.py $< > $@

# Map
map: bin/map.html

bin/map.html: $(puz_png) map.txt build_map.py
	python build_map.py

bin/images/%.png: puzzles/%.puz render_puzzle.py
	python render_puzzle.py $<

# Doc
doc:
	rm -rf html latex
	doxygen doxygen.txt

# Clean
clean: clean-puzzles clean-cpp clean-java clean-js clean-map clean-doc

clean-cpp:
	rm -rf ${CPP_EXE} src/cpp/*.o permgame

clean-puzzles:
	rm -rf puzzlelist.txt puzzles/*.puz

clean-js:
	rm -rf bin/js.html bin/game.js

clean-doc:
	rm -rf html latex

clean-java:
	rm -rf permgame/*.class

clean-map:
	rm -rf bin/map.html bin/map.png bin/images/*.png out.dot map.dot
