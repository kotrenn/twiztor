#include "glslprogram.h"

int GLSLProgram::s_currentProgram = 0;

GLSLProgram::GLSLProgram()
{
	create(NULL, NULL, NULL);
}

GLSLProgram::GLSLProgram(const char *vfile, const char *gfile, const char *ffile)
{
	create(vfile, gfile, ffile);
}

GLSLProgram::GLSLProgram(const char *vfile, const char *ffile)
{
	create(vfile, NULL, ffile);
}

GLSLProgram::~GLSLProgram()
{
}

void GLSLProgram::create(const char *vfile, const char *gfile, const char *ffile)
{
	m_canDoVertexShader = isExtensionSupported("GL_ARB_vertex_shader");
	m_canDoGeometryShader = isExtensionSupported("GL_EXT_geometry_shader4");
	m_canDoFragmentShader = isExtensionSupported("GL_ARB_fragment_shader");

	m_inputTopology = GL_TRIANGLES;
	m_outputTopology = GL_TRIANGLE_STRIP;

	m_vertexShader = m_geometryShader = m_fragmentShader = 0;
	m_programID = 0;
	m_attributeLocs.clear();
	m_uniformLocs.clear();
	m_verbose = false;

	m_programID = glCreateProgram();
	checkGLErrors("glCreateProgram");

	if (vfile != NULL && vfile[0] != '\0')
	{
		if (!m_canDoVertexShader)
			cerr << "Warning: this system cannot handle vertex shaders\n";
		
		m_vertexShader = loadVertexShader(vfile);
		int status = compileShader(m_vertexShader);
		if (status != 0)
		{
			if (m_verbose)
				cerr << "Shader " << vfile << " compiled." << endl;
			attachShader(m_vertexShader);
		}
		else
			cerr << "Shader " << vfile << " did not compile." << endl;
	}

	if (gfile != NULL && gfile[0] != '\0')
	{
		if (!m_canDoGeometryShader)
			cerr << "Warning: this system cannot handle geometry shaders\n";

		m_geometryShader = loadGeometryShader(gfile);
		int status = compileShader(m_geometryShader);
		if (status != 0)
		{
			if (m_verbose)
				cerr << "Shader " << gfile << " compiled." << endl;
			attachShader(m_geometryShader);
		}
		else
			cerr << "Shader " << gfile << " did not compile." << endl;
	}

	if (ffile != NULL && ffile[0] != '\0')
	{
		if (!m_canDoFragmentShader)
			cerr << "Warning: this system cannot handle fragment shaders\n";

		m_fragmentShader = loadFragmentShader(ffile);
		int status = compileShader(m_fragmentShader);
		if (status != 0)
		{
			if (m_verbose)
				cerr << "Shader " << ffile << " compiled." << endl;
			attachShader(m_fragmentShader);
		}
		else
			cerr << "Shader " << ffile << " did not compile." << endl;
	}

	linkProgram();
}

GLuint GLSLProgram::loadVertexShader(const char *vfile)
{
	GLuint shader = glCreateShader(GL_VERTEX_SHADER);
	if (loadShader(vfile, shader) != 0)
	{
		if (m_verbose)
			cerr << "Vertex shader " << vfile << " loaded." << endl;
		return shader;
	}
	else
	{
		cerr << "Vertex shader " << vfile << " failed to load." << endl;
		glDeleteShader(shader);
		return 0;
	}
}

GLuint GLSLProgram::loadGeometryShader(const char *gfile)
{
	GLuint shader = glCreateShader(GL_GEOMETRY_SHADER_EXT);
	if (loadShader(gfile, shader) != 0)
	{
		if (m_verbose)
			cerr << "Geometry shader " << gfile << " loaded." << endl;
		return shader;
	}
	else
	{
		cerr << "Geometry shader " << gfile << " failed to load." << endl;
		glDeleteShader(shader);
		return 0;
	}
}

GLuint GLSLProgram::loadFragmentShader(const char *ffile)
{
	GLuint shader = glCreateShader(GL_FRAGMENT_SHADER);
	if (loadShader(ffile, shader) != 0)
	{
		if (m_verbose)
			cerr << "Fragment shader " << ffile << " loaded." << endl;
		return shader;
	}
	else
	{
		cerr << "Fragment shader " << ffile << " failed to load." << endl;
		glDeleteShader(shader);
		return 0;
	}
}

int GLSLProgram::loadShader(const char *fname, GLuint shader)
{
	FILE *in = fopen(fname, "rb");
	if (in == NULL)
	{
		cerr << "Cannot open shader file " << fname << endl;
		return 0;
	}

	fseek(in, 0, SEEK_END);
	int length = ftell(in);
	fseek(in, 0, SEEK_SET);

	GLubyte *buf = new GLubyte[length + 1];
	fread(buf, sizeof(GLubyte), length, in);
	buf[length] = '\0';
	fclose(in);

	glShaderSource(shader, 1, (const char **)&buf, NULL);
	delete [] buf;
	checkGLErrors("loadShader:ShaderSource");
	return 1;
}

int GLSLProgram::compileShader(GLuint shader)
{
	glCompileShader(shader);
	GLint infoLogLen;
	GLint compileStatus;
	checkGLErrors("compileShader:");
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);

	if (compileStatus == 0)
	{
		cerr << "Failed to compile shader.\n";
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);

		if (infoLogLen > 0)
		{
			GLchar *infoLog = new GLchar[infoLogLen + 1];
			glGetShaderInfoLog(shader, infoLogLen, NULL, infoLog);
			infoLog[infoLogLen] = '\0';
			FILE *file = fopen("glsllog.txt", "w");
			fprintf(file, "\n%s\n", infoLog);
			cerr << endl << infoLog << endl;
			fclose(file);
			delete [] infoLog;
		}
		glDeleteShader(shader);
		return 0;
	}

	checkGLErrors("loadShader:compile 2");
	return 1;
}

void GLSLProgram::attachShader(GLuint shader)
{
	glAttachShader(m_programID, shader);
}

int GLSLProgram::linkProgram()
{
	if (m_geometryShader != 0)
	{
		glProgramParameteriEXT(m_programID,
		                       GL_GEOMETRY_INPUT_TYPE_EXT,
		                       m_inputTopology);
		glProgramParameteriEXT(m_programID,
		                       GL_GEOMETRY_OUTPUT_TYPE_EXT,
		                       m_outputTopology);
		glProgramParameteriEXT(m_programID,
		                       GL_GEOMETRY_VERTICES_OUT_EXT,
		                       1024);
	}

	glLinkProgram(m_programID);
	checkGLErrors("loadShader:link 1");

	GLchar *infoLog;
	GLint infoLogLen;
	GLint linkStatus;
	glGetProgramiv(m_programID, GL_LINK_STATUS, &linkStatus);
	checkGLErrors("loadShader:link 2");

	if (linkStatus == 0)
	{
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLen);
		cerr << "Failed to link program--Info LogLength = " << infoLogLen << endl;
		if (infoLogLen > 0)
		{
			infoLog = new GLchar[infoLogLen + 1];
			glGetProgramInfoLog(m_programID, infoLogLen, NULL, infoLog);
			infoLog[infoLogLen] = '\0';
			cerr << "Info Log:" << endl << infoLog << endl;
			delete [] infoLog;
		}

		glDeleteProgram(m_programID);
		glDeleteShader(m_vertexShader);
		glDeleteShader(m_geometryShader);
		glDeleteShader(m_fragmentShader);

		return 0;
	}

	return 1;
}

void GLSLProgram::use()
{
	use(m_programID);
}

void GLSLProgram::use(int programID)
{
	if (programID != s_currentProgram)
	{
		glUseProgram(programID);
		s_currentProgram = programID;
	}
}

int GLSLProgram::getAttributeLocation(const char *name)
{
	map<const char *, int>::iterator pos;

	pos = m_attributeLocs.find(name);
	if (pos == m_attributeLocs.end())
		m_attributeLocs[name] = glGetAttribLocation(m_programID, name);

	return m_attributeLocs[name];
}

void GLSLProgram::setAttribute1i(const char *name, int val)
{
	int loc;
	if ((loc = getAttributeLocation(name)) >= 0)
	{
		use();
		glVertexAttrib1f(loc, (float)val);
	}
}

void GLSLProgram::setAttribute1f(const char *name, float val)
{
	int loc;
	if ((loc = getAttributeLocation(name)) >= 0)
	{
		use();
		glVertexAttrib1f(loc, val);
	}
}

void GLSLProgram::setAttribute2f(const char *name, float val1, float val2)
{
	int loc;
	if ((loc = getAttributeLocation(name)) >= 0)
	{
		use();
		glVertexAttrib2f(loc, val1, val2);
	}
}

void GLSLProgram::setAttribute2fv(const char *name, const float data[2])
{
	int loc;
	if ((loc = getAttributeLocation(name)) >= 0)
	{
		use();
		glVertexAttrib2fv(loc, data);
	}
}

void GLSLProgram::setAttribute2fv(const char *name, const vec2f &vec)
{
	int loc;
	if ((loc = getAttributeLocation(name)) >= 0)
	{
		use();
		glVertexAttrib2f(loc, vec.getX(), vec.getY());
	}
}

void GLSLProgram::setAttribute3f(const char *name, float val1, float val2, float val3)
{
	int loc;
	if ((loc = getAttributeLocation(name)) >= 0)
	{
		use();
		glVertexAttrib3f(loc, val1, val2, val3);
	}
}

void GLSLProgram::setAttribute3fv(const char *name, const float data[3])
{
	int loc;
	if ((loc = getAttributeLocation(name)) >= 0)
	{
		use();
		glVertexAttrib3fv(loc, data);
	}
}

void GLSLProgram::setAttribute3fv(const char *name, const vec3f &vec)
{
	int loc;
	if ((loc = getAttributeLocation(name)) >= 0)
	{
		use();
		glVertexAttrib3f(loc, vec.getX(), vec.getY(), vec.getZ());
	}
}

void GLSLProgram::setAttribute4f(const char *name, float val1, float val2, float val3, float val4)
{
	int loc;
	if ((loc = getAttributeLocation(name)) >= 0)
	{
		use();
		glVertexAttrib4f(loc, val1, val2, val3, val4);
	}
}

void GLSLProgram::setAttribute4fv(const char *name, const float data[4])
{
	int loc;
	if ((loc = getAttributeLocation(name)) >= 0)
	{
		use();
		glVertexAttrib4fv(loc, data);
	}
}

int GLSLProgram::getUniformLocation(const char *name)
{
	map<const char *, int>::iterator pos;

	pos = m_uniformLocs.find(name);
	if (pos == m_uniformLocs.end())
		m_uniformLocs[name] = glGetUniformLocation(m_programID, name);

	return m_uniformLocs[name];
}

void GLSLProgram::setUniform1i(const char *name, int val)
{
	int loc;
	if ((loc = getUniformLocation(name)) >= 0)
	{
		use();
		glUniform1i(loc, val);
	}
}

void GLSLProgram::setUniform1f(const char *name, float val)
{
	int loc;
	if ((loc = getUniformLocation(name)) >= 0)
	{
		use();
		glUniform1f(loc, val);
	}
}

void GLSLProgram::setUniform2f(const char *name, float val1, float val2)
{
	int loc;
	if ((loc = getUniformLocation(name)) >= 0)
	{
		use();
		glUniform2f(loc, val1, val2);
	}
}

void GLSLProgram::setUniform2fv(const char *name, const float data[2])
{
	int loc;
	if ((loc = getUniformLocation(name)) >= 0)
	{
		use();
		glUniform2fv(loc, 1, data);
	}
}

void GLSLProgram::setUniform2fv(const char *name, const vec2f &vec)
{
	int loc;
	if ((loc = getUniformLocation(name)) >= 0)
	{
		use();
		glUniform2f(loc, vec.getX(), vec.getY());
	}
}

void GLSLProgram::setUniform3f(const char *name, float val1, float val2, float val3)
{
	int loc;
	if ((loc = getUniformLocation(name)) >= 0)
	{
		use();
		glUniform3f(loc, val1, val2, val3);
	}
}

void GLSLProgram::setUniform3fv(const char *name, const float data[3])
{
	int loc;
	if ((loc = getUniformLocation(name)) >= 0)
	{
		use();
		glUniform3fv(loc, 1, data);
	}
}

void GLSLProgram::setUniform3fv(const char *name, const vec3f &vec)
{
	int loc;
	if ((loc = getUniformLocation(name)) >= 0)
	{
		use();
		glUniform3f(loc, vec.getX(), vec.getY(), vec.getZ());
	}
}

void GLSLProgram::setUniform4f(const char *name, float val1, float val2, float val3, float val4)
{
	int loc;
	if ((loc = getUniformLocation(name)) >= 0)
	{
		use();
		glUniform4f(loc, val1, val2, val3, val4);
	}
}

void GLSLProgram::setUniform4fv(const char *name, const float data[4])
{
	int loc;
	if ((loc = getUniformLocation(name)) >= 0)
	{
		use();
		glUniform4fv(loc, 1, data);
	}
}

void GLSLProgram::setInputTopology(GLenum t)
{
	if (t != GL_POINTS &&
	    t != GL_LINES &&
	    t != GL_LINES_ADJACENCY_EXT &&
	    t != GL_TRIANGLES &&
	    t != GL_TRIANGLES_ADJACENCY_EXT)
		cerr << "Warning: You have not specified a supported Input Topology" << endl;

	m_inputTopology = t;
}

void GLSLProgram::setOutputTopology(GLenum t)
{
	if (t != GL_POINTS &&
	    t != GL_LINE_STRIP &&
	    t != GL_TRIANGLE_STRIP)
		cerr << "Warning: You have not specified a supported Output Topology" << endl;

	m_outputTopology = t;
}

bool GLSLProgram::isExtensionSupported(const char *extension)
{
	if (extension == NULL || extension[0] == '\0')
		return false;

	GLubyte *where = (GLubyte *)strchr(extension, ' ');
	if (where != 0)
		return false;

	const GLubyte *extensions = glGetString(GL_EXTENSIONS);

	for (const GLubyte *start = extensions; ; )
	{
		where = (GLubyte *)strstr((const char *)start, extension);
		if (where == 0)
			return false;

		GLubyte *terminator = where + strlen(extension);

		if (where == start ||
		    *(where - 1) == '\n' ||
		    *(where - 1) == ' ')
			if (*terminator == ' ' ||
			    *terminator == '\n' ||
			    *terminator == '\0')
				return true;
		start = terminator;
	}
	
	return false;
}

void GLSLProgram::printProgramLog() const
{
	if (glIsProgram(m_programID))
	{
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

		char *infoLog = new char[maxLength];

		glGetProgramInfoLog(m_programID, maxLength, &infoLogLength, infoLog);

		if (infoLogLength > 0)
			cout << infoLog << endl;

		delete[] infoLog;
	}
	else
		cout << "Name " << m_programID << " is not a GLSL program" << endl;
}

void GLSLProgram::printVertexShaderLog() const
{
	printShaderLog(m_vertexShader);
}

void GLSLProgram::printGeometryShaderLog() const
{
	printShaderLog(m_geometryShader);
}

void GLSLProgram::printFragmentShaderLog() const
{
	printShaderLog(m_fragmentShader);
}

void GLSLProgram::printShaderLog(unsigned int shader) const
{
	if (glIsShader(shader))
	{
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		char *infoLog = new char[maxLength];

		glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0)
			cerr << infoLog << endl;

		delete[] infoLog;
	}
	else
	{
		cerr << "Name " << shader << " is not a shader." << endl;
	}
}

void GLSLProgram::checkGLErrors(const char *caller) const
{
	unsigned int gle = glGetError();

	if (gle == GL_NO_ERROR) return;

	cerr << "GL Error discovered from caller %s:" << caller << endl;
	switch (gle)
	{
	case GL_INVALID_ENUM:      cerr << "Invalid enum." << endl; break;
	case GL_INVALID_VALUE:     cerr << "Invalid value." << endl; break;
	case GL_INVALID_OPERATION: cerr << "Invalid operation." << endl; break;
	case GL_STACK_OVERFLOW:    cerr << "Stack overflow." << endl; break;
	case GL_STACK_UNDERFLOW:   cerr << "Stack underflow." << endl; break;
	case GL_OUT_OF_MEMORY:     cerr << "Out of memory." << endl; break;
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		cerr << "Framebuffer object is not complete." << endl; break;
	default: break;
	}
}
