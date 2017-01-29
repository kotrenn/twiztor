#ifndef __ARC_H_
#define __ARC_H_

#include "permutation.h"
#include "slot.h"

class Permutation;

class Arc
{
public:
	Arc(Permutation *permutation, Slot *slotU, Slot *slotV);

	virtual void computeParameters();
	virtual vec2f getPoint(float t) const = 0;
	virtual void render() const;

	virtual void adjustCenter(const vec2f &newCenter);
	virtual void normalize(float radius);
protected:
	static const Uint32 sc_animDuration = 12000;
	Permutation *m_permutation;
	Slot *m_slotU;
	Slot *m_slotV;
	Uint32 m_startTime;
};

class LineArc : public Arc
{
public:
	LineArc(Permutation *permutation, Slot *slotU, Slot *slotV);

	vec2f getPoint(float t) const;
	virtual void render() const;
};

class CircleArc : public Arc
{
public:
	CircleArc(Permutation *permutation, Slot *slotU, Slot *slotV,
	          float circleRadius,
	          bool circlePlus, bool circleInverted);

	void computeParameters();
	vec2f getPoint(float t) const;
	virtual void render() const;

	void normalize(float radius);
private:
	static const bool sc_debugEnabled = false;

	// Input parameters
	float m_circleRadius;
	bool m_circlePlus;
	bool m_circleInverted;

	// Calculated parameters
	vec2f m_circleCenter;
	float m_thetaU;
	float m_thetaV;
	float m_dTheta;

};

#endif
