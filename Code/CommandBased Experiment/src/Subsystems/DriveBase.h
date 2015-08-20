#ifndef DriveBase_H
#define DriveBase_H

#include <Commands/Subsystem.h>
#include <WPILib.h>
#include <memory>
#include "../RobotMap.h"

class DriveBase: public Subsystem
{
private:
    std::auto_ptr<Talon> talons[2][2];

private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
    static float AdustPower(Side side, End end, float powerPercent);

private:
	DriveBase();

public:
	virtual void InitDefaultCommand();

	void SetLeftPower(float powerPercent)  { SetPower(Left, powerPercent); }
	void SetRightPower(float powerPercent) { SetPower(Right, powerPercent); }
	void SetPower(Side side, float powerPercent);

	static DriveBase& GetInstance();
};

#endif
