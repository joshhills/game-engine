#pragma once

#include <vector>
#include "Event.h"

using namespace std;

class EventManager {
public:
	EventManager();
	~EventManager();

	vector<Event *> & GetEventQueue();

	void addEvent(Event * e);
private:
	// Queue of events for running application.
	vector<Event *> queue;
};