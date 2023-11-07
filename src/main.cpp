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
	ADIDigitalIn stopperButton('A');
	Motor_Group cataGroup({rightCatapult, leftCatapult});
	

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
	cataGroup.set_brake_modes(MOTOR_BRAKE_HOLD);
	cataGroup.set_encoder_units(MOTOR_ENCODER_DEGREES);
	backLeft.set_encoder_units(MOTOR_ENCODER_ROTATIONS);
	backRight.set_encoder_units(MOTOR_ENCODER_ROTATIONS);
	middleLeft.set_encoder_units(MOTOR_ENCODER_ROTATIONS);
	middleRight.set_encoder_units(MOTOR_ENCODER_ROTATIONS);
	frontLeft.set_encoder_units(MOTOR_ENCODER_ROTATIONS);
	frontRight.set_encoder_units(MOTOR_ENCODER_ROTATIONS);
	
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
delay((rotations / 2) * 400);
}

void drivebackwards(int rotations, int velocity) {
frontLeft.move_relative(-rotations, velocity);
backLeft.move_relative(-rotations, velocity);
middleLeft.move_relative(-rotations, velocity);
middleRight.move_relative(-rotations, velocity);
backRight.move_relative(-rotations, velocity);
frontRight.move_relative(-rotations, velocity);
delay((rotations / 2) * 400);
}

void turnleft(int rotations, int velocity) {
frontLeft.move_relative(-rotations, velocity);
backLeft.move_relative(-rotations, velocity);
middleLeft.move_relative(-rotations, velocity);
middleRight.move_relative(rotations, velocity);
backRight.move_relative(rotations, velocity);
frontRight.move_relative(rotations, velocity);
delay((rotations / 2) * 400);
}

void turnright(int rotations, int velocity) {
frontLeft.move_relative(rotations, velocity);
backLeft.move_relative(rotations, velocity);
middleLeft.move_relative(rotations, velocity);
middleRight.move_relative(-rotations, velocity);
backRight.move_relative(-rotations, velocity);
frontRight.move_relative(-rotations, velocity);
delay((rotations / 2) * 400);
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
	driveforward(1.1, 200);
	delay(2000);
	drivebackwards(1, 40);
	
	/*
	P_cataFire();
	frontLeft.move_velocity(-5);
	backLeft.move_velocity(-5);
	middleLeft.move_velocity(-5);
	middleRight.move_velocity(-5);
	backRight.move_velocity(-5);
	frontRight.move_velocity(-5);
	*/

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

void catapultfiremanual () {
		if (master.get_digital(E_CONTROLLER_DIGITAL_R2)) {
			cataGroup.move(80);
			delay(5);
			cataGroup.brake();
		}
		if (master.get_digital(E_CONTROLLER_DIGITAL_R1)){
			cataGroup.move(50);
			delay(5);
			cataGroup.brake();
		}
}

void opcontrol() {
	//cataGroup.move_relative(88.8 * 3.0, 50);
		//while (!((rightCatapult.get_position() < 268.4) && (rightCatapult.get_position() > 264.4))){
		 //	delay(5);
		//}
		//rightCatapult.tare_position();
	
	while(true){
		
		catapultfiremanual();
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
	}
}