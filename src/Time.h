#ifndef SRC_TIME_H_
#define SRC_TIME_H_

#include <iostream>

class Time {

public:

	Time();
	Time(int hours, int min);
	int getHours() const;
	int getMinutes() const;

private:

	int hour;
	int min;
};

#endif /* SRC_TIME_H_ */
