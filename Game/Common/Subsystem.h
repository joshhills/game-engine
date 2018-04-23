#pragma once

#include <map>
#include <functional>
#include <time.h>
#include <stdio.h>

#include "Event.h"
#include "EventManager.h"
#include "LoggerInstance.h"

class Subsystem {
public:
	Subsystem(string id, Event::Subsystem subSystemType, EventManager * eventManager);
	virtual ~Subsystem();

	virtual void Update()
	{
		logger.Info("Updating subsystem.");

		HandleEvents();
	}
	
	/**
	 * Delegate event handling based
	 * on the engine's event queue.
	 */
	virtual void HandleEvents() {
		logger.Info("Handling events.");

		// Search event queue for messages that pertain to this sub-system.
		for (Event * e : eventManager->GetEventQueue(subSystemType))
		{
			HandleEvent(e);
		}
	};

	virtual void HandleEvent(Event * e) {
		logger.Debug("Handling event.");

		if (eventMap.count(e->type) > 0)
		{
			eventMap[e->type](e);
		}
		else
		{
			logger.Warn("Skipping handling of unmapped event of type " + to_string(e->type));
		}
		
		// Inform the manager that we are finished with the event.
		eventManager->MarkAsHandled(e, subSystemType);
	};

	// TODO: Do startup / shutdown
protected:
	// Engine utility.
	string id;
	LoggerInstance logger;
	Event::Subsystem subSystemType; 

	// Engine state.
	EventManager * eventManager;

	// Map event codes to functions.
	map<Event::EventType, std::function<void(Event * e)>> eventMap;
};