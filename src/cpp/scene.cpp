#include "scene.h"

Scene::Scene(Camera *camera)
	:m_camera(camera),
	 m_entityList(),
	 m_previousTime(SDL_GetTicks())
{
}

Scene::~Scene()
{
}

bool Scene::init(GLData &glData)
{
	bool success = true;

	for (GLEntity *entity : m_entityList)
		if (!entity->init(glData))
			success = false;
	
	return success;
}

void Scene::update()
{
	for (GLEntity *entity : m_entityList)
		entity->update();
}

void Scene::move()
{
	Uint32 currentTime = SDL_GetTicks();
	m_previousTimeDelta = currentTime - m_previousTime;
	m_previousTime = currentTime;

	for (GLEntity *entity : m_entityList)
		entity->move(m_previousTimeDelta);
}

void Scene::render(GLSystem *) const
{
	m_camera->loadToGL();
	
	for (GLEntity *entity : m_entityList)
		entity->render();
}

void Scene::addGLEntity(GLEntity *entity)
{
	m_entityList.push_back(entity);
}



TestScene::TestScene()
	:Scene(new Camera()),
	 m_circle(new CircleGLEntity(0.0, 0.0, 0.3))
{
	addGLEntity(m_circle);
}

TestScene::~TestScene()
{
	delete m_circle;
	delete m_camera;
}
