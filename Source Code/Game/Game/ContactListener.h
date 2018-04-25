#pragma once

#include <Box2D/Box2D.h>

#include <Common/Collider.h>

class ContactListener : public b2ContactListener
{
	virtual void BeginContact(b2Contact * contact)
	{
		void * bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
		if (bodyUserData)
		{
			Collider * c = static_cast<Collider *>(bodyUserData);
			if (c != nullptr)
			{
				c->OnCollisionStart();
			}
		}

		void * bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
		if (bodyUserData)
		{
			Collider * c = static_cast<Collider *>(bodyUserData);
			if (c != nullptr)
			{
				c->OnCollisionStart();
			}
		}
	}

	virtual void EndContact(b2Contact * contact)
	{
		void * bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
		if (bodyUserData)
		{
			Collider * c = static_cast<Collider *>(bodyUserData);
			if (c != nullptr)
			{
				c->OnCollisionEnd();
			}
		}

		void * bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
		if (bodyUserData)
		{
			Collider * c = static_cast<Collider *>(bodyUserData);
			if (c != nullptr)
			{
				c->OnCollisionEnd();
			}
		}
	}
};