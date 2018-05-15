#pragma once

class Entity;

/**
 * Denote entities that have collision enabled.
 */
class Collider {
public:
	virtual void OnCollisionStart(Entity * e) = 0;
	virtual void OnCollisionEnd(Entity * e) = 0;
};