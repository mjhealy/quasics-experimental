#ifndef StopDrive_H
#define StopDrive_H

#include "../CommandBase.h"
#include "WPILib.h"
#include "DrivePower.h"

class StopDrive : public DrivePower
{
public:
	StopDrive() : DrivePower("stop", 0, 0, 0) {}
};

#endif
