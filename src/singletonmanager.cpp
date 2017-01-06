#include "singletonmanager.h"

#include "glgraphics.h"
#include "inputsystem.h"

SingletonManager::SingletonManager()
{
	GLGraphics::getInstance();
	InputSystem::getInstance();
}

SingletonManager::~SingletonManager()
{
	delete GLGraphics::getInstance();
	delete InputSystem::getInstance();
}
