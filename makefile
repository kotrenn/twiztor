LINUX = 1
DEBUG = 1
NAME = permcpp

src := $(wildcard src/cpp/*.cpp)
obj := $(src:%.cpp=%.o)
puz_src := $(wildcard puzzles/*.txt)
puz_obj := $(puz_src:%.txt=%.puz)

WIN_LINKS = -lm -lmingw32 -lSDL2main -lSDL2 -lglew32 -lopengl32 -lglu32 src/cpp/glew.c -DGLEW_STATIC
LIN_LINKS = -lm -lSDL2 -lSDL2_image -lSDL2_mixer -lGL -lGLU -lGLEW

O0_FLAGS = -O0 -g -Wall -Wall -Wextra
O3_FLAGS = -O3

WIN_FLAGS = -Wl,-subsystem,windows
LIN_FLAGS =

WIN_EXE = bin\${NAME}.exe
LIN_EXE = bin/${NAME}

OPT_FLAGS = $(O0_FLAGS)
OS_FLAGS = $(WIN_FLAGS)

FLAGS = $(OPT_FLAGS) $(OS_FLAGS) -std=c++0x
LINKS = $(WIN_LINKS)
EXE = $(WIN_EXE)

all: ${EXE} puzzles

${EXE}: $(obj)
	g++ -o ${EXE} $(obj) ${FLAGS} ${LINKS}

$(obj): %.o: %.cpp
	g++ ${FLAGS} -c -o $@ $<

clean:
	rm -rf ${EXE} src/cpp/*.o puzzlelist.txt puzzles/*.puz

clean-all:
	rm -rf ${EXE} src/cpp/*.o puzzlelist.txt puzzles/*.puz html latex

doc:
	rm -rf html latex
	doxygen doxygen.txt

puzzles: puzzlelist.txt

puzzlelist.txt: genpuzzles.py compile_puzzle.py $(puz_obj)
	python genpuzzles.py

$(puz_obj): %.puz: %.txt
	python compile_puzzle.py $< > $@
