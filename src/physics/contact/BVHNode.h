#include "BoundingSphere.h"
#include "Rigidbody.h"
#include "PotentialContact.h"

// Arbre binaire pour contenir la hiérarchie des volumes englobants
template<class BoundingVolumeClass> 
class BVHNode {	

	// Arbre binaire => 2 nodes filles
	BVHNode* children[2];

	// Volume englobant tous les fils
	BoundingVolumeClass volume;

	
	// Contient un rigidbody s'il s'agit d'une feuille de l'arbre
	RigidBody* body;

	BVHNode* parent;

	BVHNode(BVHNode* node, BoundingVolumeClass& newVolume, RigidBody* body);

	// Détermine si le noeud est un feuille ou non
	bool isLeaf() const;

	bool overlaps(const BVHNode<BoundingVolumeClass>* other)const;

	unsigned getPotentialContacts(PotentialContact* contacts, unsigned limit) const;

	unsigned getPotentialContactsWith(const BVHNode<BoundingVolumeClass> *other,PotentialContact* contacts, unsigned limit) const;

	void insert(RigidBody* body, const BoundingVolumeClass& volume);

	~BVHNode();
};