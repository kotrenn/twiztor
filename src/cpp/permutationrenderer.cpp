#include "permutationrenderer.h"

#include "glgraphics.h"

PermutationRenderer::PermutationRenderer()
{
}

void PermutationRenderer::render(const Permutation &permutation,
                                 const vector<Slot *> &slotList,
                                 const vector<Arc *> &arcList) const
{
	Color permColor = permutation.getColor();
	const vector<unsigned int> &mapping = permutation.getMapping();

	GLGraphics *glGraphics = GLGraphics::getInstance();
	glGraphics->setColor(permColor);

	/*
	for (unsigned int i = 0; i < mapping.size(); ++i)
	{
		Slot *curSlot = slotList[i];
		Slot *nextSlot = slotList[mapping[i]];

		vec2f v0 = curSlot->getCenter();
		vec2f v1 = nextSlot->getCenter();

		float scale = 0.02;
		scale = 0.0;
		int index = permutation.getIndex();
		v0 += vec2f(index * scale);
		v1 += vec2f(index * scale);

		glGraphics->setColor(permColor);
		glGraphics->drawLine(v0, v1);

	}
	*/
	
	for (unsigned int i = 0; i < arcList.size(); ++i)
	{
		Arc *arc = arcList[i];
		if (arc == NULL) continue;
		arc->render();
	}

}
