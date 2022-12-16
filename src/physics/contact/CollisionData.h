#pragma once

#include "physics/contact/Contact.h"

#include <vector>

class CollisionData
{
private:
	// Array contenant tous les contacts
	std::vector<Contact> contactList;

public:
	void AddContact(Contact contact);
	std::vector<Contact> getContactList();
};