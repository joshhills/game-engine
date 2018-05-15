#pragma once

#include <Common/Entity.h>
#include <Common/CompleteLevelEvent.h>
#include <Common/HoleEnterEvent.h>
#include <Common/PlaySoundEvent.h>
#include <Common/MoveEvent.h>
#include <Physics/Physics.h>

/**
* Wrapper class for tile entities.
*/
class TileEntity : public Entity, public Collider {
public:

	/**
	* Tile types and embedded orientation used for
	* serialisation in file operations.
	*/
	enum class TileType {
		NOTHING = 0,
		BLOCK = 1,
		WEDGE_BOTTOM_LEFT = 2,
		WEDGE_TOP_LEFT = 3,
		WEDGE_TOP_RIGHT = 4,
		WEDGE_BOTTOM_RIGHT = 5,
		FLIPPER_TOP = 6,
		FLIPPER_RIGHT = 7,
		FLIPPER_BOTTOM = 8,
		FLIPPER_LEFT = 9,
		FLIPPER_BOTTOM_LEFT = 10,
		FLIPPER_TOP_LEFT = 11,
		FLIPPER_TOP_RIGHT = 12,
		FLIPPER_BOTTOM_RIGHT = 13,
		BUMPER = 14,
		HOLE_ENTER = 15,
		HOLE_EXIT = 16,
		SPAWN = 17,
		FINISH = 18
	};

	/**
	* Constructor to create a tile entity.
	*
	* @param type			The type of the tile as embedded data.
	* @param gridPositionX	The position on the grid this entity should be positioned horizontally.
	* @param gridPositionX	The position on the grid this entity should be positioned vertically.
	*/
	TileEntity(EventManager * eventManager, TileType type, int gridPositionX, int gridPositionY)
		: Entity(eventManager),
		type(type),
		gridPositionX(gridPositionX * 2),
		gridPositionY(gridPositionY * 2)
	{};

	virtual ~TileEntity() {}

	TileType type;
	int gridPositionX;
	int gridPositionY;

	void OnCollisionStart(Entity * e)
	{
		switch (type)
		{
			case TileType::FINISH:
				eventManager->AddEvent(new CompleteLevelEvent());
				eventManager->AddEvent(new PlaySoundEvent("./Resources/Audio/complete-level.wav", true, 0, 0));
				break;
			case TileType::HOLE_ENTER:
				eventManager->AddEvent(new HoleEnterEvent());
				eventManager->AddEvent(new PlaySoundEvent("./Resources/Audio/collide-hole.wav", true, gameObject->x, gameObject->y));
				break;
			case TileType::FLIPPER_TOP:
				// If the other entity is in the correct place.
				if (e->GetPhysicsData()->GetBody()->GetPosition().y > physicsData->GetBody()->GetPosition().y)
				{
					MoveEvent::Direction d;
					d.x = 0;
					d.y = FLIPPER_SPEED;

					eventManager->AddEvent(
						(new MoveEvent(d))->AddEntity(e)
					);
					eventManager->AddEvent(new PlaySoundEvent("./Resources/Audio/collide-flipper.wav", true, gameObject->x, gameObject->y));
				}
				break;
			case TileType::FLIPPER_RIGHT:
				// If the other entity is in the correct place.
				if (e->GetPhysicsData()->GetBody()->GetPosition().x < physicsData->GetBody()->GetPosition().x)
				{
					MoveEvent::Direction d;
					d.x = -FLIPPER_SPEED;
					d.y = 0;

					eventManager->AddEvent(
						(new MoveEvent(d))->AddEntity(e)
					);
					eventManager->AddEvent(new PlaySoundEvent("./Resources/Audio/collide-flipper.wav", true, gameObject->x, gameObject->y));
				}
				break;
			case TileType::FLIPPER_BOTTOM:
				// If the other entity is in the correct place.
				if (e->GetPhysicsData()->GetBody()->GetPosition().y < physicsData->GetBody()->GetPosition().y)
				{
					MoveEvent::Direction d;
					d.x = 0;
					d.y = -FLIPPER_SPEED;

					eventManager->AddEvent(
						(new MoveEvent(d))->AddEntity(e)
					);
					eventManager->AddEvent(new PlaySoundEvent("./Resources/Audio/collide-flipper.wav", true, gameObject->x, gameObject->y));
				}
				break;
			case TileType::FLIPPER_LEFT:
				// If the other entity is in the correct place.
				if (e->GetPhysicsData()->GetBody()->GetPosition().x > physicsData->GetBody()->GetPosition().x)
				{
					MoveEvent::Direction d;
					d.x = FLIPPER_SPEED;
					d.y = 0;

					eventManager->AddEvent(
						(new MoveEvent(d))->AddEntity(e)
					);
					eventManager->AddEvent(new PlaySoundEvent("./Resources/Audio/collide-flipper.wav", true, gameObject->x, gameObject->y));
				}
				break;
			case TileType::FLIPPER_BOTTOM_LEFT:
				// If the other entity is in the correct place.
				if (e->GetPhysicsData()->GetBody()->GetPosition().x < physicsData->GetBody()->GetPosition().x
					|| e->GetPhysicsData()->GetBody()->GetPosition().y > physicsData->GetBody()->GetPosition().y)
				{
					MoveEvent::Direction d;
					d.x = -FLIPPER_SPEED;
					d.y = FLIPPER_SPEED;

					eventManager->AddEvent(
						(new MoveEvent(d))->AddEntity(e)
					);
					eventManager->AddEvent(new PlaySoundEvent("./Resources/Audio/collide-flipper.wav", true, gameObject->x, gameObject->y));
				}
				break;
			case TileType::FLIPPER_BOTTOM_RIGHT:
				// If the other entity is in the correct place.
				if (e->GetPhysicsData()->GetBody()->GetPosition().x > physicsData->GetBody()->GetPosition().x
					|| e->GetPhysicsData()->GetBody()->GetPosition().y > physicsData->GetBody()->GetPosition().y)
				{
					MoveEvent::Direction d;
					d.x = FLIPPER_SPEED;
					d.y = FLIPPER_SPEED;

					eventManager->AddEvent(
						(new MoveEvent(d))->AddEntity(e)
					);
					eventManager->AddEvent(new PlaySoundEvent("./Resources/Audio/collide-flipper.wav", true, gameObject->x, gameObject->y));
				}
				break;
			case TileType::FLIPPER_TOP_LEFT:
				// If the other entity is in the correct place.
				if (e->GetPhysicsData()->GetBody()->GetPosition().x < physicsData->GetBody()->GetPosition().x
					|| e->GetPhysicsData()->GetBody()->GetPosition().y < physicsData->GetBody()->GetPosition().y)
				{
					MoveEvent::Direction d;
					d.x = -FLIPPER_SPEED;
					d.y = -FLIPPER_SPEED;

					eventManager->AddEvent(
						(new MoveEvent(d))->AddEntity(e)
					);
					eventManager->AddEvent(new PlaySoundEvent("./Resources/Audio/collide-flipper.wav", true, gameObject->x, gameObject->y));
				}
				break;
			case TileType::FLIPPER_TOP_RIGHT:
				// If the other entity is in the correct place.
				if (e->GetPhysicsData()->GetBody()->GetPosition().x > physicsData->GetBody()->GetPosition().x
					|| e->GetPhysicsData()->GetBody()->GetPosition().y < physicsData->GetBody()->GetPosition().y)
				{
					MoveEvent::Direction d;
					d.x = FLIPPER_SPEED;
					d.y = -FLIPPER_SPEED;

					eventManager->AddEvent(
						(new MoveEvent(d))->AddEntity(e)
					);
					eventManager->AddEvent(new PlaySoundEvent("./Resources/Audio/collide-flipper.wav", true, gameObject->x, gameObject->y));
				}
				break;
			case TileType::BUMPER:
				// Get the normalised direction between the two entities.
				b2Vec2 direction = (e->GetPhysicsData()->GetBody()->GetPosition() - physicsData->GetBody()->GetPosition());
				direction.Normalize();
				direction *= BUMPER_SPEED;

				MoveEvent::Direction d;
				d.x = direction.x;
				d.y = direction.y;
				eventManager->AddEvent(
					(new MoveEvent(d))->AddEntity(e)
				);
				eventManager->AddEvent(new PlaySoundEvent("./Resources/Audio/collide-bumper.wav", true, gameObject->x, gameObject->y));
				break;
		}
	}

	void OnCollisionEnd(Entity * e)
	{}

private:
	const int FLIPPER_SPEED = 30000;
	const int BUMPER_SPEED = 30000;
};