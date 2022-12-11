#include "BVHNode.h"


template<class BoundingVolumeClass>
bool BVHNode<BoundingVolumeClass>::isLeaf() const
{
	return body != nullptr;
}

template<class BoundingVolumeClass>
bool BVHNode<BoundingVolumeClass>::overlaps(const BVHNode<BoundingVolumeClass>* other) const
{
	return volume->overlaps(other->volume);
}

template<class BoundingVolumeClass>
unsigned BVHNode<BoundingVolumeClass>::getPotentialContacts(PotentialContact* contacts, unsigned limit) const
{
	// Si c'est une feuille ou qu'on a dépassé la limite de contact => on n'ajoute pas de contacts
	if (isLeaf() || limit <= 0) {
		return 0;
	}
	// Sinon, on regarde les contacts potentiels du noeuf fils gauche avec le noeud fils droite 
	else {
		return children[0]->getPotentialContactsWith(children[1], contacts, limit);
	}
}

template<class BoundingVolumeClass>
unsigned BVHNode<BoundingVolumeClass>::getPotentialContactsWith(const BVHNode<BoundingVolumeClass>* other, PotentialContact* contacts, unsigned limit) const
{
	// S'il n'y a pas d'overlap ou si la limite de contact potentiels est atteinte => on n'ajoute pas de contact
	if (!overlaps(other) || limit <= 0) {
		return 0;
	}

	// Sinon s'il y a chevauchement et que les 2 noeuds sont des feuilles, alors on ajoute le contact
	else if (isLeaf() && other->isLeaf()) {
		contacts->body[0] = body;
		contacts->body[1] = other->body;
		return 1;
	}

	if (other->isLeaf() || (!isLeaf() && volume->getSize() >= other->volume->getSize())) {
		unsigned count = children[0]->getPotentialContactsWith(other, contacts, limit);

		if (limit > count) {
			return count + children[1]->getPotentialContactsWith(other, contacts + count, limit - count);
		}
		else {
			return count;
		}

	}

	else {
		unsigned count = getPotentialContactsWith(other->children[0], contacts, limit);

		if (limit > count) {
			return count + getPotentialContactsWith(other->children[1], contacts + count, limit - count);
		}
		else {
			return count;
		}

	}

	return 0;
}


template<class BoundingVolumeClass>
void BVHNode<BoundingVolumeClass>::insert(RigidBody* newBody, const BoundingVolumeClass& newVolume)
{
	// Si on est une feuille, on doit créer deux nouveau fils et placer le nouveau
	// volume dans l'un d'eux

	if (isLeaf()) {
		// Le 1er fils est une copie du corps actuel
		children[0] = new BVHNode<BoundingVolumeClass>(this, volume, body);

		children[1] = new BVHNode<BoundingVolumeClass>(this, newVolume, newBody);


		this->body = NULL;

		// Recalculer le bounding volume ? La fonction est pas décrite dans le livre
		// donc à voir ce que ça fait
	}

	else {
		// A voir 
	}

}

template<class BoundingVolumeClass>
BVHNode<BoundingVolumeClass>::~BVHNode()
{
}
