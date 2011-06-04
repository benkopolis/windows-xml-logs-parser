#include "eventparser.h"
#include "../configuration.h"

EventParser::EventParser():
    _eventId(0)
{
	_filter = new DataFilter(Configuration::instance());
}

EventParser::EventParser(int eventId):
    _eventId(eventId)
{
	_filter = new DataFilter(Configuration::instance());
}
