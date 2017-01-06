#include "glsystem.h"

GLSystem::GLSystem()
	:m_matrixStacks()
{
	loadAllIdentities();
}

void GLSystem::loadAllIdentities()
{
	loadIdentity(MAT_PROJECTION);
	loadIdentity(MAT_MODEL);
	loadIdentity(MAT_VIEW);
}

void GLSystem::loadIdentity(MatrixType matrixType)
{
	if (m_matrixStacks.find(matrixType) == m_matrixStacks.end())
		m_matrixStacks[matrixType] = list<mat3f>();

	list<mat3f> &matrixStack = m_matrixStacks[matrixType];
	matrixStack.clear();
	matrixStack.push_back(mat3f::identity3f());
}

void GLSystem::translate2fv(const vec2f &)
{
}

void GLSystem::pushMatrix(MatrixType matrixType)
{
	mat3f newMatrix = mat3f(m_matrixStacks[matrixType].back());
	m_matrixStacks[matrixType].push_back(newMatrix);
}

void GLSystem::popMatrix(MatrixType matrixType)
{
	m_matrixStacks[matrixType].pop_back();
}
