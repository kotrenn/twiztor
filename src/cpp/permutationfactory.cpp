#include "permutationfactory.h"

PermutationFactory::PermutationFactory()
	:m_permutationRenderer(new PermutationRenderer())
{
}

PermutationFactory::~PermutationFactory()
{
	delete m_permutationRenderer;
}

Permutation *PermutationFactory::makePermutation(unsigned int n,
                                                 const Color &color,
                                                 int index,
                                                 const vector<vector<unsigned int>> &cycles)
{
	Permutation *permutation = new Permutation(m_permutationRenderer, n, color, index);
	permutation->setCycles(cycles);
	return permutation;
}
