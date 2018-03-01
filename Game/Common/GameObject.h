#pragma once

/**
 * The purpose of this class is to decouple
 * an entity from an individual subsystem's
 * data. In this way, subsystems are not
 * inter-dependent.
 */
struct GameObject {
	// Declare generic, abstracted fields.
	// TODO: Make this a vector? But then, don't want dependencies...
	float x;
	float y;
	float rotation;
};