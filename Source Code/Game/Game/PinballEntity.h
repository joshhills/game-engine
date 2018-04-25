#pragma once

#include <Common/Entity.h>
#include <Common/Movement.h>
#include <Common/Collider.h>
#include <Common/CameraTrackEvent.h>
#include <Physics/Physics.h>

#include <Common/PlaySoundEvent.h>

class PinballEntity : public Entity, public Movement, public Collider {
public:
	PinballEntity(EventManager * eventManager, int spawnX = 0, int spawnY = 0);
	virtual ~PinballEntity();

	/**
	 * Make the camera focus on the pinball.
	 */
	void OnMove(EventManager * eventManager, float oldX, float oldY, float newX, float newY) override;

	void OnCollisionStart();

	void OnCollisionEnd() {}
};