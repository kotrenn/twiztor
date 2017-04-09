#ifndef __MOUSE_LISTENER_H_
#define __MOUSE_LISTENER_H_

#include <SDL2/SDL.h>

class MouseListener
{
public:
	MouseListener() {}
	virtual ~MouseListener() {}

	virtual void eventMouseMotion(const SDL_MouseMotionEvent &) {}
	virtual void eventMouseButtonDown(const SDL_MouseButtonEvent &) {}
	virtual void eventMouseButtonUp(const SDL_MouseButtonEvent &) {}
	virtual void eventMouseWheel(const SDL_MouseWheelEvent &) {}
};

#endif
