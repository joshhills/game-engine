#include "EventManager.h"

EventManager::EventManager() : logger("Event Manager")
{}

EventManager::~EventManager()
{
}

vector<Event *>& EventManager::GetEventQueue()
{
	return queue;
}

void EventManager::AddEvent(Event * e)
{
	queue.push_back(e);
}

void EventManager::MarkAsHandled(Event * e, Event::Subsystem subsystem)
{
	// Defensive check that subsystem is part of array.
	int index = find(e->subsystems.begin(), e->subsystems.end(), subsystem) - e->subsystems.begin();
	if (index < e->subsystems.size())
	{
		e->subsystems.erase(e->subsystems.begin() + index);
	}
}

void EventManager::RemoveFinishedEvents()
{
	int numRemoved = 0;

	// Remove-erase idiom adapted from StackOverflow 9927163 (not thread safe).
	for (vector<Event *>::iterator it = queue.begin(); it != queue.end();)
	{
		if((*it)->subsystems.size() == 0)
		{
			// Clear memory.
			delete (*it);
			it = queue.erase(it);
			numRemoved++;
		}
		else
		{
			++it;
		}
	}
	
	if (numRemoved > 0)
	{
		logger.Info("Removed " + to_string(numRemoved) + " events.");
	}
}

void EventManager::PurgeEvents()
{
	if (queue.size() > 0) {
		logger.Info("Purging " + to_string(queue.size()) + " events.");
	}

	// Delete all events before emptying queue.
	for (auto e : queue) {
		delete e;
	}

	queue.clear();
}