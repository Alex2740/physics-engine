#include "BoundingSphere.h"
#include "Rigidbody.h"

// Arbre binaire pour contenir la hiérarchie des volumes englobants
template<class BoudingVolumeClass> class BVHNode {

	// Arbre binaire => 2 nodes filles
	BVHNode* children[2]

	// Volume englobant tous les fils
	BoudingVolumeClass volume;

	
	// Contient un rigidbody s'il s'agit d'une feuille de l'arbre
	RigidBody* body;

	// Détermine si le noeud est un feuille ou non
	bool isLeaf() const;


};