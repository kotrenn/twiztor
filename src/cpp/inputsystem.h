#ifndef __INPUT_SYSTEM_H_
#define __INPUT_SYSTEM_H_

#include "common.h"
#include "keylistener.h"
#include "mouselistener.h"

class InputSystem
{
public:
	static InputSystem *getInstance();
	~InputSystem();

	bool processEvents();

	void addKeyListener(KeyListener *keyListener);
	void removeKeyListener(KeyListener *keyListener);

	void addMouseListener(MouseListener *mouseListener);
	void removeMouseListener(MouseListener *mouseListener);

private:
	InputSystem();
	static InputSystem *s_instance;

	bool eventKeyDown(SDL_Event &event);
	bool eventKeyUp(SDL_Event &event);
	bool eventMouseButtonDown(SDL_Event &event);
	bool eventMouseButtonUp(SDL_Event &event);
	bool eventMouseMotion(SDL_Event &event);
	bool eventMouseWheel(SDL_Event &event);
	
	void synchronizeLists();
	
	set<KeyListener *> m_keyListeners;
	set<KeyListener *> m_addKeyListeners;

	set<MouseListener *> m_mouseListeners;
	set<MouseListener *> m_addMouseListeners;
};

#endif
