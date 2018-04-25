#pragma once

#include <Box2D/Box2D.h>
#include <Common/Entity.h>
#include <Common/Collider.h>

class ContactListener : public b2ContactListener
{
	virtual void BeginContact(b2Contact * contact)
	{
		// Only entities are passed as userdata.
		Entity * bodyUserDataA = (Entity *)contact->GetFixtureA()->GetBody()->GetUserData();
		Entity * bodyUserDataB = (Entity *)contact->GetFixtureB()->GetBody()->GetUserData();

		if (bodyUserDataA)
		{
			Collider * c = dynamic_cast<Collider *>(bodyUserDataA);
			if (c != nullptr)
			{
				c->OnCollisionStart();
			}
		}

		if (bodyUserDataB)
		{
			Collider * c = dynamic_cast<Collider *>(bodyUserDataB);
			if (c != nullptr)
			{
				c->OnCollisionStart();
			}
		}
	}

	virtual void EndContact(b2Contact * contact)
	{
		// Only entities are passed as userdata.
		Entity * bodyUserDataA = (Entity *)contact->GetFixtureA()->GetBody()->GetUserData();
		Entity * bodyUserDataB = (Entity *)contact->GetFixtureB()->GetBody()->GetUserData();

		if (bodyUserDataA)
		{
			Collider * c = dynamic_cast<Collider *>(bodyUserDataA);
			if (c != nullptr)
			{
				c->OnCollisionEnd();
			}
		}

		if (bodyUserDataB)
		{
			Collider * c = dynamic_cast<Collider *>(bodyUserDataB);
			if (c != nullptr)
			{
				c->OnCollisionEnd();
			}
		}
	}
};