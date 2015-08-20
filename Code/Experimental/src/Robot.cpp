#include "WPILib.h"

class Robot: public IterativeRobot
{
	// RobotDrive myRobot; // robot drive system
	// Motor port definitions
	const int FrontRightTalonPort = 8;
	const int FrontLeftTalonPort = 6;
	const int RearLeftTalonPort = 7;
	const int RearRightTalonPort = 9;
	// Encoder definitions
	const int LeftEncoderA = 2;
	const int LeftEncoderB = 3;
	const int RightEncoderA = 0;
	const int RightEncoderB = 1;

	// RobotDrive myRobot; // robot drive system
    Talon leftFront;
    Talon leftRear;
    Talon rightFront;
    Talon rightRear;
	Joystick stick; // only joystick
	LiveWindow *lw;
	int autoLoopCounter;

public:
	Robot() :
		// myRobot(0, 1),	// these must be initialized in the same order
		leftFront(FrontLeftTalonPort),
		leftRear(RearLeftTalonPort),
		rightFront(FrontRightTalonPort),
		rightRear(RearRightTalonPort),
		stick(0),		// as they are declared above.
		lw(NULL),
		autoLoopCounter(0)
	{
		// myRobot.SetExpiration(0.1);
	}

private:
	void SetDrivePower(float leftDrivePower, float rightDrivePower) {
		leftFront.Set(leftDrivePower);
		leftRear.Set(leftDrivePower);
		rightFront.Set(-rightDrivePower);
		rightRear.Set(-rightDrivePower);
	}

	virtual void RobotInit()
	{
		lw = LiveWindow::GetInstance();
	}

	virtual void AutonomousInit()
	{
		autoLoopCounter = 0;
	}

	virtual void AutonomousPeriodic()
	{
		if(autoLoopCounter < 100) //Check if we've completed 100 loops (approximately 2 seconds)
		{
			SetDrivePower(0.5, 0.5); 	// drive forwards half speed
			autoLoopCounter++;
		} else {
			SetDrivePower(0.0, 0.0); 	// stop robot
		}
	}

	virtual void TeleopInit()
	{

	}

	virtual void TeleopPeriodic()
	{
		// myRobot.ArcadeDrive(stick); // drive with arcade style (use right stick)
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
