NAME = permcpp
EXE = bin\${NAME}.exe
src := $(wildcard src/*.cpp)
obj := $(src:%.cpp=%.o)
FLAGS = -O0 -g -Wall -Wextra -std=c++0x -Wl,-subsystem,windows
#FLAGS = -O3 -std=c++0x
LINKS = -lm -lmingw32 -lSDL2main -lSDL2 -lglew32 -lopengl32 -lglu32
#LINKS = -lm -lSDL2 -lSDL2_image -lSDL2_mixer

all: ${EXE} puzzles

${EXE}: $(obj)
	g++ -o ${EXE} src/glew.c $(obj) ${FLAGS} ${LINKS} -DGLEW_STATIC

$(obj): %.o: %.cpp
	g++ ${FLAGS} -c -o $@ $<

clean:
	rm -rf ${EXE} src/*.o puzzlelist.txt

clean-all:
	rm -rf ${EXE} src/*.o html latex

doc:
	rm -rf html latex
	doxygen doxygen.txt

puzzles: puzzlelist.txt

puzzlelist.txt: genpuzzles.py
	python genpuzzles.py
