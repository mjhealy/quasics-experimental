#ifndef DrivePower_H
#define DrivePower_H

#include "../CommandBase.h"
#include "WPILib.h"
#include <algorithm>
#include <sys/time.h>
#include <string>

class DrivePower: public CommandBase
{
private:
	float _left;
	float _right;
	float _duration;
	timeval _endTime;

	int counter;

public:
	DrivePower(const char* name, float leftPower, float rightPower, float duration);
	virtual void Initialize();
	virtual void Execute();
	virtual void End();
	virtual bool IsFinished();
	virtual void Interrupted();
};

#endif
