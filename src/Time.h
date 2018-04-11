#ifndef SRC_TIME_H_
#define SRC_TIME_H_

#include <iostream>

class Time {

public:

	Time();
	Time(int hours, int min);
	int getHours() const;
	int getMinutes() const;

	void setHours(int hour);
	void setMinutes(int min);


private:

	int hour;
	int min;
};

#endif /* SRC_TIME_H_ */
