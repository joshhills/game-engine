#include "EventManager.h"

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
}

vector<Event *>& EventManager::GetEventQueue()
{
	return queue;
}

void EventManager::addEvent(Event * e)
{
	queue.push_back(e);
}

void EventManager::removeFinishedEvents()
{
}

void EventManager::purgeEvents()
{
	if (queue.size() > 0) {
		std::cout << "Purging events, there were " << queue.size() << " events" << endl;
	}

	// Delete all events before emptying queue.
	for (auto e : queue) {
		delete e;
	}

	queue.clear();
}