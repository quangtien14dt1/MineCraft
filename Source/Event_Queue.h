#pragma once

#include <queue>

using EventID = unsigned int;

class EventQueue {
public:
	void AddEvent(const EventID& e) {}

	bool ProcessEvents(EventID& _id) {
		if (_queue.empty()) { return false; }
		_id = _queue.front();
		_queue.pop();
		return true;
	}

	void Clear() { while (!_queue.empty()) { _queue.pop(); } }
private:
	std::queue<EventID> _queue;
};