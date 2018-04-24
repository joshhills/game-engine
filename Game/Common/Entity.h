#pragma once

#include "GameObject.h"
#include <Graphics\GraphicsData.h>
#include <Physics\PhysicsData.h>
#include <Audio\AudioData.h>

class Entity {
public:
	Entity();
	virtual ~Entity();

	GameObject * GetGameObject();
	GraphicsData * GetGraphicsData();
	PhysicsData * GetPhysicsData();
	AudioData * GetAudioData();
protected:
	GameObject * gameObject;
	GraphicsData * graphicsData;
	PhysicsData * physicsData;
	AudioData * audioData;
};