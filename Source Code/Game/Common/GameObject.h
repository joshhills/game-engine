#pragma once

/**
 * The purpose of this class is to decouple
 * an entity from an individual subsystem's
 * data. In this way, subsystems are not
 * inter-dependent.
 */
struct GameObject {
	// Declare generic, abstracted fields.
	float x;
	float y;
	float rotation;
};