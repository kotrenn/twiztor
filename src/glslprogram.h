#ifndef __GLSL_PROGRAM_H_
#define __GLSL_PROGRAM_H_

#define GLEW_STATIC

#include <SDL2/SDL.h>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "common.h"
#include "vec2f.h"
#include "vec3f.h"

class GLSLProgram
{
public:
	GLSLProgram();
	GLSLProgram(const char *vfile, const char *gfile, const char *ffile);
	GLSLProgram(const char *vfile, const char *ffile);
	~GLSLProgram();

	// Set Attributes
	void setAttribute1i(const char *name, int val);
	void setAttribute1f(const char *name, float val);
	
	void setAttribute2f(const char *name, float val1, float val2);
	void setAttribute2fv(const char *name, const float data[2]);
	void setAttribute2fv(const char *name, const vec2f &vec);
	
	void setAttribute3f(const char *name, float val1, float val2, float val3);
	void setAttribute3fv(const char *name, const float data[3]);
	void setAttribute3fv(const char *name, const vec3f &vec);
	
	void setAttribute4f(const char *name, float val1, float val2, float val3, float val4);
	void setAttribute4fv(const char *name, const float data[4]);

	// Set Uniforms
	void setUniform1i(const char *name, int val);
	void setUniform1f(const char *name, float val);

	void setUniform2f(const char *name, float val1, float val2);
	void setUniform2fv(const char *name, const float data[2]);
	void setUniform2fv(const char *name, const vec2f &vec);
	
	void setUniform3f(const char *name, float val1, float val2, float val3);
	void setUniform3fv(const char *name, const float data[3]);
	void setUniform3fv(const char *name, const vec3f &vec);
	
	void setUniform4f(const char *name, float val1, float val2, float val3, float val4);
	void setUniform4fv(const char *name, const float data[4]);

	// Set Topologies
	void setInputTopology(GLenum t);
	void setOutputTopology(GLenum t);

	void use();
	void use(int programID);

	bool isExtensionSupported(const char *extension);

	void setVerbose(bool verbose) { m_verbose = verbose; }
	void printProgramLog() const;
	void printVertexShaderLog() const;
	void printGeometryShaderLog() const;
	void printFragmentShaderLog() const;

	GLuint getProgramID() const { return m_programID; }
private:
	void create(const char *vfile, const char *gfile, const char *ffile);
	GLuint loadVertexShader(const char *vfile);
	GLuint loadGeometryShader(const char *gfile);
	GLuint loadFragmentShader(const char *ffile);
	int loadShader(const char *fname, GLuint shader);
	int compileShader(GLuint shader);
	void attachShader(GLuint shader);
	int linkProgram();
	int getAttributeLocation(const char *name);
	int getUniformLocation(const char *name);
	
	void printShaderLog(unsigned int shader) const;
	void checkGLErrors(const char *caller) const;

	static int s_currentProgram;
	
	GLuint m_programID;
	bool m_canDoVertexShader;
	bool m_canDoGeometryShader;
	bool m_canDoFragmentShader;
	GLenum m_inputTopology;
	GLenum m_outputTopology;
	unsigned int m_vertexShader;
	unsigned int m_geometryShader;
	unsigned int m_fragmentShader;
	map<const char *, int> m_attributeLocs;
	map<const char *, int> m_uniformLocs;
	bool m_verbose;
};

#endif
