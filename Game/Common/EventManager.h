#pragma once

#include <vector>
#include "Event.h"
#include <iostream>

using namespace std;

class EventManager {
public:
	EventManager();
	~EventManager();

	/**
	 * Return a reference to the current event queue.
	 * (ergo must stay in memory).
	 *
	 * @return	A vector of event pointers representing
	 *			all messages in the engine.
	 */
	vector<Event *> & GetEventQueue();

	/**
	 * Add an event to the event queue.
	 * 
	 * @param e	The event to be added.
	 */
	void addEvent(Event * e);

	/**
	 * Remove events that have been handled
	 * by all relevant subsystems.
	 */
	void removeFinishedEvents();

	/**
	 * Remove all events in the queue.
	 */
	void purgeEvents();
private:
	/* Queue of events for running application;
	 * they represent messages between subsystems.
	 */
	vector<Event *> queue;
};