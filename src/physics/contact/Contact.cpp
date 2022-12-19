#include "Contact.h"

Contact Contact::ContactNull()
{
	Contact c = Contact();
	c.type = ContactType::ContactNull;

	return c;
}

bool Contact::operator==(const Contact& other) const
{
	return (type == other.type)
		&& (body[0] == other.body[0])
		&& (body[1] == other.body[1])
		&& (contactPoint == other.contactPoint)
		&& (contactNormal == other.contactNormal)
		&& (penetration == other.penetration)
		&& (restitution && other.restitution)
		&& (friction && other.friction);
}

bool Contact::operator!=(const Contact& other) const
{
	return !(*this == other);
}
