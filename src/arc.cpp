#include "arc.h"

#include "glgraphics.h"

Arc::Arc(Permutation *permutation, Slot *slotU, Slot *slotV)
	:m_permutation(permutation),
	 m_slotU(slotU),
	 m_slotV(slotV),
	 m_startTime(SDL_GetTicks())
{
}

void Arc::computeParameters()
{
}

void Arc::adjustCenter(const vec2f &)
{
}

void Arc::normalize(float)
{
}

void Arc::render() const
{
	GLGraphics *glGraphics = GLGraphics::getInstance();
	glGraphics->setColor(m_permutation->getColor());
	
	Uint32 curTime = SDL_GetTicks();
	float duration = (float)(curTime - m_startTime) / sc_animDuration;
	float t0 = duration - static_cast<int>(duration);

	unsigned int numDots = 3;
	for (unsigned int i = 0; i < numDots; ++i)
	{
		float t = t0 + static_cast<float>(i) / numDots;
		if (t > 1.0) t -= 1.0;
		vec2f p = getPoint(t);
		glGraphics->drawCircle(p, 0.01, true);
	}
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
	Arc::render();
	
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
	 m_circleInverted(circleInverted),
	 m_circleCenter(0.0, 0.0),
	 m_thetaU(0.0),
	 m_thetaV(0.0),
	 m_dTheta(0.0)
{
	computeParameters();
}

void CircleArc::computeParameters()
{
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
	m_circleCenter = midpoint + h * rot;

	// Set up interval of angles to iterate along
	vec2f deltaU = v0 - m_circleCenter;
	vec2f deltaV = v1 - m_circleCenter;

    m_thetaU = atan2(deltaU[1], deltaU[0]);
	m_thetaV = atan2(deltaV[1], deltaV[0]);

	m_dTheta = m_thetaV - m_thetaU;

	// Put dTheta into the interval [0, 2pi]
	while (m_dTheta < 0)             m_dTheta += 2.0 * 3.14159;
	while (m_dTheta > 2.0 * 3.14159) m_dTheta -= 2.0 * 3.14159;

	// Invert it?
	if (m_circleInverted)
	{
		float tmp = m_thetaU;
		m_thetaU = m_thetaV;
		m_thetaV = tmp;
		m_dTheta = 2.0 * 3.14159 - m_dTheta;
	}
}

vec2f CircleArc::getPoint(float t) const
{
	//float theta = m_thetaU + t * m_dTheta;
	float theta = m_thetaU + t * m_dTheta;

	vec2f p(cos(theta), sin(theta));
	p = m_circleRadius * p + m_circleCenter;

	return p;
}

void CircleArc::render() const
{
	Arc::render();
	
	GLGraphics *glGraphics = GLGraphics::getInstance();
	glGraphics->setColor(m_permutation->getColor());

	unsigned int numIntervals = 20;
	if (sc_debugEnabled) numIntervals = 5;
	float dt = 1.0 / numIntervals;
	for (unsigned int i = 0; i < numIntervals; ++i)
	{
		float t0 = i * dt;
		float t1 = (i + 1) * dt;

		vec2f p0 = getPoint(t0);
		vec2f p1 = getPoint(t1);

		glGraphics->drawLine(p0, p1);

		if (sc_debugEnabled)
		{
			glGraphics->setColor(t0, 0.0, 1.0 - t0);
			glGraphics->drawCircle(p0, 0.03, true);
			glGraphics->setColor(m_permutation->getColor());
		}
	}

	if (sc_debugEnabled)
	{
		glGraphics->setColor(0.0, 1.0, 0.0);
		glGraphics->drawCircle(m_circleCenter, 0.03, true);
	}
}

void CircleArc::normalize(float radius)
{
	m_circleRadius /= radius;
}
