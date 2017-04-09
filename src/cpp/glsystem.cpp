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
		m_matrixStacks[matrixType] = vector<mat3f>();

	vector<mat3f> &matrixStack = m_matrixStacks[matrixType];
	matrixStack.clear();
	matrixStack.push_back(mat3f::identity3f());
}

void GLSystem::translate2fv(MatrixType matrixType, const vec2f &vec)
{
	mat3f matrix(1.0, 0.0, vec.getX(),
	             0.0, 1.0, vec.getY(),
	             0.0, 0.0, 1.0);
	mat3f prevMatrix = getMatrix(matrixType);
	mat3f newMatrix = prevMatrix * matrix;
	replaceMatrix(matrixType, newMatrix);
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

mat3f GLSystem::getMatrix(MatrixType matrixType)
{
	return m_matrixStacks[matrixType].back();
}

void GLSystem::replaceMatrix(MatrixType matrixType, const mat3f &mat)
{
	unsigned int stackSize = m_matrixStacks[matrixType].size();
	if (stackSize == 0) return;
	m_matrixStacks[matrixType][stackSize - 1] = mat;
}
