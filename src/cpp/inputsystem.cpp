#include "inputsystem.h"

#include "gfx.h"

InputSystem *InputSystem::s_instance = NULL;

InputSystem *InputSystem::getInstance()
{
	if (s_instance == NULL)
		s_instance = new InputSystem();
	return s_instance;
}

InputSystem::InputSystem()
	:m_keyListeners(),
	 m_addKeyListeners(),
	 m_mouseListeners(),
	 m_addMouseListeners()
{
}

InputSystem::~InputSystem()
{
}

bool InputSystem::processEvents()
{
	bool quit = false;
	
	SDL_Event event;

	synchronizeLists();
	
	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
		case SDL_QUIT: quit = true; break;
		case SDL_KEYDOWN: quit = eventKeyDown(event); break;
		case SDL_KEYUP: quit = eventKeyUp(event); break;
		case SDL_MOUSEBUTTONDOWN: quit = eventMouseButtonDown(event); break;
		case SDL_MOUSEBUTTONUP: quit = eventMouseButtonUp(event); break;
		case SDL_MOUSEMOTION: quit = eventMouseMotion(event); break;
		case SDL_MOUSEWHEEL: quit = eventMouseWheel(event); break;
		default: break;
		};
	}

	return quit;
}

bool InputSystem::eventKeyDown(SDL_Event &event)
{
	bool quit = false;
	
	if (event.key.keysym.sym == SDLK_ESCAPE) quit = true;

	for (KeyListener *keyListener : m_keyListeners)
		keyListener->eventKeyDown(event.key);

	return quit;
}

bool InputSystem::eventKeyUp(SDL_Event &event)
{
	bool quit = false;

	for (KeyListener *keyListener : m_keyListeners)
		keyListener->eventKeyUp(event.key);

	return quit;
}

bool InputSystem::eventMouseButtonDown(SDL_Event &event)
{
	bool quit = false;

	for (MouseListener *mouseListener : m_mouseListeners)
		mouseListener->eventMouseButtonDown(event.button);

	return quit;
}

bool InputSystem::eventMouseButtonUp(SDL_Event &event)
{
	bool quit = false;

	for (MouseListener *mouseListener : m_mouseListeners)
		mouseListener->eventMouseButtonUp(event.button);

	return quit;
}

bool InputSystem::eventMouseMotion(SDL_Event &event)
{
	bool quit = false;
	
	for (MouseListener *mouseListener : m_mouseListeners)
		mouseListener->eventMouseMotion(event.motion);

	return quit;
}

bool InputSystem::eventMouseWheel(SDL_Event &event)
{
	bool quit = false;

	for (MouseListener *mouseListener : m_mouseListeners)
		mouseListener->eventMouseWheel(event.wheel);

	return quit;
}

void InputSystem::addKeyListener(KeyListener *keyListener)
{
	m_addKeyListeners.insert(keyListener);
}

void InputSystem::removeKeyListener(KeyListener *keyListener)
{
	m_keyListeners.erase(keyListener);
}

void InputSystem::addMouseListener(MouseListener *mouseListener)
{
	m_addMouseListeners.insert(mouseListener);
}

void InputSystem::removeMouseListener(MouseListener *mouseListener)
{
	m_mouseListeners.erase(mouseListener);
}

void InputSystem::synchronizeLists()
{
	for (KeyListener *keyListener : m_addKeyListeners)
		m_keyListeners.insert(keyListener);

	for (MouseListener *mouseListener : m_addMouseListeners)
		m_mouseListeners.insert(mouseListener);

	m_addKeyListeners.clear();
	m_addMouseListeners.clear();
}
