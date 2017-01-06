#ifndef __GL_ENTITY_H
#define __GL_ENTITY_H

#define GLEW_STATIC

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>

#include "common.h"

class GLData;

class GLEntity
{
public:
	GLEntity();
	virtual ~GLEntity() {}
	
	virtual bool init(GLData &glData);
	virtual void update() = 0;
	virtual void move(Uint32 timeDelta) = 0;
	virtual void render() const = 0;
private:
	GLint m_vertexPos2DLocation;
};

class CircleGLEntity : public GLEntity
{
public:
	CircleGLEntity(float x, float y, float r);
	virtual ~CircleGLEntity() {}

	bool init(GLData &glData);
	void update();
	void move(Uint32 timeDelta);
	void render() const;

	void setPosition(float x, float y) { m_x = x; m_y = y; }

	float getX() const { return m_x; }
	float getY() const { return m_y; }
private:
	float m_x;
	float m_y;
	float m_r;
	int m_numSides;
};

#endif
