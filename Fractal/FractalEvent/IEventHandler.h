#ifndef _IEVENTHANDLER_H
#define _IEVENTHANDLER_H
#include "Channel.h"
using namespace fractal;
using namespace fevent;

template<typename tEvent>
class EventHandler {
	EventHandler() {
		Channel::addHandler<tEvent>(this);
	}

	virtual ~EventHandler() {
		Channel::remove<tEvent>(this);
	}

	virtual void operator()(const tEvent&) = 0;
};
#endif // !_IEVENTHANDLER_H
