#pragma once

#include "BoundingSphere.h"
#include "Rigidbody.h"
#include "PotentialContact.h"

// Arbre binaire pour contenir la hiérarchie des volumes englobants

class BVHNode {	

	// Arbre binaire => 2 nodes filles
	BVHNode* children[2];

	// Volume englobant tous les fils
	BoundingSphere volume;

	
	// Contient un rigidbody s'il s'agit d'une feuille de l'arbre
	RigidBody* body;

	BVHNode* parent;

public :

	BVHNode(BVHNode* parent, const BoundingSphere& newVolume, RigidBody* body);

	// Détermine si le noeud est un feuille ou non
	bool isLeaf() const;

	bool overlaps(const BVHNode* other)const;

	unsigned getPotentialContacts(PotentialContact* contacts, unsigned limit) const;

	unsigned getPotentialContactsWith(const BVHNode *other,PotentialContact* contacts, unsigned limit) const;

	void recalculateBoundingVolume();

	void insert(RigidBody* body, const BoundingSphere& volume);

	// Affiche récursivement le BVH
	void print(int space);

	BVHNode* getLeftChildren();
	BVHNode* getRightChildren();

	~BVHNode();
};