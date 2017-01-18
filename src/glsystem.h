#ifndef __GL_SYSTEM_H_
#define __GL_SYSTEM_H_

#include "mat3f.h"

enum MatrixType
{
	MAT_PROJECTION,
	MAT_MODEL,
	MAT_VIEW,
	MAT_MODELVIEW
};

class GLSystem
{
public:
	GLSystem();
	
	void loadAllIdentities();
	void loadIdentity(MatrixType matrixType);
	
	void pushMatrix(MatrixType matrixType);
	void popMatrix(MatrixType matrixType);

	mat3f getMatrix(MatrixType matrixType);

	void translate2fv(MatrixType matrixType, const vec2f &vec);
private:
	map<MatrixType, vector<mat3f>> m_matrixStacks;

	void replaceMatrix(MatrixType matrixType, const mat3f &mat);
};

#endif
