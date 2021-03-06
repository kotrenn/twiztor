#ifndef __CAMERA_H_
#define __CAMERA_H_

#include "keylistener.h"
#include "mouselistener.h"
#include "vec2f.h"

class Camera : public KeyListener, MouseListener
{
public:
	Camera();

	void lookAt(const vec2f &loc);

	void loadToGL() const;
	
	void eventKeyDown(const SDL_KeyboardEvent &key);
	void eventMouseMotion(const SDL_MouseMotionEvent &motion);
	void eventMouseWheel(const SDL_MouseWheelEvent &wheel);

	vec2f cameraToWorld(const vec2f &mouseLoc) const;
	vec2f getCenter() const;

	float getZoomFactor() const { return 1.0 / m_zoomScale; }
private:
	float m_viewWidth;
	float m_viewHeight;
	float m_zoomScale;
	float m_centerX;
	float m_centerY;
	float m_offsetX;
	float m_offsetY;
	float m_rotationAngle;
	float m_moveSpeed;
};

#endif
