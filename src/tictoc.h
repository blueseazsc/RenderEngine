#ifndef TICTOC_H
#define TICTOC_H

#include <sys/time.h>
#include "config.h"

namespace framework {

class Timestamp {
public:
	Timestamp() {
		gettimeofday(&_startTime, NULL);
	}
	void update() {
		gettimeofday(&_startTime, NULL);
	}
	int64 getElapsedMilliSec()
	{
		return getElapsedMicroSec() * 0.001;
	}
	int64 getElapsedMicroSec()
	{
		timeval endTime;
		gettimeofday(&endTime, NULL);

		int64 diff = endTime.tv_sec - _startTime.tv_sec;
		return diff * 1000000 + (endTime.tv_usec - _startTime.tv_usec);
	}
protected:
	timeval _startTime;
};

}
#endif
