#include "BVHNode.h"


BVHNode::BVHNode(BVHNode* parent, const BoundingSphere& newVolume, RigidBody* body)
{
	this->parent = parent;
	volume = newVolume;
	this->body = body;
	children[0] = nullptr;
	children[1] = nullptr;
}

BVHNode::BVHNode(BVHNode* parent, Primitive* objet) {
	this->parent = parent;
	volume = BoundingSphere(objet);
	this->body = objet->body;
	children[0] = nullptr;
	children[1] = nullptr;
}


bool BVHNode::isLeaf() const
{
	return body != nullptr;
}


bool BVHNode::overlaps(const BVHNode* other) const
{
	return volume.overlaps(other->volume);
}


int BVHNode::getPotentialContacts(PotentialContact** contacts, int limit) const
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

int BVHNode::getPotentialContactsWith(const BVHNode* other, PotentialContact** contacts, int limit) const
{
	// S'il n'y a pas d'overlap ou si la limite de contact potentiels est atteinte => on n'ajoute pas de contact
	if (!overlaps(other) || limit <= 0) {
		return 0;
	}

	// Sinon s'il y a chevauchement et que les 2 noeuds sont des feuilles, alors on ajoute le contact
	else if (isLeaf() && other->isLeaf()) {
		contacts[0] = static_cast<PotentialContact*>(calloc(1, sizeof(PotentialContact)));
		contacts[0]->bodies[0] = body;
		contacts[0]->bodies[1] = other->body;
		return 1;
	}

	// TODO: i am sure that this can be bad in some cases, to be checked later (Wenhao)
	if (other->isLeaf() || (!isLeaf() && volume.getSize() >= other->volume.getSize())) {
		int count = children[0]->getPotentialContactsWith(other, contacts, limit);

		if (limit > count) {
			return count + children[1]->getPotentialContactsWith(other, contacts + count, limit - count);
		}
		else {
			return count;
		}

	}

	else {
		int count = getPotentialContactsWith(other->children[0], contacts, limit);

		if (limit > count) {
			return count + getPotentialContactsWith(other->children[1], contacts + count, limit - count);
		}
		else {
			return count;
		}
	}

	return 0;
}

void BVHNode::recalculateBoundingVolume()
{
	// Pas sûr de l'implémentation, à corriger dans le futur selon les tests
	// 
	// On calcule le nouveau Bounding volume qui englobe les deux nodes filles

	if (children[0] && !children[1]) {
		volume = children[0]->volume;
	}
	else if (!children[0] && children[1]) {
		volume = children[1]->volume;
	}
	else {
		volume = BoundingSphere(children[0]->volume, children[1]->volume);
	}
}


void BVHNode::insert(RigidBody* newBody, const BoundingSphere& newVolume)
{
	// Si on est une feuille, on doit créer deux nouveau fils et placer le nouveau
	// volume dans l'un d'eux

	if (isLeaf()) {
		

		// Le 1er fils est une copie du corps actuel
		children[0] = new BVHNode(this, volume, body);

		children[1] = new BVHNode(this, newVolume, newBody);

	
		this->body = nullptr;

		recalculateBoundingVolume();



	}

	// Si c'est une node, on ajoute le nouveau corps avec le fils 
	// dont le volume englobant serait le plus petit
	else {

		if (children[0]->volume.getGrowth(newVolume) < children[1]->volume.getGrowth(newVolume)) {
			children[0]->insert(newBody, newVolume);
		}
		else {
			children[1]->insert(newBody, newVolume);
		}
	}

}

BVHNode::~BVHNode()
{
	// Suppression d'une node

	// Si la node possède un parent


	if (parent) {

		BVHNode* sibling;
		if (parent->children[0] == this) {
			sibling = parent->children[1];
		}
		else {
			sibling = parent->children[0];
		}

		// On copie les données de la node soeur dans le parent
		parent->volume = sibling->volume;
		parent->body = sibling->body;
		parent->children[0] = sibling->children[0];
		parent->children[1] = sibling->children[1];

		// On supprime la node soeur;
		sibling->parent = nullptr;
		sibling->body = nullptr;
		sibling->children[0] = nullptr;
		sibling->children[1] = nullptr;
	
		delete sibling;

		

		// On recalcule le bounding volume du parent
		// Je ne comprends pas pq étant donné que le volume englobant du parent reprend celui de la node soeur donc je le commente pour l'instant
		//parent->recalculateBoundingVolume();
	}

	// On supprime simplement les enfants

		if (children[0]) {
			children[0]->parent = NULL;
			delete children[0];
		}
		if (children[1]) {

			children[1]->parent = NULL;
			delete children[1];
		}

}

void BVHNode::print(int space) {

	space += 10;

	if (isLeaf()) {
		for (int i = 10; i < space; i++)
			std::cout << " ";
		std::cout << body->getId() << "\n";
		return;
	}

	else {
		children[1]->print(space);
		for (int i = 10; i < space; i++)
			std::cout << " ";
		std::cout << "N" << "\n";

		children[0]->print(space);
	}

}

BVHNode* BVHNode::getLeftChildren() { return children[0];}
BVHNode* BVHNode::getRightChildren() { return children[1];}

void freePotentialContactList(PotentialContact** list) {
	if (list == nullptr) return;
	for (int i = 0; list[i] != nullptr; i++) {
		free(list[i]);
	}
	free(list);
}