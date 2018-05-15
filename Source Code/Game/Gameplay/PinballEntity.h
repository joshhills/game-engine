#pragma once

#include <Common/Entity.h>
#include <Common/Movement.h>
#include <Common/Collider.h>
#include <Common/CameraTrackEvent.h>
#include <Physics/Physics.h>

#include <Common/PlaySoundEvent.h>

class PinballEntity : public Entity, public Movement, public Collider {
public:
	PinballEntity(EventManager * eventManager);
	virtual ~PinballEntity();

	/**
	* Make the camera focus on the pinball.
	*/
	void OnMove(EventManager * eventManager, float oldX, float oldY, float newX, float newY) override;

	void OnCollisionStart(Entity * e);

	void OnCollisionEnd(Entity * e);

	void UpdateShaderBasedOnBumpAbility(bool canBump);
private:
	Shader * bumpShader;
	Shader * noBumpShader;

	const float COLLISION_SOUND_THRESHOLD = 300;
	float lastFinishedColliding = 0;
};