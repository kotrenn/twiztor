#include "levelselect.h"

#include "glgraphics.h"
#include "inputsystem.h"

LevelSelect::LevelSelect(Camera *camera)
	:Scene(camera),
	 KeyListener(),
	 MouseListener(),
	 m_puzzleList(NULL),
	 m_puzzleController(NULL),
	 m_prevCameraTime(0),
	 m_moveDuration(1200),
	 m_cameraStartVec(0.0, 0.0),
	 m_cameraGoalVec(0.0, 0.0),
	 m_showingCursor(false)
{
	InputSystem *inputSystem = InputSystem::getInstance();
	inputSystem->addKeyListener(this);
	inputSystem->addMouseListener(this);
	
	m_puzzleList = new PuzzleList();
	m_puzzleList->readPuzzlesFromFile("puzzlelist.txt");
	m_puzzleList->readWorldFromFile("world.txt");

	m_puzzleController = new PuzzleController(m_puzzleList->getCurrentPuzzle());

	moveCamera();
}

LevelSelect::~LevelSelect()
{
	delete m_puzzleList;
}

vec2f LevelSelect::interpolate(float t, const vec2f &a, const vec2f &b) const
{
    // Use 5th-degree polynomial from Perlin noise
	float t3 = t * t * t;
	float t4 = t3 * t;
	float t5 = t4 * t;
	float f = 6 * t5 - 15 * t4 + 10 * t3;
	return (1.0 - f) * a + f * b;
}

void LevelSelect::update()
{
	Uint32 curTime = SDL_GetTicks();
	Uint32 deltaTime = curTime - m_prevCameraTime;
	float t = (float)deltaTime / (float)m_moveDuration;
	if (t > 1.0) t = 1.0;
	vec2f interp = interpolate(t, m_cameraStartVec, m_cameraGoalVec);
	m_camera->lookAt(interp);
}

void LevelSelect::render(GLSystem *glSystem) const
{
	Scene::render(glSystem);

	m_puzzleList->render();

	if (m_showingCursor)
		renderCursor();
}

void LevelSelect::renderCursor() const
{
	GLGraphics *glGraphics = GLGraphics::getInstance();

	int mouseX = 0;
	int mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);
	vec2f point = m_camera->cameraToWorld(vec2f(mouseX, mouseY));
	//cout << point << endl;
	glGraphics->setColor(1.0, 0.0, 1.0);
	glGraphics->drawCircle(point, 0.03 * m_camera->getZoomFactor());
}

void LevelSelect::eventKeyUp(const SDL_KeyboardEvent &key)
{
	unsigned int skip = 10;
	
	switch (key.keysym.sym)
	{
	case SDLK_DOWN:
	case SDLK_LEFT:
	case SDLK_LEFTBRACKET:  m_puzzleList->prevPuzzle(); moveCamera(); break;
	case SDLK_UP:
	case SDLK_RIGHT:
	case SDLK_RIGHTBRACKET: m_puzzleList->nextPuzzle(); moveCamera(); break;
	case SDLK_HOME:         m_puzzleList->firstPuzzle(); moveCamera(); break;
	case SDLK_END:          m_puzzleList->lastPuzzle(); moveCamera(); break;
	case SDLK_PAGEUP:       m_puzzleList->prevPuzzle(skip); moveCamera(); break;
	case SDLK_PAGEDOWN:     m_puzzleList->nextPuzzle(skip); moveCamera(); break;
	default: break;
	}

	m_puzzleController->setPuzzleData(m_puzzleList->getCurrentPuzzle());
}

void LevelSelect::eventMouseButtonUp(const SDL_MouseButtonEvent &mouse)
{
	vec2f worldLoc = m_camera->cameraToWorld(vec2f(mouse.x, mouse.y));
	m_puzzleList->nearestPuzzle(worldLoc);
	moveCamera();
}

void LevelSelect::moveCamera()
{
	m_prevCameraTime = SDL_GetTicks();
	m_cameraStartVec = m_cameraGoalVec;
	m_cameraGoalVec = m_puzzleList->getCurrentPuzzle()->getCenter();
}
