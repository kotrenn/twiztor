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

void Arc::normalize(float)
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
                     float circleRadius,
                     bool circlePlus,
                     bool circleInverted)
	:Arc(permutation, slotU, slotV),
	 m_circleRadius(circleRadius),
	 m_circlePlus(circlePlus),
	 m_circleInverted(circleInverted)
{
}

vec2f CircleArc::getPoint(float) const
{
	// TODO: CircleArc::getPoint(float)
	return m_slotV->getCenter();
}

void CircleArc::render() const
{
	GLGraphics *glGraphics = GLGraphics::getInstance();
	glGraphics->setColor(m_permutation->getColor());
	
	vec2f v0 = m_slotU->getCenter();
	vec2f v1 = m_slotV->getCenter();

	// Calculate the center of the circle
	float d = (v0 - v1).getNorm();
	float r2 = m_circleRadius * m_circleRadius;
	float disc = r2 - d * d / 4.0;
	float minDisc = 0.001;
	if (disc < minDisc) disc = minDisc;
	float h = sqrt(disc);
	vec2f midpoint = (v0 + v1) / 2.0;
	vec2f disp = (v1 - v0).getUnit();
	vec2f rot = vec2f(disp.getY(), -disp.getX());
	if (m_circlePlus) rot *= -1.0;
	vec2f circleCenter = midpoint + h * rot;

	// Set up interval of angles to iterate along
	vec2f deltaU = v0 - circleCenter;
	vec2f deltaV = v1 - circleCenter;

	float thetaU = atan2(deltaU[1], deltaU[0]);
	float thetaV = atan2(deltaV[1], deltaV[0]);

	unsigned int numIntervals = 25;
	if (sc_debugEnabled) numIntervals = 5;
	
	float dTheta = thetaV - thetaU;

	// Put dTheta into the interval [0, 2pi]
	while (dTheta < 0)             dTheta += 2.0 * 3.14159;
	while (dTheta > 2.0 * 3.14159) dTheta -= 2.0 * 3.14159;

	// Invert it?
	if (m_circleInverted)
	{
		float tmp = thetaU;
		thetaU = thetaV;
		thetaV = tmp;
		dTheta = 2.0 * 3.14159 - dTheta;
	}

	dTheta /= numIntervals;

	// Iterate!
	for (unsigned int i = 0; i < numIntervals; ++i)
	{
		float theta0 = thetaU + i * dTheta;
		float theta1 = thetaU + (i + 1) * dTheta;

		vec2f p0(cos(theta0), sin(theta0));
		vec2f p1(cos(theta1), sin(theta1));

		p0 = m_circleRadius * p0 + circleCenter;
		p1 = m_circleRadius * p1 + circleCenter;

		glGraphics->drawLine(p0, p1);

		if (sc_debugEnabled)
		{
			glGraphics->drawCircle(p0, 0.005, true);
			glGraphics->drawCircle(p1, 0.005, true);
		}
	}

	if (sc_debugEnabled)
	{
		glGraphics->setColor(1.0, 0.0, 1.0);
		glGraphics->drawCircle(midpoint, 0.005, true);

		glGraphics->setColor(0.0, 1.0, 0.0);
		glGraphics->drawCircle(circleCenter, 0.005, true);
	}
}

void CircleArc::normalize(float radius)
{
	m_circleRadius /= radius;
}
