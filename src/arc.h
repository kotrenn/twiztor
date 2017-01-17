#ifndef __ARC_H_
#define __ARC_H_

#include "permutation.h"
#include "slot.h"

class Permutation;

class Arc
{
public:
	Arc(Permutation *permutation, Slot *slotU, Slot *slotV);

	virtual vec2f getPoint(float t) const = 0;
	virtual void render() const = 0;

	virtual void adjustCenter(const vec2f &newCenter);
	virtual void normalize(float radius);
protected:
	Permutation *m_permutation;
	Slot *m_slotU;
	Slot *m_slotV;
};

class LineArc : public Arc
{
public:
	LineArc(Permutation *permutation, Slot *slotU, Slot *slotV);

	vec2f getPoint(float t) const;
	void render() const;
};

class CircleArc : public Arc
{
public:
	CircleArc(Permutation *permutation, Slot *slotU, Slot *slotV,
	          float circleRadius,
	          bool circlePlus, bool circleInverted);

	vec2f getPoint(float t) const;
	void render() const;

	void normalize(float radius);
private:
	static const bool sc_debugEnabled = false;
	
	float m_circleRadius;
	bool m_circlePlus;
	bool m_circleInverted;
};

#endif
