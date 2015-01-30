#include "WPILib.h"
#include "stdio.h"
#include "math.h"
class Robot: public SampleRobot
{
	//RobotDrive myRobot;
	Talon leftDriveMotor;
	Talon rightDriveMotor;
	Joystick DriveStick; // arcade drive joystick

public:
	Robot() :
			leftDriveMotor(0),
			rightDriveMotor(1),
			DriveStick(0)
	{
		//myRobot.SetExpiration(0.1);
	}
	float smoothJoyStick(float joyInput)
	{
		return powf(joyInput,3);
	}
	void customArcadeDrive() //the motor's speed is the joystick input multiplied by speedCoef, this way the crazy drivetrain can be slowed down
	{
		float x;
		float y;
		x=smoothJoyStick(DriveStick.GetX());
		y=smoothJoyStick(DriveStick.GetY());
		float speedCoef=(DriveStick.GetThrottle()+1)/-2;
		leftDriveMotor.Set((y+x)*speedCoef);
		rightDriveMotor.Set(-(y-x)*speedCoef); //the right side runs where -1 is full speed forward
	}
	void OperatorControl()
	{
		while (IsOperatorControl() && IsEnabled())
		{
			customArcadeDrive();
			Wait(0.005);				// wait for a motor update time
		}
	}

};

START_ROBOT_CLASS(Robot);
