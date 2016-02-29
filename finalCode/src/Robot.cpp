#include "WPILib.h"

class Robot: public SampleRobot
{
	Joystick stick1;
	Joystick stick2;
	Joystick gamePad;
	Talon leftFront;
	Talon leftBack;
	Talon rightFront;
	Talon rightBack;
	Talon intake;
	Encoder leftEncoder;
	Encoder rightEncoder;
	DoubleSolenoid tiltA;
	DoubleSolenoid tiltB;
	DoubleSolenoid intakePNUA;
	DoubleSolenoid intakePNUB;
	Solenoid innerMast1;
	Solenoid innerMast2;
	DoubleSolenoid plate;
	Solenoid carriage;
	Servo cameraTilt;
	Servo cameraRotate;
	bool switchCtrl;
	DigitalInput switch1;
	DigitalInput switch2;
	DigitalInput switch3;
	Compressor compressor;
	bool previous_button1_pressed;
	bool previous_button2_pressed;

public:
	Robot() :
		stick1(0),
		stick2(1),
		gamePad(2),
		leftFront(3),
		leftBack(4),
		rightFront(0),
		rightBack(1),
		intake(2),
		leftEncoder(1, 2, false, Encoder::k4X),
		rightEncoder(8, 9, false, Encoder::k4X),
		tiltA(0,0,1),
		tiltB(0,2,3),
		intakePNUA(0,4,5),
		intakePNUB(0,6,7),
		innerMast1(1,0),
		innerMast2(1,1),
		plate(1,2,3),
		carriage(1,4),
		cameraTilt(5),
		cameraRotate(6),
		switchCtrl(false),
		switch1(5),
		switch2(6),
		switch3(7),
		compressor(0),
		previous_button1_pressed(false),
		previous_button2_pressed(false)
	{
		leftEncoder.SetSamplesToAverage(5);
		leftEncoder.SetDistancePerPulse(1.0/360);

		rightEncoder.SetSamplesToAverage(5);
		rightEncoder.SetDistancePerPulse(1.0/360);
	}

	void deployIntake()
	{
		intakePNUA.Set(DoubleSolenoid::Value::kForward);
		intakePNUB.Set(DoubleSolenoid::Value::kForward);
	}
	void moveForward (double driveForward)
	{
		double rEncVal = 0;
		leftEncoder.Reset();
		rightEncoder.Reset();
		while (fabs(rightEncoder.GetDistance() < driveForward) &&
				fabs(leftEncoder.GetDistance() < driveForward) &&
				IsAutonomous() && IsEnabled());
		{
			rEncVal = (fabs(rightEncoder.GetDistance()));
			leftFront.Set(-0.5);
			leftBack.Set(-0.5);
			rightFront.Set(0.5);
			rightBack.Set(0.5);
			SmartDashboard::PutNumber("Test Encoder Value: ", rEncVal);
		}
		rightFront.Set(0);
		rightBack.Set(0);
		leftFront.Set(0);
		leftBack.Set(0);

	}
	void turn180 (double driveForward)
	{
		double rEncVal = 0;
		leftEncoder.Reset();
		rightEncoder.Reset();
		while (fabs(rightEncoder.GetDistance() < driveForward) &&
				fabs(leftEncoder.GetDistance() < driveForward) &&
				IsAutonomous() && IsEnabled());
		{
			rEncVal = (fabs(rightEncoder.GetDistance()));
			leftFront.Set(0.45);
			leftBack.Set(0.45);
			rightFront.Set(0.45);
			rightBack.Set(0.45);
			SmartDashboard::PutNumber("Test Encoder Value: ", rEncVal);
		}
		rightFront.Set(0);
		rightBack.Set(0);
		leftFront.Set(0);
		leftBack.Set(0);

	}
	void moveSlow(double driveDistance)
	{
		double rEncVal = 0;
		leftEncoder.Reset();
		rightEncoder.Reset();
		while (fabs(rightEncoder.GetDistance() < driveDistance) &&
				fabs(leftEncoder.GetDistance() < driveDistance) &&
				IsAutonomous() && IsEnabled())
		{
			rEncVal = (fabs(rightEncoder.GetDistance()));
			leftFront.Set(-0.45);
			leftBack.Set(-0.45);
			rightFront.Set(0.45);
			rightBack.Set(0.45);
			SmartDashboard::PutNumber("Test Encoder Value: ", rEncVal);
		}
		rightFront.Set(0);
		rightBack.Set(0);
		leftFront.Set(0);
		leftBack.Set(0);
	}
	void moveSlowBack(double driveSlow)
	{
		double rEncVal = 0;
		leftEncoder.Reset();
		rightEncoder.Reset();
		while (fabs(rightEncoder.GetDistance() < driveSlow) &&
				fabs(leftEncoder.GetDistance() < driveSlow) &&
				IsAutonomous() && IsEnabled())
		{
			rEncVal = (fabs(rightEncoder.GetDistance()));
			leftFront.Set(0.45);
			leftBack.Set(0.45);
			rightFront.Set(-0.45);
			rightBack.Set(-0.45);
			SmartDashboard::PutNumber("Test Encoder Value: ", rEncVal);
		}
		rightFront.Set(0);
		rightBack.Set(0);
		leftFront.Set(0);
		leftBack.Set(0);
	}

	void bdAuto()

	{
		moveForward(2);
		Wait(1);
		moveSlow(2);
		Wait(1);
		moveForward(2);
		Wait(1);
		deployIntake();
		if(switch3.Get()== 1)
		{

			intake.Set(0.5);
			Wait(0.5);
			turn180(1);
		}
	}
	void portcullisAuto()
	{
		plate.Set(DoubleSolenoid::Value::kForward);
		Wait(1);
		tiltA.Set(DoubleSolenoid::Value::kForward);
		tiltB.Set(DoubleSolenoid::Value::kForward);
		Wait(1);
		moveForward(2);
		Wait(1);
		moveSlow(1);
		Wait(1);
		plate.Set(DoubleSolenoid::Value::kReverse);
		Wait(1);
		moveSlowBack(0.5);
		Wait(1);
		innerMast1.Set(DoubleSolenoid::Value::kForward);
		innerMast2.Set(DoubleSolenoid::Value::kForward);
		Wait(1);
		moveSlow(2.5);
		deployIntake();
		if(switch3.Get()== 1)
		{
			intake.Set(0.5);
			Wait(0.5);
			turn180(1);
		}

	}
	void chevalAuto()
	{
		plate.Set(DoubleSolenoid::Value::kForward);
		Wait(1);
		tiltA.Set(DoubleSolenoid::Value::kForward);
		tiltB.Set(DoubleSolenoid::Value::kForward);
		Wait(1);
		innerMast1.Set(DoubleSolenoid::Value::kForward);
		innerMast2.Set(DoubleSolenoid::Value::kForward);
		Wait(1);
		moveForward(2);
		Wait(1);
		moveSlow(1);
		Wait(1);
		innerMast1.Set(DoubleSolenoid::Value::kReverse);
		innerMast2.Set(DoubleSolenoid::Value::kReverse);
		Wait(1);
		moveSlow(1.0);
		innerMast1.Set(DoubleSolenoid::Value::kForward);
		innerMast2.Set(DoubleSolenoid::Value::kForward);
		Wait(1);
		moveSlow(2.5);
		Wait(1);
		deployIntake();
		if(switch3.Get()== 1)
		{
			intake.Set(0.5);
			Wait(0.5);
			turn180(1);
		}
	}
	void intakeOuttake()
	{
		if(switchCtrl== true)
		{
			if(gamePad.GetRawButton(5))
			{
				intake.Set(-1);
			}
			else if(gamePad.GetRawButton(6))
			{
				intake.Set(1);
			}
			else if(gamePad.GetRawButton(8))
			{
				intake.Set(0.5);
			}
			else
			{
				intake.Set(0);
			}
			bool current_button1_pressed = gamePad.GetRawButton(1);
			if (previous_button1_pressed == false && current_button1_pressed)
			{
				DoubleSolenoid::Value current_value = intakePNUA.Get();
				// toggle value
				if (DoubleSolenoid::Value::kForward == current_value)
				{
					intakePNUA.Set(DoubleSolenoid::Value::kReverse);
					intakePNUB.Set(DoubleSolenoid::Value::kReverse);
				}
				else
				{
					intakePNUA.Set(DoubleSolenoid::Value::kForward);
					intakePNUB.Set(DoubleSolenoid::Value::kForward);
				}
			}
			previous_button1_pressed = current_button1_pressed;
		}
	}

	void RobotInit() override
			{
		CameraServer::GetInstance()->SetQuality(50);
		CameraServer::GetInstance()->StartAutomaticCapture("cam0");
			}
	void drive()
	{

		float leftDrive=-stick1.GetRawAxis(1);
		float rightDrive=stick2.GetRawAxis(1);
		float secondLeftDrive=-gamePad.GetRawAxis(3);
		float secondRightDrive=gamePad.GetRawAxis(1);
		if(switchCtrl == false)
		{
			if(fabs(leftDrive) > 0.2)
			{
				//leftFront.Set(leftDrive);
				//leftBack.Set(leftDrive);
				if(stick1.GetRawButton(1) || stick2.GetRawButton(1))
				{
					leftFront.Set(0.45*leftDrive);
					leftBack.Set(0.45*leftDrive);
				}
				else
				{
					leftFront.Set(leftDrive);
					leftBack.Set(leftDrive);
				}
			}
			else
			{
				leftFront.Set(0);
				leftBack.Set(0);
			}
			if(fabs(rightDrive)> 0.2)
			{
				if(stick1.GetRawButton(1) || stick2.GetRawButton(1))
				{
					rightFront.Set(0.45*rightDrive);
					rightBack.Set(0.45*rightDrive);
				}
				else
				{
					rightFront.Set(rightDrive);
					rightBack.Set(rightDrive);
				}
			}
			else
			{
				rightFront.Set(0);
				rightBack.Set(0);
			}
		}
		SmartDashboard::PutNumber("Left Stick", leftDrive);
		SmartDashboard::PutNumber("Right Stick", rightDrive);
		SmartDashboard::PutString("Controller Mode",switchCtrl? "Gamepad" : "Joystick");
		if(gamePad.GetRawButton(9))
		{
			switchCtrl = true;
		}
		if(stick1.GetRawButton(7) || stick2.GetRawButton(7))
		{
			switchCtrl = false;
		}
		//GamePad Drive
		if(switchCtrl == true)
		{
			if(fabs(secondRightDrive) > 0.2)
			{
				if(gamePad.GetRawButton(7))
				{
					rightFront.Set(0.45*-secondRightDrive);
					rightBack.Set(0.45*-secondRightDrive);
				}
				else
				{
					rightFront.Set(-secondRightDrive);
					rightBack.Set(-secondRightDrive);
				}
			}
			else
			{
				rightFront.Set(0);
				rightBack.Set(0);
			}
			if(fabs(secondLeftDrive) > 0.2 && switchCtrl == true)
			{
				if(gamePad.GetRawButton(7))
				{
					leftFront.Set(0.45*-secondLeftDrive);
					leftBack.Set(0.45*-secondLeftDrive);
				}
				else
				{
					leftFront.Set(-secondLeftDrive);
					leftBack.Set(-secondLeftDrive);
				}
			}
			else
			{
				leftFront.Set(0);
				leftBack.Set(0);
			}
		}

	}
	void camera()
	{
		//Toggle Camera and stick Driving
		const float POSITION_1 = 0.4;
		const float POSITION_2 = 0.6;
		const float POSITION_INTAKE = 0.5;
		if(switchCtrl==false)
		{
			if((stick1.GetRawButton(8) && cameraTilt.Get() == POSITION_1) || (stick2.GetRawButton(8) && cameraTilt.Get() == POSITION_1))
			{
				cameraRotate.Set(1);
				cameraTilt.Set(POSITION_2);
			}
			if((stick1.GetRawButton(8) && cameraTilt.Get() == POSITION_2) || (stick2.GetRawButton(8) && cameraTilt.Get() == POSITION_2))
			{
				cameraRotate.Set(1);
				cameraTilt.Set(POSITION_1);
			}
		}
		//GamePad Driving
		if(switchCtrl == true)
		{
			cameraRotate.Set(0);
			cameraTilt.Set(POSITION_INTAKE);
		}
	}
	void forklift()
	{
		if(switchCtrl == false)
		{
			//Cross the Portcullis and Stick Driving
			if(stick1.GetRawButton(4) || stick2.GetRawButton(4))
			{
				carriage.Set(true);
				Wait(1);
				leftFront.Set(0.75);
				leftBack.Set(0.75);
				rightFront.Set(0.75);
				rightBack.Set(0.75);
				Wait(0.9);
			}
			else
			{
				innerMast1.Set(false);
				innerMast2.Set(false);
			}
			bool current_button2_pressed = gamePad.GetRawButton(2);
			if (previous_button2_pressed == false && current_button2_pressed)
			{
				DoubleSolenoid::Value current_value = tiltA.Get();
				// toggle values
				if (DoubleSolenoid::Value::kForward == current_value)
				{
					tiltA.Set(DoubleSolenoid::Value::kReverse);
					tiltB.Set(DoubleSolenoid::Value::kReverse);
				}
				else
				{
					tiltA.Set(DoubleSolenoid::Value::kForward);
					tiltB.Set(DoubleSolenoid::Value::kForward);
				}
			}
			previous_button2_pressed = current_button2_pressed;

			//Cheval de Frise
			if(stick1.GetRawButton(3) || stick2.GetRawButton(3))
			{
				innerMast1.Set(true);
				innerMast2.Set(true);
				if(plate.Get()==DoubleSolenoid::Value::kReverse)
				{
					plate.Set(DoubleSolenoid::Value::kForward);
				}
				Wait(0.9);
				leftFront.Set(0.5);
				leftBack.Set(0.5);
				rightFront.Set(0.5);
				rightBack.Set(0.5);
				Wait(0.5);
				innerMast1.Set(false);
				innerMast2.Set(false);
				Wait(0.75);
				leftFront.Set(0.5);
				leftBack.Set(0.5);
				rightFront.Set(0.5);
				rightBack.Set(0.5);
				Wait(0.9);

				plate.Set(DoubleSolenoid::Value::kReverse);
			}
			//Hanging
			if(stick1.GetRawButton(5))
			{
				plate.Set(DoubleSolenoid::Value::kReverse);
				Wait(0.25);
				innerMast1.Set(DoubleSolenoid::Value::kForward);
				innerMast2.Set(DoubleSolenoid::Value::kForward);
				carriage.Set(true);
				Wait(0.25);
				plate.Set(DoubleSolenoid::Value::kReverse);
				carriage.Set(false);
				innerMast2.Set(DoubleSolenoid::Value::kReverse);
				innerMast1.Set(DoubleSolenoid::Value::kReverse);

			}
		}

	}
	void Autonomous()
	{
		while(IsAutonomous())
		{

			if(switch1.Get()== 0 && switch2.Get()== 0 )
			{
				chevalAuto();
			}
			if(switch1.Get()== 0 && switch2.Get()== 1 )
			{
				portcullisAuto();
			}
			if(switch1.Get()== 1 && (switch2.Get()== 0 || switch2.Get()== 1))
			{
				bdAuto();
			}
		}
	}
	void OperatorControl()
	{
		while(IsOperatorControl())
		{
			intakeOuttake();
			forklift();
			camera();
			drive();
		}
	}
	void Test()
	{
	}
};
START_ROBOT_CLASS(Robot)
