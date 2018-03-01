#pragma once

#include "Event.h"
#include "EventManager.h"
#include "LoggerInstance.h"

class Subsystem {
public:
	Subsystem(string id, Event::Subsystem eventType, EventManager * eventManager);
	virtual ~Subsystem();

	virtual void Update() = 0;
	
	/**
	 * Delegate event handling based
	 * on the engine's event queue.
	 */
	virtual void HandleEvents() {
		logger.Info("Handling events.");

		// Search event queue for messages that pertain to this sub-system.
		for (Event * e : eventManager->GetEventQueue(eventType))
		{
			HandleEvent(e);
		}
	};

	// TODO: Partly implement.
	virtual void HandleEvent(Event * event) = 0;

	// TODO: Do startup / shutdown
protected:
	// Engine utility.
	string id;
	LoggerInstance logger;
	Event::Subsystem eventType;

	// Engine state.
	EventManager * eventManager;
};