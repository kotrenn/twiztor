#include "camera.h"

#include "gldata.h"
#include "glgraphics.h"
#include "inputsystem.h"

Camera::Camera()
	:m_viewWidth(1.33333),
	 m_viewHeight(1.0),
	 m_zoomScale(0.42),
	 m_centerX(0.0),
	 m_centerY(0.0),
	 m_rotationAngle(0.0),
	 m_moveSpeed(0.003)
{
	InputSystem *inputSystem = InputSystem::getInstance();
	inputSystem->addKeyListener(this);
	inputSystem->addMouseListener(this);
}

void Camera::lookAt(const vec2f &loc)
{
	m_centerX = loc.getX();
	m_centerY = loc.getY();
}

void Camera::loadToGL() const
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	float left = -0.5 * m_viewWidth / m_zoomScale;
	float right = 0.5 * m_viewWidth / m_zoomScale;
	float bottom = -0.5 * m_viewHeight / m_zoomScale;
	float top = 0.5 * m_viewHeight / m_zoomScale;
	gluOrtho2D(left, right, bottom, top);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float eyeX = m_centerX;
	float eyeY = m_centerY;
	float eyeZ = 1.0;

	float centerX = m_centerX;
	float centerY = m_centerY;
	float centerZ = 0.0;

	float upX = 0.0;
	float upY = 1.0;
	float upZ = 0.0;

	gluLookAt(eyeX, eyeY, eyeZ,
	          centerX, centerY, centerZ,
	          upX, upY, upZ);
}

void Camera::eventKeyDown(const SDL_KeyboardEvent &)
{
	//if (key.keysym.sym == )
}

void Camera::eventMouseMotion(const SDL_MouseMotionEvent &event)
{
	Uint32 buttonState = event.state;
	int deltaX = event.xrel;
	int deltaY = event.yrel;

	if (buttonState == 0) return;
	m_centerX -= deltaX * m_moveSpeed / m_zoomScale;
	m_centerY += deltaY * m_moveSpeed / m_zoomScale;
}

void Camera::eventMouseWheel(const SDL_MouseWheelEvent &event)
{
	int y = event.y;

	float factor = 0.9;
	if (y < 0)
		m_zoomScale *= factor;
	else if (y > 0)
		m_zoomScale /= factor;
}
