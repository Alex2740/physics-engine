#include "BVHNode.h"

bool BVHNode::isLeaf() const
{
	return body != nullptr;
}
