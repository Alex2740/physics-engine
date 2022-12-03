#include "CollisionData.h"

void CollisionData::AddContact(Contact contact)
{
	int positionContact = contactMax - contactsLeft;

	if (positionContact >= contactMax) return;

	contacts[positionContact] = contact;
	contactsLeft -= 1;
}
