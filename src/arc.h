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
	CircleArc(Permutation *permutation, Slot *slotU, Slot *slotV, const vec2f &circleCenter);

	vec2f getPoint(float t) const;
	void render() const;

	void adjustCenter(const vec2f &newCenter);
private:
	vec2f m_circleCenter;
};

#endif
