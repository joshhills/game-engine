#pragma once

/**
 * Denote entities that have collision enabled.
 */
class Collider {
public:
	virtual void OnCollisionStart() = 0;
	virtual void OnCollisionEnd() = 0;
};