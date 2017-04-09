#ifndef __PERMUTATION_FACTORY_H_
#define __PERMUTATION_FACTORY_H_

#include "permutation.h"
#include "permutationrenderer.h"

class Permutation;
class PermutationRenderer;

class PermutationFactory
{
public:
	PermutationFactory();
	~PermutationFactory();

	Permutation *makePermutation(unsigned int n,
	                             const Color &color,
	                             int index,
	                             const vector<vector<unsigned int>> &cycles);
private:
	PermutationRenderer *m_permutationRenderer;
};

#endif
