#ifndef __SCENE_H_
#define __SCENE_H_

#include "camera.h"
#include "common.h"
#include "gldata.h"
#include "glentity.h"
#include "glsystem.h"

class GLData;

class Scene
{
public:
	Scene(Camera *camera);
	virtual ~Scene();

	virtual bool init(GLData &glData);
	virtual void update();
	virtual void move();
	virtual void render(GLSystem *glSystem) const;

	void addGLEntity(GLEntity *entity);
protected:
	Camera *m_camera;
	vector<GLEntity *> m_entityList;
	Uint32 m_previousTime;
	Uint32 m_previousTimeDelta;
};
	

class TestScene : public Scene
{
public:
	TestScene();
	virtual ~TestScene();
private:
	CircleGLEntity *m_circle;
};

#endif
