#ifndef __GL_GRAPHICS_H_
#define __GL_GRAPHICS_H_

#include "color.h"
#include "gldata.h"
#include "glsystem.h"
#include "vec2f.h"

class GLGraphics
{
public:
	static GLGraphics *getInstance();
	~GLGraphics();
	
	void setColor(float r, float g, float b);
	void setColor(float r, float g, float b, float a);
	void setColor(const Color &color);

	void drawLine(const vec2f &v1, const vec2f &v2);
	void drawLine(float x1, float y1, float x2, float y2);
	void drawCircle(const vec2f &center, float r, bool filled=false);
	void drawCircle(float x, float y, float r, bool filled=false);

	void setGLData(GLData *glData) { m_glData = glData; }
	void setGLSystem(GLSystem *glSystem) { m_glSystem = glSystem; }

	GLSystem *getGLSystem() const { return m_glSystem; }
private:
	GLGraphics();
	static GLGraphics *s_instance;
	
	GLData *m_glData;
	GLSystem *m_glSystem;
	Color m_currentColor;
	
	void loadColorToGL();
	void vertex2f(float x, float y);
};

#endif
