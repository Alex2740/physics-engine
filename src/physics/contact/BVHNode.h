#pragma once

#include <vector>
#include "BoundingSphere.h"
#include "PotentialContact.h"
//#include "physics/contact/primitive/Primitive.h"
#include "physics/Rigidbody.h"

// Arbre binaire pour contenir la hiï¿½rarchie des volumes englobants

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
	//BVHNode(BVHNode* parent, Primitive* objet);

	// Détermine si le noeud est un feuille ou non
	bool isLeaf() const;

	bool overlaps(const BVHNode* other)const;

	std::vector<PotentialContact> getPotentialContacts();

	std::vector<PotentialContact> getPotentialContactsWith(const BVHNode *other);

	void recalculateBoundingVolume();

	void insert(RigidBody* body, const BoundingSphere& volume);
	//void insert(Primitive* primitive);

	// Affiche récursivement le BVH
	void print();

	BVHNode* getLeftChildren();
	BVHNode* getRightChildren();

	~BVHNode();
};

void freePotentialContactList(std::vector<PotentialContact> list);