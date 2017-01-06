#ifndef __GL_GRAPHICS_H_
#define __GL_GRAPHICS_H_

#include "color.h"
#include "gldata.h"
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
	void drawCircle(const vec2f &center, float r);
	void drawCircle(float x, float y, float r);

	void setGLData(GLData *glData) { m_glData = glData; }
private:
	GLGraphics();
	static GLGraphics *s_instance;
	
	void loadColorToGL();

	GLData *m_glData;
	Color m_currentColor;
};

#endif
