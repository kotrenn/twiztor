#include "glgraphics.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <math.h>

GLGraphics *GLGraphics::s_instance = NULL;

GLGraphics *GLGraphics::getInstance()
{
	if (s_instance == NULL)
		s_instance = new GLGraphics();
	return s_instance;
}

GLGraphics::GLGraphics()
	:m_glData(NULL),
	 m_currentColor(1.0, 1.0, 1.0, 1.0)
{
}

GLGraphics::~GLGraphics()
{
}

void GLGraphics::setColor(float r, float g, float b)
{
	m_currentColor = Color(r, g, b);
	loadColorToGL();
}

void GLGraphics::setColor(float r, float g, float b, float a)
{
	m_currentColor = Color(r, g, b, a);
	loadColorToGL();
}

void GLGraphics::setColor(const Color &color)
{
	m_currentColor = color;
	loadColorToGL();
}

void GLGraphics::drawLine(const vec2f &v1, const vec2f &v2)
{
	drawLine(v1.getX(), v1.getY(), v2.getX(), v2.getY());
}

void GLGraphics::drawLine(float x1, float y1, float x2, float y2)
{
	glBegin(GL_LINES);

	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	
	glEnd();
}

void GLGraphics::drawCircle(const vec2f &center, float r)
{
	drawCircle(center.getX(), center.getY(), r);
}

void GLGraphics::drawCircle(float x, float y, float r)
{
	int numSides = 20;
	float dtheta = 2.0 * 3.14159265 / numSides;
	
	//glBegin(GL_LINE_LOOP);
	glBegin(GL_POLYGON);

	for (int i = 0; i < numSides; ++i)
	{

		float theta = i * dtheta;
		float curX = x + r * cos(theta);
		float curY = y + r * sin(theta);
		glVertex2f(curX, curY);
	}
	
	glEnd();
}

void GLGraphics::loadColorToGL()
{
	float r = m_currentColor.getR();
	float g = m_currentColor.getG();
	float b = m_currentColor.getB();
	float a = m_currentColor.getA();
	glColor4f(r, g, b, a);
}
