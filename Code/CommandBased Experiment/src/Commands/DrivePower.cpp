#include "DrivePower.h"
#include "../Subsystems/DriveBase.h"
#include <sys/time.h>


DrivePower::DrivePower(const char* name, float leftPower, float rightPower, float durationMSec)
	: CommandBase(name),
	  _left(std::max(std::min(leftPower, 1.0f), 0.0f)),
	  _right(std::max(std::min(rightPower, 1.0f), 0.0f)),
	  _duration(durationMSec),
	  counter(0)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(&DriveBase::GetInstance());
}

#define USE_TIMING

// Called just before this Command runs the first time
void DrivePower::Initialize()
{
#ifdef USE_TIMING
	timeval now;
	if (gettimeofday(&now, 0) == 0) {
		printf("Time is now: %d:%d\n", int(now.tv_sec), int(now.tv_usec));
		timeval offset = {time_t(_duration / 1000), time_t((int(_duration) % 1000) * 1000)};
		timeradd(&now, &offset, &_endTime);
		printf("End time is: %d:%d\n", int(_endTime.tv_sec), int(_endTime.tv_usec));
		DriveBase::GetInstance().SetPower(Left, _left);
		DriveBase::GetInstance().SetPower(Right, _right);
	}
#else
	counter = 0;
	DriveBase::GetInstance().SetPower(Left, _left);
	DriveBase::GetInstance().SetPower(Right, _right);
#endif
}

// Called repeatedly when this Command is scheduled to run
void DrivePower::Execute()
{
#if !defined( USE_TIMING )
	counter = counter + 1;
	printf("Counter is now: %d\n", counter);
#endif
}


// Make this return true when this Command no longer needs to run execute()
bool DrivePower::IsFinished()
{
#ifdef USE_TIMING
	timeval now;
	if (gettimeofday(&now, 0) != 0) {
		// Error: couldn't get time of day, so we'll assume we're done.
		return true;
	}
	printf("Time is now: %d:%d\n", int(now.tv_sec), int(now.tv_usec));
	return (timercmp(&now, &_endTime, >=));
#else
	const bool finished = counter > 10;
	printf("IsFinished() ==> %s\n", finished ? "true" : "false");
	return finished;
#endif
}

// Called once after isFinished returns true
void DrivePower::End()
{
	DriveBase::GetInstance().SetPower(Left, _left);
	DriveBase::GetInstance().SetPower(Right, _right);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DrivePower::Interrupted()
{
	End();
}
