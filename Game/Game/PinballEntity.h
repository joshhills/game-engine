#pragma once

#include <Common/Entity.h>
#include <Common/Movement.h>
#include <Common/Collider.h>
#include <Common/CameraTrackEvent.h>
#include <Physics/Physics.h>

class PinballEntity : public Entity, public Movement, public Collider {
public:
	PinballEntity(int spawnX = 0, int spawnY = 0);
	virtual ~PinballEntity();

	/**
	 * Make the camera focus on the pinball.
	 */
	void OnMove(EventManager * eventManager, float oldX, float oldY, float newX, float newY) override;

	/**
	 * Make noise.
	 */
	void OnCollisionStart() override;

	/**
	* Make noise.
	*/
	void OnCollisionEnd() override {};
};