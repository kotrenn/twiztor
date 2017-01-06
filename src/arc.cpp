#include "arc.h"

#include "glgraphics.h"

Arc::Arc(Permutation *permutation, Slot *slotU, Slot *slotV)
	:m_permutation(permutation),
	 m_slotU(slotU),
	 m_slotV(slotV)
{
}

void Arc::adjustCenter(const vec2f &)
{
}



LineArc::LineArc(Permutation *permutation, Slot *slotU, Slot *slotV)
	:Arc(permutation, slotU, slotV)
{
}

vec2f LineArc::getPoint(float t) const
{
	return (1 - t) * m_slotU->getCenter() + t * m_slotV->getCenter();
}

void LineArc::render() const
{
	GLGraphics *glGraphics = GLGraphics::getInstance();
	glGraphics->setColor(m_permutation->getColor());

	vec2f v0 = m_slotU->getCenter();
	vec2f v1 = m_slotV->getCenter();

	glGraphics->drawLine(v0, v1);
}



CircleArc::CircleArc(Permutation *permutation,
                     Slot *slotU,
                     Slot *slotV,
                     const vec2f &circleCenter)
	:Arc(permutation, slotU, slotV),
	 m_circleCenter(circleCenter)
{
}

vec2f CircleArc::getPoint(float) const
{
	return m_slotV->getCenter();
}

void CircleArc::render() const
{
	// TODO: PuzzleReader: Change circleCenter to radius and compute the circle through two points
	GLGraphics *glGraphics = GLGraphics::getInstance();
	glGraphics->setColor(m_permutation->getColor());
	
	vec2f v0 = m_slotU->getCenter();
	vec2f v1 = m_slotV->getCenter();

	vec2f deltaU = v0 - m_circleCenter;
	vec2f deltaV = v1 - m_circleCenter;

	float radius = deltaU.getNorm();

	float thetaU = atan2(deltaU[1], deltaU[0]);
	float thetaV = atan2(deltaV[1], deltaV[0]);

	unsigned int numIntervals = 5;
	float dTheta = (thetaV - thetaU) / numIntervals;

	for (unsigned int i = 0; i < numIntervals; ++i)
	{
		float theta0 = thetaU + i * dTheta;
		float theta1 = thetaU + (i + 1) * dTheta;

		vec2f p0(cos(theta0), sin(theta0));
		vec2f p1(cos(theta1), sin(theta1));

		p0 = radius * p0 + m_circleCenter;
		p1 = radius * p1 + m_circleCenter;

		glGraphics->drawLine(p0, p1);

		glGraphics->drawCircle(p0, 0.005);
		glGraphics->drawCircle(p1, 0.005);
	}

	glGraphics->setColor(0.0, 1.0, 0.0);
	glGraphics->drawCircle(m_circleCenter, 0.005);
}

void CircleArc::adjustCenter(const vec2f &newCenter)
{
	m_circleCenter -= newCenter;
}
