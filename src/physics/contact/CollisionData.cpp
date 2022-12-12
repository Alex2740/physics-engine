#include "CollisionData.h"

void CollisionData::AddContact(Contact contact)
{
	this->contactList.push_back(contact);
}

std::vector<Contact> CollisionData::getContactList() {
	return this->contactList;
}
