#pragma once

/**
 * Add modularity to requirements of subsystem by
 * separating lifecycle procedures to separate 
 * interface.
 */
class SubsystemLifecycle {
public:
	virtual void StartUp() = 0;
	virtual void ShutDown() = 0;
};