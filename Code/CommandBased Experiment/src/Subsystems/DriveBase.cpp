#include "DriveBase.h"
#include "../Commands/StopDrive.h"
#include "../RobotMap.h"
#include <algorithm>

#define allocateTalon(s,e)	talons[s][e].reset(new Talon(MotorChannels[s][e]))

DriveBase::DriveBase() :
	Subsystem("DriveBase")
{
	allocateTalon(Left, Front);
	allocateTalon(Right, Front);
	allocateTalon(Left, Rear);
	allocateTalon(Right, Rear);
}

float DriveBase::AdustPower(Side side, End end, float powerPercent) {
	const float baseInverter = (side == Right) ? -1 : 1;
	const float normalizedPower = std::max(std::min(powerPercent, 1.0f), 0.0f);
	return baseInverter * normalizedPower;
}

void DriveBase::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(new StopDrive());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void DriveBase::SetPower(Side side, float powerPercent) {
	talons[side][Front]->Set(AdustPower(side, Front, powerPercent));
	talons[side][Rear]->Set(AdustPower(side, Rear, powerPercent));
}

DriveBase& DriveBase::GetInstance() {
	static DriveBase singleton;
	return singleton;
}
