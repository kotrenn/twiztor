#ifndef __GL_DATA_H_
#define __GL_DATA_H_

#define SDL_MAIN_HANDLED
#define GLEW_STATIC

#include <SDL2/SDL.h>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "common.h"
#include "glslprogram.h"
#include "glsystem.h"
#include "scene.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

class Scene;

class GLData
{
public:
	GLData();
	void printProgramLog(GLuint program);
	void printShaderLog(GLuint shader);
	bool initGL();
	bool init();
	void handleKeys(unsigned char key, int x, int y);
	void render(Scene *scene);
	void close();

	SDL_Window *getWindow() const { return gWindow; }
	//GLuint getProgramID() const { return gProgramID; }
	//GLint getPolygonColorLocation() const { return m_polygonColorLocation; }

	GLSLProgram *getProgram() const { return m_program; }
private:

	SDL_Window *gWindow;
	SDL_GLContext gContext;
	GLSLProgram *m_program;
	//GLuint gProgramID;
	GLint gVertexPos2DLocation;
	GLuint gVBO;
	GLuint gIBO;
	//GLint m_polygonColorLocation;
	GLSystem m_glSystem;
};

#endif
