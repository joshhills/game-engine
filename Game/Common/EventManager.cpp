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
