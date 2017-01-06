#include "glentity.h"

#include "gldata.h"
#include "glgraphics.h"

GLEntity::GLEntity()
	:m_vertexPos2DLocation(-1)
{
}

bool GLEntity::init(GLData &glData)
{
	bool success = true;

	GLuint programID = glData.getProgram()->getProgramID();
	m_vertexPos2DLocation = glGetAttribLocation(programID, "LVertexPos2D");
	if (m_vertexPos2DLocation == -1)
	{
		printf("LVertexPos2D is not a valid glsl program variable!\n");
		success = false;
	}

	return success;
}



CircleGLEntity::CircleGLEntity(float x, float y, float r)
	:GLEntity(),
	 m_x(x),
	 m_y(y),
	 m_r(r),
	 m_numSides(9)
{
}

bool CircleGLEntity::init(GLData &glData)
{
	bool success = true;

	if (!GLEntity::init(glData)) success = false;
	else
	{
	}

	return success;
}

void CircleGLEntity::update()
{
}

void CircleGLEntity::move(Uint32)
{
}

void CircleGLEntity::render() const
{
	GLGraphics *glGraphics = GLGraphics::getInstance();
	
	glGraphics->drawCircle(vec2f(m_x, m_y), m_r);
}
