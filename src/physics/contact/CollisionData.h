#include "Contact.h"

class CollisionData
{
	// Array contenant tous les contacts
	Contact* contacts;

	int contactMax;

public:
	// Nombre de contacts disponible dans l'array
	int contactsLeft;

	void AddContact(Contact contact);
};