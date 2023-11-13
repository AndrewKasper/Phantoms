#include "main.h"

using namespace pros;

	Controller master(E_CONTROLLER_MASTER);
	Motor frontLeft(4, true); 
	Motor middleLeft(6, true);
	Motor backLeft(8, true);
	Motor frontRight(3);
	Motor middleRight(5);
	Motor backRight(7);
	Motor rightCatapult(10, E_MOTOR_GEAR_RED, true);
	Motor leftCatapult(9, E_MOTOR_GEAR_RED);
	//ADIDigitalIn stopperButton('A');
	Motor_Group cataGroup({rightCatapult, leftCatapult});
    pros::Rotation rotationSensor(2,true);
	ADIDigitalOut SolenoidR('A');
	ADIDigitalOut SolenoidL('B');
	// int speed = 100;
	

	// int stopperGotPressed = 0;
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */


void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
	SolenoidL.set_value(LOW);
	SolenoidR.set_value(HIGH);
	cataGroup.set_brake_modes(MOTOR_BRAKE_HOLD);
	cataGroup.set_encoder_units(MOTOR_ENCODER_DEGREES);
	backLeft.set_encoder_units(MOTOR_ENCODER_ROTATIONS);
	backRight.set_encoder_units(MOTOR_ENCODER_ROTATIONS);
	middleLeft.set_encoder_units(MOTOR_ENCODER_ROTATIONS);
	middleRight.set_encoder_units(MOTOR_ENCODER_ROTATIONS);
	frontLeft.set_encoder_units(MOTOR_ENCODER_ROTATIONS);
	frontRight.set_encoder_units(MOTOR_ENCODER_ROTATIONS);
	//rotationSensor.set_position(0);
	//rotationSensor.reset_position();
	//delay(500);
	
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */

void P_cataFire(){
	cataGroup.move_velocity(65);
}

void driveforward(int rotations, int velocity) {
frontLeft.move_relative(rotations, velocity);
backLeft.move_relative(rotations, velocity);
middleLeft.move_relative(rotations, velocity);
middleRight.move_relative(rotations, velocity);
backRight.move_relative(rotations, velocity);
frontRight.move_relative(rotations, velocity);
}

void drivebackwards(int rotations, int velocity) {
frontLeft.move_relative(-rotations, -velocity);
backLeft.move_relative(-rotations, -velocity);
middleLeft.move_relative(-rotations, -velocity);
middleRight.move_relative(-rotations, -velocity);
backRight.move_relative(-rotations, -velocity);
frontRight.move_relative(-rotations, -velocity);
}

void turnleft(int rotations, int velocity) {
frontLeft.move_relative(-rotations, -velocity);
backLeft.move_relative(-rotations, -velocity);
middleLeft.move_relative(-rotations, -velocity);
middleRight.move_relative(rotations, velocity);
backRight.move_relative(rotations, velocity);
frontRight.move_relative(rotations, velocity);
}

void turnright(int rotations, int velocity) {
frontLeft.move_relative(rotations, velocity);
backLeft.move_relative(rotations, velocity);
middleLeft.move_relative(rotations, velocity);
middleRight.move_relative(-rotations, -velocity);
backRight.move_relative(-rotations, -velocity);
frontRight.move_relative(-rotations, -velocity);
}

void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	delay(1000);
	// JUST PUSH CODE
	
	driveforward(1.2, 200);
	delay(2000);
	drivebackwards(0.5, 40);
	delay(200);
	//SolenoidL.set_value(HIGH);
	//drivebackwards(0.5, 40);
	//delay(1500);
	//turnleft(3, 60);
	
	

	// END OF JUST PUSH CODE
  
	// NEAR SIDE CODE
	/*
	driveforward(1, 50);
	delay(1000);
	SolenoidL.set_value(HIGH);
	delay(500);
	drivebackwards(0.8, 50);
	delay(1000);
	turnleft(1.4, 30);
	delay(1000);
	drivebackwards(3, 60);
	delay(1000);
	*/
	// END OF NEAR SIDE CODE

	// AUTONOMOUS SKILLS CODE
/*
	P_cataFire();
	frontLeft.move_velocity(-3);
	backLeft.move_velocity(-3);
	middleLeft.move_velocity(-3);
	middleRight.move_velocity(-3);
	backRight.move_velocity(-3);
	frontRight.move_velocity(-3);
*/
	// END OF AUTONOMOUS SKILLS CODE

/*
driveforward(1, 80);
delay(1000);
turnleft(1, 80);
delay(1000);
driveforward(2, 80);
delay(1000);
drivebackwards(2, 80);
*/


}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
/*
void catapultfire () {
	while(true){
		if (master.get_digital(E_CONTROLLER_DIGITAL_R2)) {
			rightCatapult.tare_position();
			cataGroup.move_relative(48.2 , 50);
				while (!((rightCatapult.get_position() > 45.8) && (rightCatapult.get_position() < 47.8))){
					delay(5);
				}
			delay(30);
			cataGroup.move_relative(311.9, 50);
				while (!((rightCatapult.get_position() > 358) && (rightCatapult.get_position() < 362))){
					delay(5);
				}
			rightCatapult.tare_position();
		}
	};
}
*/
// void catapultfiremanual () {
// 		if (master.get_digital(E_CONTROLLER_DIGITAL_R2)) {
// 			cataGroup.move(80);
// 			delay(5);
// 			cataGroup.brake();
// 		}
// 		if (master.get_digital(E_CONTROLLER_DIGITAL_R1)){
// 			cataGroup.move(50);
// 			delay(5);
// 			cataGroup.brake();
// 		}
// }
/*
void catapultfire () {
		if (rotationSensor.get_position() == 88) {
			if (master.get_digital(E_CONTROLLER_DIGITAL_R2))
			{
				cataGroup.move_velocity(100);
			}
		else
			cataGroup.brake();
		}
}
*/

void rotationalCata() {
	while (true)
	{
		while ((rotationSensor.get_angle() < 7700) || (rotationSensor.get_angle() > 8500))
		{
			cataGroup.move(127);
		}
		cataGroup.move(0);
		cataGroup.brake();
		if (master.get_digital(E_CONTROLLER_DIGITAL_R2))
		{
			int motorP = rightCatapult.get_position();
			int fireM = 20;
			int grace = 5;
			cataGroup.move_relative(fireM, 100);
			while ((rightCatapult.get_position() < motorP + fireM - grace) || (rightCatapult.get_position() > motorP + fireM + grace)){
				delay(5);
			}
			delay(100);
		}	
	}
}

void opcontrol() {
	SolenoidL.set_value(LOW);
	SolenoidR.set_value(HIGH);
	int OCINT = 0;
	Task fireCatapult(rotationalCata);
	while(true){
		int forward_val =  master.get_analog(ANALOG_LEFT_Y);
		int turn_val =  master.get_analog(ANALOG_RIGHT_X) > 5 || master.get_analog(ANALOG_RIGHT_X) < -5 ? master.get_analog(ANALOG_RIGHT_X) : 0;

		int right_motors = forward_val - turn_val;
		int left_motors = forward_val + turn_val;

		frontLeft = left_motors;
		middleLeft = left_motors;
		backLeft = left_motors;
		
		frontRight = right_motors;
		middleRight = right_motors;
		backRight = right_motors;

		if (master.get_digital(E_CONTROLLER_DIGITAL_L2) == 1)
		{
			if(OCINT == 0)
			{
				SolenoidL.set_value(HIGH);
				SolenoidR.set_value(LOW);
				OCINT = 1;
				delay(500);
			}
			else
			{
				SolenoidL.set_value(LOW);
				SolenoidR.set_value(HIGH);
				OCINT = 0;
				delay(500);
			}
			
		}
		if (master.get_digital(E_CONTROLLER_DIGITAL_L1) == 1)
		{
			if(OCINT == 0)
			{
				SolenoidL.set_value(HIGH);
				OCINT = 1;
				delay(500);
			}
			else
			{
				SolenoidL.set_value(LOW);
				OCINT = 0;
				delay(500);
			}
		}
		if (master.get_digital(E_CONTROLLER_DIGITAL_R1) == 1)
		{
			if(OCINT == 0)
			{
				SolenoidR.set_value(LOW);
				OCINT = 1;
				delay(500);
			}
			else
			{
				SolenoidR.set_value(HIGH);
				OCINT = 0;
				delay(500);
			}
			
		}
	}
		
		
	
}