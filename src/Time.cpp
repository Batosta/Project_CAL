#include "Time.h"

using namespace std;

Time::Time() {

}

Time::Time(int hour, int min){

	this->hour = hour;
	this->min = min;
}
int Time::getHours() const{

	return this->hour;
}
int Time::getMinutes() const{

	return this->min;
}


void Time::setHours(int hour){

	this->hour = hour;
}
void Time::setMinutes(int min){

	this->min = min;
}
