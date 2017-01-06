#ifndef __KEY_LISTENER_H_
#define __KEY_LISTENER_H_

#include <SDL2/SDL.h>

class KeyListener
{
public:
	virtual ~KeyListener() {}

	virtual void eventKeyDown(const SDL_KeyboardEvent &) {}
	virtual void eventKeyUp(const SDL_KeyboardEvent &) {}
};

#endif
