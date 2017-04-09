#include "gldata.h"

GLData::GLData()
{
	gWindow = NULL;
	m_program = NULL;
	//gProgramID = 0;
	gVertexPos2DLocation = -1;
	gVBO = 0;
	gIBO = 0;
	//m_polygonColorLocation = -1;
	m_glSystem = GLSystem();
}

void GLData::printProgramLog(GLuint program)
{
	if (glIsProgram(program))
	{
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		char *infoLog = new char[maxLength];

		glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0)
		{
			printf("%s\n", infoLog);
		}

		delete[] infoLog;
	}
	else
	{
		printf("Name %d is not a program\n", program);
	}
}

void GLData::printShaderLog(GLuint shader)
{
	if (glIsShader(shader))
	{
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		char *infoLog = new char[maxLength];

		glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0)
		{
			printf("%s\n", infoLog);
		}

		delete[] infoLog;
	}
	else
	{
		printf("Name %d is not a shader\n", shader);
	}
}

bool GLData::initGL()
{
	bool success = true;

	//gProgramID = glCreateProgram();
	m_program = new GLSLProgram("shaders/simple.vert", "shaders/simple.frag");

	/*
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	const GLchar *vertexShaderSource[] = { "#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }" };

	glShaderSource(vertexShader, 1, vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	GLint vShaderCompiled = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
	if (vShaderCompiled != GL_TRUE)
	{
		printf("Unable to compile vertex shader %d!\n", vertexShader);
		printShaderLog(vertexShader);
		success = false;
	}
	else
	{
		glAttachShader(gProgramID, vertexShader);
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		//const GLchar *fragmentShaderSource[] = { "#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }" };
		const GLchar *fragmentShaderSource[] = { "#version 140\nout vec4 LFragment; uniform vec4 LPolygonColor = vec4(1.0, 1.0, 1.0, 1.0); void main() { gl_FragColor = LPolygonColor; }" };

		glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		GLint fShaderCompiled = GL_FALSE;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
		if (fShaderCompiled != GL_TRUE)
		{
			printf("Unable to compile fragment shader %d!\n", fragmentShader);
			printShaderLog(fragmentShader);
			success = false;
		}
		else
		{
			glAttachShader(gProgramID, fragmentShader);
			glLinkProgram(gProgramID);

			GLint programSuccess = GL_TRUE;
			glGetProgramiv(gProgramID, GL_LINK_STATUS, &programSuccess);
			if (programSuccess != GL_TRUE)
			{
				printf("Error linking program %d!\n", gProgramID);
				printProgramLog(gProgramID);
				success = false;
			}
			else
			{
				glClearColor(0.f, 0.f, 0.f, 1.f);

				m_polygonColorLocation = glGetUniformLocation(gProgramID, "LPolygonColor");
				if (m_polygonColorLocation == -1)
				{
					printf("LPolygonColor is not a valid glsl program variable!\n");
				}
			}
		}
	}
	*/

	return success;
}

bool GLData::init()
{
	bool success = true;
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize!  SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Use OpenGL 3.1 core
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

		gWindow = SDL_CreateWindow("PermC++", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created!  SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Create context
			gContext = SDL_GL_CreateContext(gWindow);
			if (gContext == NULL)
			{
				printf("OpenGL context could not be created!  SDL_Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				glewExperimental = GL_TRUE;
				GLenum glewError = glewInit();
				if (glewError != GLEW_OK)
				{
					printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
				}

				if (SDL_GL_SetSwapInterval(1) < 0)
				{
					printf("Warning: Unable to set VSync! SDL_Error: %s\n", SDL_GetError());
				}
				
				if (!initGL())
				{
					printf("Unable to initialize OpenGL");
					success = false;
				}
			}
		}
	}

	return success;
}

void GLData::render(Scene *scene)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//glUseProgram(gProgramID);
	m_program->use();

	scene->render(&m_glSystem);
		
	glUseProgram((GLuint)NULL);
}

void GLData::close()
{
	//glDeleteProgram(gProgramID);
	delete m_program;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();
}
