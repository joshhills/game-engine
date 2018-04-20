#pragma once

#include <vector>
#include <iostream>

#include "Event.h"
#include "LoggerInstance.h"

using namespace std;

/* Not static as we may want multiple event streams.
 */
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
	* Return a reference to all events in the queue
	* that pertain to a specific subsystem.
	*
	* @param	A subsystem to filter events on.
	* @return	A vector of event pointers representing
	*			all messages in the engine.
	*/
	vector<Event *> GetEventQueue(Event::Subsystem subsystem);

	/**
	 * Add an event to the event queue.
	 * 
	 * @param e	The event to be added.
	 */
	void AddEvent(Event * e);

	/**
	 * Shortcut method to remove an
	 * event from the queue.
     * 
	 * @param e The event to remove.
	 */
	void RemoveEvent(Event * e);

	/**
	 * Shortcut to mark an event as having been handled.
	 *
	 * @param e			The event to mark as completed.
	 * @param subsystem	The subsystem that has finished dealing with it.
	 */
	void MarkAsHandled(Event * e, Event::Subsystem subsystem);

	/**
	 * Remove events that have been handled
	 * by all relevant subsystems.
	 */
	void RemoveFinishedEvents();

	/**
	 * Remove all events in the queue.
	 */
	void PurgeEvents();
private:
	// Engine utility.
	LoggerInstance logger;

	/* Queue of events for running application;
	 * they represent messages between subsystems.
	 */
	vector<Event *> queue;
};