
#include "vex.h"
#include "pictures.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name] [Type] [Port(s)]
// rightFront motor 9 
// rightBack motor 15 
// rightMid motor 21 
// leftFront motor 4 
// leftBack motor 14 
// leftMid motor 12 
// Controller1 controller 
// Intake motor 1 
// Inertial inertial 5 
// MOGO digital_out A 
// detected distance 10 
// Upper motor 20 
// mogo digital_out B 
// opticalsensor optical 3 
// aligner distance 13 
// WallStakes motor 17 
// rotationSensor rotation 6 
// Doinker digital_out C 
// ---- END VEXCODE CONFIGURED DEVICES ----

using namespace vex;
competition Competition;



Drive chassis(

ZERO_TRACKER_NO_ODOM,



//Left Motors:
motor_group(leftFront,leftMid,leftBack),

//Right Motors:

motor_group(rightFront, rightBack, rightMid),


PORT5,


3.25,


0.8,

//Gyro scale, this is what gyro reads when you spin the robot 360 degrees.

//CHANGED

//CHANGED
//CHANGED
//CHANGED
//CHANGED

356.5,

//CHANGED
//CHANGED
//CHANGED








//LF: //RF: 
PORT2, -PORT20,

//LB: //RB: 
PORT17, -PORT11,

3,
2.75,

-2,


1,

-2.75,

5.5

);






void TurnAntiClockwise(double howmuch){
 Inertial.resetRotation();
 rightFront.setVelocity(40, percent);
 rightMid.setVelocity(40, percent);
 leftFront.setVelocity(40, percent);
 leftMid.setVelocity(40, percent);
 leftBack.setVelocity(40, percent);
 rightBack.setVelocity(40, percent);
 while (true) {
 if(Inertial.rotation(degrees) > (howmuch*-1)){
 leftFront.spin(reverse);
 leftMid.spin(reverse);
 leftBack.spin(reverse);
 rightFront.spin(forward);
 rightMid.spin(forward);
 rightBack.spin(forward);
 }
 else if (Inertial.rotation(degrees) < (howmuch*-1)){
 leftFront.stop();
 leftMid.stop();
 leftBack.stop();
 rightFront.stop();
 rightMid.stop();
 rightBack.stop(); 
 return;
 }
 }
 }













































//REAL PID



// Drivetrain PID Function
void drivePID(double targetdegrees) {
 double kp = 1;
 double ki = 0.1;
 double kd = 0.1;
 double error = targetdegrees;
 double integral = 0;
 double lasterror = error;
 double speed;
 double prevdegrees = leftFront.position(degrees);

 double count = 0;

 leftFront.setPosition(0, degrees);
 leftBack.setPosition(0, degrees);
 rightFront.setPosition(0, degrees);
 rightBack.setPosition(0, degrees);
 leftMid.setPosition(0, degrees);
 rightMid.setPosition(0, degrees);
 int rspeed = 0;
 int lspeed = 0;

 while (true) {
 double measureddegrees = (leftFront.position(degrees) + rightFront.position(degrees)) / 2;
 error = targetdegrees - measureddegrees;

/*
 if (fabs(measureddegrees - prevdegrees) < 3) {
 count++; // add to count
 } else { // if not being stalled
 count = 0;
 }

 if (count > 10) { // exit when stuck for 200 ms
 leftFront.stop();
 leftBack.stop();
 rightFront.stop();
 rightBack.stop();
 leftMid.stop();
 rightMid.stop();
 Controller1.Screen.clearScreen();
 Controller1.Screen.setCursor(1, 1);
 Controller1.Screen.print("stalled");
 wait(3000,msec);
 return;
 }
*/
 // Controller1.Screen.clearScreen();
 // Controller1.Screen.setCursor(1, 1);
 // Controller1.Screen.print(measureddegrees);
 prevdegrees = measureddegrees;

 // Integral windup
 if (fabs(error) < targetdegrees/10*3 && fabs(integral) < 300) {//fabs(error) < 300
 integral += error;
 }
 if (fabs(error) < 30 /* || fl.current(amp) > 3.0*/) { // exit condition
 leftFront.stop();
 leftBack.stop();
 rightFront.stop();
 rightBack.stop();
 leftMid.stop();
 rightMid.stop();

 /*
 Controller1.Screen.clearScreen();
 Controller1.Screen.setCursor(1, 1);
 Controller1.Screen.print(error);
 wait(3000,msec);
 */
 return;
 }

 speed = error * kp + integral * ki + (error - lasterror) * kd; // motor speed

 leftFront.spin(forward, speed, rpm);
 leftBack.spin(forward, speed, rpm);
 rightFront.spin(forward, speed, rpm);
 rightBack.spin(forward, speed, rpm);
 leftMid.spin(forward, speed, rpm);
 rightMid.spin(forward, speed, rpm);
 lasterror = error;
 wait(20, msec);
 }
}












void arcadeDrive(){
  float throttle = deadband(controller(primary).Axis3.value(), 1);
  float turn = deadband(controller(primary).Axis1.value(), 12);
  leftFront.spin(fwd, to_volt(throttle+turn), volt);
  leftMid.spin(fwd, to_volt(throttle+turn), volt);
  leftBack.spin(fwd, to_volt(throttle+turn), volt);
  rightFront.spin(fwd, to_volt(throttle-turn), volt);
  rightMid.spin(fwd, to_volt(throttle-turn), volt);
  rightBack.spin(fwd, to_volt(throttle-turn), volt);
}










// Drivetrain PID Function
void IntakeCode(double targetdegrees, double kp, double ki, double kd) {
 double error = targetdegrees;
 double integral = 0;
 double lasterror = error;
 double speed;
 double prevdegrees = Upper.position(degrees);

 double count = 0;

 Upper.setPosition(0, degrees);
 
 int rspeed = 0;
 int lspeed = 0;

 while (true) {
 double measureddegrees = (Upper.position(degrees) + Upper.position(degrees)) / 2;
 error = targetdegrees - measureddegrees;

/*
 if (fabs(measureddegrees - prevdegrees) < 3) {
 count++; // add to count
 } else { // if not being stalled
 count = 0;
 }

 if (count > 10) { // exit when stuck for 200 ms
 leftFront.stop();
 leftBack.stop();
 rightFront.stop();
 rightBack.stop();
 leftMid.stop();
 rightMid.stop();
 Controller1.Screen.clearScreen();
 Controller1.Screen.setCursor(1, 1);
 Controller1.Screen.print("stalled");
 wait(3000,msec);
 return;
 }
*/
 // Controller1.Screen.clearScreen();
 // Controller1.Screen.setCursor(1, 1);
 // Controller1.Screen.print(measureddegrees);
 prevdegrees = measureddegrees;

 // Integral windup
 if (fabs(error) < targetdegrees/10*3 && fabs(integral) < 300) {//fabs(error) < 300
 integral += error;
 }
 if (fabs(error) < 30 /* || fl.current(amp) > 3.0*/) { // exit condition
 Upper.stop();

 Controller1.Screen.clearScreen();
 Controller1.Screen.setCursor(1, 1);
 Controller1.Screen.print(error);
 wait(3000,msec);
 return;
 }

 speed = error * kp + integral * ki + (error - lasterror) * kd; // motor speed

 Upper.spin(forward, speed, rpm);
 lasterror = error;
 wait(20, msec);
 }
}



void ThrowAwayBlue() {

color blue = color((0, 0, 255));

 if (opticalsensor.color() == blue) {
Controller1.rumble("...");
sorter.set(true);
wait(1000,msec);
sorter.set(false);
//Intake.stop(hold);

}
}




void ThrowAwayRed() {
// Controller1.rumble("...");

opticalsensor.setLightPower(100,percent);

 if (opticalsensor.color() == red) {
Controller1.rumble("...");
sorter.set(true);
wait(1000,msec);
sorter.set(false);
//Intake.stop(hold);

}
}


void driveForward(double targetPosition,double speed){
  // Reset the motor positions
    leftFront.resetPosition();
    leftMid.resetPosition();
    leftBack.resetPosition();
    rightFront.resetPosition();
    rightMid.resetPosition();
    rightBack.resetPosition();

            leftFront.stop(brake);
            leftMid.stop(brake);
            leftBack.stop(brake);
            rightFront.stop(brake);
            rightMid.stop(brake);
            rightBack.stop(brake);
    
    double kp = 0.7;  
    //change KP to 1 for solo awp
    //change KP to 0.7 for normal autos

    double setpoint = (targetPosition*15); 
    double error = 0.0;
    double output = 0.0;

    double tolerance = 5.0; 
    double speedLimit = (speed/200); //max speed

    while (true) {
        // Calculate the error (setpoint - current position)
        double currentPosition = (leftFront.position(degrees) + rightFront.position(degrees)) / 2; //average of dt motor positions
        error = setpoint - currentPosition;

        // Calculate P output
        output = kp * error; // P output

        // Limit output to be within -100% to 100%
        if (output > 100.0) {
            output = 100.0;
        } else if (output < -100.0) {
            output = -100.0;
        }

        // Apply the speed limit
        output *= speedLimit; // uses speed limit to stay in speed

        // Apply the output to the motors in percent
        leftFront.spin(forward, output, percent);
        leftMid.spin(forward, output, percent);
        leftBack.spin(forward, output, percent);
        rightFront.spin(forward, output, percent);
        rightMid.spin(forward, output, percent);
        rightBack.spin(forward, output, percent);
        
        // checks to see if position is less than tolerance
        if (fabs(error) < tolerance) {
            // Stop all motors
            leftFront.stop();
            leftMid.stop();
            leftBack.stop(brake);
            rightFront.stop();
            rightMid.stop();
            rightBack.stop(brake);
            vex::task::sleep(100); // wait 1/10 of a second
            break; // Exit the loop
        }

        // Wait a short time before the next loop iteration
        vex::task::sleep(20); //waits to save resources
    }
}


/*

void driveForward(double distance, double speed){
   double realspeed = (speed/100);
   Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(0,0); 
   Controller1.Screen.print(realspeed);
    
    double amount = (distance*15);

if (amount>0){
      //Controller1.rumble("...");
    driveForward(1);

    driveForward(amount);
}
else if (amount<0){
    driveForward(-1);

    driveForward(amount);
}


}

*/

vex::task ColorSortRed() {
 Controller1.rumble("...");
 wait(50,msec);
  opticalsensor.setLightPower(100,percent);

 while(1){

opticalsensor.setLightPower(100,percent);

 if (opticalsensor.color() == red) {
Controller1.rumble("...");
sorter.set(true);
wait(1000,msec);
sorter.set(false);
//Intake.stop(hold);

}

}

}




vex::task ColorSortBlue() {


 while(1){
 wait(10,msec);

 opticalsensor.setLightPower(100,percent);
color blue = color((0, 0, 255));

 if (opticalsensor.color() == blue) {
Controller1.rumble("...");
sorter.set(true);
wait(1000,msec);
sorter.set(false);

}
}
}



vex::task positionTask() {


 while(1){
 wait(20,msec);

 if(Controller1.ButtonRight.pressing()){
 WallStakes.setVelocity(10, percent);
 while (rotationSensor.angle(degrees)<227){
 Controller1.rumble("...");
 WallStakes.spin(reverse);

 }

  WallStakes.stop(hold);
    
 }

}
}


void UserRedSort(){
 if (opticalsensor.color() == red) {
 Controller1.rumble("...");
wait(100,msec);
Upper.setVelocity(5,percent);
wait(2000,msec);
Upper.setVelocity(100,percent);
}
}



void UserBlueSort(){
 // Controller1.rumble("...");
if (opticalsensor.color() == cyan) {
 Controller1.rumble("...");
wait(50,msec);
Upper.setVelocity(1,percent);
wait(2500,msec);
Upper.setVelocity(100,percent);
}
}



















void TurnClockwise(double target){
 Inertial.setRotation(0,degrees);
 rightFront.setVelocity(100, percent);
 rightMid.setVelocity(100, percent);
 leftFront.setVelocity(100, percent);
 leftMid.setVelocity(100, percent);
 leftBack.setVelocity(100, percent);
 rightBack.setVelocity(100, percent);
 while (true) {
 if(Inertial.rotation(degrees) < target){
 leftFront.spin(forward);
 leftMid.spin(forward);
 leftBack.spin(forward);
 rightFront.spin(reverse); 
 rightMid.spin(reverse);
 rightBack.spin(reverse);
 }
 else if (Inertial.rotation(degrees) > target){
 leftFront.stop();
 leftMid.stop();
 leftBack.stop();
 rightFront.stop();
 rightMid.stop();
 rightBack.stop(); 
 return;
 }
 }
 }







void MogoUp(){
MOGO.set(true);
MOGO.set(true);
 }



void MogoDown(){
MOGO.set(false);
MOGO.set(false);
 }




int current_auton_selection = 0;
bool auto_started = false; 

void pre_auton(void) {
 vexcodeInit();



rotationSensor.setPosition(0, degrees);






 Controller1.rumble("...");
Inertial.calibrate();
 

while (Inertial.isCalibrating() == true){
 Controller1.rumble("...");
 wait(100,msec);
}

current_auton_selection = 0;

default_constants();
 while(auto_started == false){ 
 //Brain.Screen.clearScreen(); 
 switch(current_auton_selection){ 
 
case 0:

 //Brain.Screen.printAt(50, 50, "SOLO AWP RED");
 SoloAwpRedPicture();
 
 // Brain.Screen.printAt(50, 50, "Elims Scoring Red Right");
 break;




 case 1:


 //Brain.Screen.printAt(50, 50, "Elims Scoring Red Right");

 ElimsRedRightPicture();
  wait(1000,msec);

 case 2:

 //Brain.Screen.printAt(50, 50, "Elims Scoring Red Left");

ElimsRedLeftPicture();

 // Brain.Screen.printAt(50, 50, "SOLO AWP RED");
 break;

 case 3:

ElimsBlueRightPicture();
 //Brain.Screen.printAt(50, 50, "Elims Scoring Blue Right");

 // Brain.Screen.printAt(50, 50, "Elims Scoring Red Left");
 break;

 case 4:

ElimsBlueLeftPicture();

 //Brain.Screen.printAt(50, 50, "Elims Scoring Blue Left");


 // Brain.Screen.printAt(50, 50, "Elims Scoring Blue Right");
 break;

 case 5:

SoloAwpBluePicture();
// Brain.Screen.printAt(50, 50, "SOLO Awp Blue");
 break;

 case 6:

QualsRedRightPicture();
 //Brain.Screen.printAt(50, 50, "Bar Touch Red Right");
 break;

 case 7:

 

 Brain.Screen.printAt(50, 50, "Quals Red Left");
 break;

 case 8:


 Brain.Screen.printAt(50, 50, "Quals Blue Left");
 break;

 case 9:


Brain.Screen.printAt(50, 50, "Quals Blue Right");
 break;

 case 10:



 Brain.Screen.printAt(50, 50, "Skills");
 break;

 case 11:



 Brain.Screen.printAt(50, 50, "Skills Max");
 break; 

 

 }
 if(Brain.Screen.pressing()){
 
 while(Brain.Screen.pressing()) {}
 Brain.Screen.clearScreen();
 current_auton_selection ++;
 } else if (current_auton_selection == 11){
 current_auton_selection = 0;
 }
 task::sleep(10);
 }
}



void autonomous(void) {
 auto_started = true;
 switch(current_auton_selection){ 
 case 0: //SOLO AWP RED


WallStakes.spin(forward,20,percent);
Puller.set(false);
mogo.set(false);
MOGO.set(false);

driveForward(-0.1,100);

//driveForward(-10,100);

driveForward(-20,60);

WallStakes.stop(hold);

mogo.set(true);
MOGO.set(true);
//wait(500,msec);

driveForward(-4,100);


chassis.turn_to_angle(90);


Intake.spin(forward,100,percent);

driveForward(0.1,100);

driveForward(20,60);

wait(500,msec);

chassis.turn_to_angle(300);

mogo.set(false);
MOGO.set(false);

driveForward(0.1,100);

driveForward(50,100);

chassis.turn_to_angle(45);

driveForward(-0.1,100);

driveForward(-35,60);

mogo.set(true);
MOGO.set(true);

wait(500,msec);

chassis.turn_to_angle(280);

driveForward(0.1,100);

driveForward(25,100);

///
 break; 

 case 1: //Elims Red Right

WallStakes.setVelocity(100,percent);

driveForward(30,100);

chassis.turn_to_angle(333);

driveForward(0.1,100);

driveForward(6,100);

WallStakes.spin(forward);
wait(1200,msec);

WallStakes.spin(reverse,10,percent);

chassis.turn_to_angle(210);

WallStakes.stop(hold);

Intake.spin(forward,100,percent);


driveForward(0.1,100);

driveForward(20,100);

Intake.stop();

chassis.turn_to_angle(115);

Intake.setVelocity(100,percent);

driveForward(-0.1,100);

driveForward(-15,100);






 break;

 case 2: //Elims Red Left

 //driveForward(10,100);

Puller.set(false);
mogo.set(false);
MOGO.set(false);

driveForward(-0.1,100);

//driveForward(-10,100);

driveForward(-20,60);


mogo.set(true);
MOGO.set(true);
//wait(500,msec);

driveForward(-5,100);


chassis.turn_to_angle(130);


Intake.spin(forward,100,percent);




driveForward(0.1,100); //reset

driveForward(16,100);
wait(500,msec);




driveForward(-5,100);



chassis.turn_to_angle(115);


driveForward(0.1,100); //reset

driveForward(12,100);


wait(1000,msec);



driveForward(-7,100);


chassis.turn_to_angle(50);



driveForward(0.1,100); //reset

driveForward(14,100);

driveForward(-6,100);

wait(2000,msec);

chassis.turn_to_angle(307);

Intake.stop(hold);

driveForward(0.1,100); //reset

driveForward(60,100);


/*
Intake.spin(forward,100,percent);



Puller.set(true);

driveForward(0.1,100); //reset

driveForward(30,100);


wait(500,msec);
//chassis.turn_to_angle(180);

Puller.set(false);
*/


break;


case 3: //Elims Blue Right


WallStakes.spin(forward,20,percent);
Puller.set(false);
mogo.set(false);
MOGO.set(false);

driveForward(-0.1,100);

//driveForward(-10,100);

driveForward(-20,60);

WallStakes.stop(hold);

mogo.set(true);
MOGO.set(true);
//wait(500,msec);

driveForward(-5,100);


chassis.turn_to_angle(230);


Intake.spin(forward,100,percent);




driveForward(0.1,100); //reset

driveForward(16,100);
wait(500,msec);




driveForward(-5,100);



chassis.turn_to_angle(245);

driveForward(0.1,100); //reset

driveForward(12,100);


wait(1000,msec);



driveForward(-7,100);


chassis.turn_to_angle(310);



driveForward(0.1,100); //reset



driveForward(14,100);

driveForward(-6,100);

wait(2000,msec);


chassis.turn_to_angle(53);

driveForward(0.1,100); //reset

driveForward(60,100);


/*
Puller.set(true);

driveForward(0.1,100); //reset

driveForward(48,100);


chassis.turn_to_angle(180);

driveForward(0.1,100); //reset

driveForward(20,50);


*/


break;
 case 4: // Elims Auton Blue Left







 break;


 case 5: // Elims Auton Blue


 break;


 case 6: // Quals Red Right

   WallStakes.spinFor(50,degrees,false);
   driveForward(30,100);
  chassis.drive_distance(5,325);
  chassis.turn_to_angle(45);



 break;

 case 7: // quals red left

Puller.set(false);
mogo.set(false);
MOGO.set(false);
Intake.setVelocity(100,percent);
WallStakes.setVelocity(100,percent);

chassis.turn_to_angle(45);

WallStakes.spin(forward);
wait(1000,msec);
WallStakes.stop(hold);


driveForward(-0.1,100);
driveForward(-10,100);

chassis.turn_to_angle(80);

driveForward(-0.1,100);
driveForward(-23,60);

mogo.set(true);
MOGO.set(true);

wait(500,msec);

Intake.spin(reverse);


chassis.turn_to_angle(180);


Intake.spin(forward,100,percent);

driveForward(0.1,100);
driveForward(28,100);

chassis.turn_to_angle(267);

driveForward(0.1,100);
driveForward(12,100);
wait(1000,msec);


driveForward(-0.1,100);
driveForward(-10,100);

chassis.turn_to_angle(0);


driveForward(0.1,100);
driveForward(50,80);



 break;

 case 8: 





 break;

 case 9: // Quals blue right


Puller.set(false);
mogo.set(false);
MOGO.set(false);
Intake.setVelocity(100,percent);
WallStakes.setVelocity(100,percent);

chassis.turn_to_angle(315);

WallStakes.spin(forward);
wait(1000,msec);
WallStakes.stop(hold);


driveForward(-0.1,100);
driveForward(-10,100);

chassis.turn_to_angle(280);

driveForward(-0.1,100);
driveForward(-23,60);

mogo.set(true);
MOGO.set(true);
wait(500,msec);
Intake.spin(reverse);


chassis.turn_to_angle(180);


Intake.spin(forward,100,percent);

driveForward(0.1,100);
driveForward(28,100);

chassis.turn_to_angle(90);

driveForward(0.1,100);
driveForward(12,100);
wait(1000,msec);

driveForward(-0.1,100);
driveForward(-10,100);

chassis.turn_to_angle(0);


driveForward(0.1,100);
driveForward(50,100);




 break;

 case 10: // Skills



Intake.setVelocity(100,percent);

Intake.spin(forward);
wait(500,msec);

Intake.stop();

driveForward(7,100);

chassis.turn_to_angle(270);

driveForward(-0.1,100); //reset

driveForward(-10,100);
driveForward(-5,40);

mogo.set(true);
MOGO.set(true);

Intake.spin(reverse);

driveForward(-3,100);

chassis.turn_to_angle(0);

Intake.spin(forward,100,percent);

driveForward(0.1,100); //reset

driveForward(20,100);

driveForward(-10,100);

chassis.turn_to_angle(55);



driveForward(0.1,100); //reset

driveForward(30,100);


driveForward(-5,100);

chassis.turn_to_angle(27);

driveForward(0.1,100); //reset

driveForward(30,100);
wait(500,msec);


driveForward(-0.1,100); //reset

driveForward(-18,100);

chassis.turn_to_angle(182);

driveForward(0.1,100); //reset

driveForward(30,100);

wait(500,msec);

driveForward(-0.1,100); //reset

driveForward(-10,100);

chassis.turn_to_angle(90);



/*

driveForward(0.1,100); //reset

driveForward(20,100);

wait(500,msec);

driveForward(-0.1,100); //reset

driveForward(-7,100);

chassis.turn_to_angle(180);

driveForward(0.1,100); //reset

driveForward(35,100);
wait(500,msec);

driveForward(-25,100);

chassis.turn_to_angle(145);

driveForward(0.1,100); //reset

driveForward(13,100);

chassis.turn_to_angle(335);

mogo.set(false);
MOGO.set(false);

driveForward(-0.1,100); //reset

driveForward(-15,50);

driveForward(0.1,100); //reset

driveForward(10,100);


/*



chassis.turn_to_angle(90);


Intake.stop();


driveForward(15,50);


WallStakes.spin(forward);
wait(1000,msec);
WallStakes.spin(reverse);

driveForward(-10,100);
WallStakes.stop();

chassis.turn_to_angle(180);

Intake.spin(forward);

driveForward(50,30);

chassis.turn_to_angle(75);

driveForward(10,100);


chassis.turn_to_angle(325);


mogo.set(false);
MOGO.set(false);

driveForward(-20,50);

driveForward(12,100);

chassis.turn_to_angle(90);

driveForward(-60,100);

mogo.set(true);
MOGO.set(true);

chassis.turn_to_angle(0);

driveForward(24,100);



*/



 break;

 case 11: // Skills Max

 break;


 }
}


int down = false;







void simpleDrive(){

 
 int forwardAmount = Controller1.Axis1.position();
 int turnAmount = Controller1.Axis3.position();
 rightFront.setVelocity(100, percent);
 rightMid.setVelocity(100, percent);
 rightBack.setVelocity(100, percent);

 leftFront.setVelocity(100, percent);
 leftMid.setVelocity(100, percent);
 leftBack.setVelocity(100, percent);

 rightFront.spin(reverse,forwardAmount - turnAmount, percent);
 leftFront.spin(forward, forwardAmount + turnAmount, percent);
 leftMid.spin(forward, forwardAmount + turnAmount, percent);
 leftBack.spin(forward, forwardAmount + turnAmount, percent);
 rightMid.spin(reverse,forwardAmount - turnAmount, percent);
 rightBack.spin(reverse,forwardAmount - turnAmount, percent);
}



void DistanceCode(){


while (detected.objectDistance(inches)>3){

  rightFront.spin(reverse);
  leftFront.spin(reverse);

}
rightFront.stop(hold);
leftFront.stop(hold);

}






void DoinkerCode(){
 if(Controller1.ButtonUp.pressing()){
Doinker.set(true);
Controller1.rumble("...");
 
 }
 else if(Controller1.ButtonDown.pressing()){
Doinker.set(false);



 }
 else{
//Nothing happens
 }
}




void IntakeUpCode(){
 if(Controller1.ButtonY.pressing()){
Puller.set(true);
 
 }
 else if(Controller1.ButtonB.pressing()){
Puller.set(false);
 }
 else{
//Nothing happens
 }
}



void MogoCode(){
 if(Controller1.ButtonX.pressing()){
MOGO.set(true);
mogo.set(true);
 
 }
 else if(Controller1.ButtonA.pressing()){
MOGO.set(false);
mogo.set(false);
 }
 else{
//Nothing happens
 }
}


double speed = (rotationSensor.velocity(rpm));




void positionCode(){


 if(Controller1.ButtonRight.pressing()){

  if (rotationSensor.velocity(rpm) < 1){

    WallStakes.stop(hold);

  }

 WallStakes.setVelocity(23, percent);
 while (rotationSensor.angle(degrees)<217){
 Controller1.rumble("...");
 WallStakes.spin(reverse);

 }

  WallStakes.stop(hold);
    
 }
}





void descoreCode(){


 if(Controller1.ButtonLeft.pressing()){
 WallStakes.setVelocity(10, percent);
 while (rotationSensor.angle(degrees)>100){
 Controller1.rumble("...");
 WallStakes.spin(forward);

 }

  WallStakes.stop(hold);
    
 }
}











void SlowCode(){

 Intake.setVelocity(100, percent);
 Upper.setVelocity(100, percent);
 if(Controller1.ButtonUp.pressing()){
 Intake.setVelocity(50, percent);
 Upper.setVelocity(50, percent);
 
 Intake.spin(forward);
 Upper.spin(forward);
 //FlywheelPID(10000,10,0,0);
 
 }
 else if(Controller1.ButtonDown.pressing()){


 //FlywheelPID(-10000,10,0,0);

 }
 else{

 
 }
}


void intakeCode(){
opticalsensor.setLightPower(100,percent);
 Intake.setVelocity(100, percent);
  if(Controller1.ButtonR1.pressing()){

 Intake.spin(forward);

 }
 else if(Controller1.ButtonR2.pressing()){

 Intake.spin(reverse);

 }
 else{

 Intake.stop();


 }

}



void WallStakesCode(){
opticalsensor.setLightPower(100,percent);
 WallStakes.setVelocity(100, percent);
  if(Controller1.ButtonL1.pressing()){

 WallStakes.spin(forward);

 }
 else if(Controller1.ButtonL2.pressing()){

 WallStakes.spin(reverse);

 }
 else if(Controller1.ButtonUp.pressing()){
 WallStakes.setVelocity(5, percent);
 WallStakes.spin(forward);

 }
 else if(Controller1.ButtonDown.pressing()){
 WallStakes.setVelocity(5, percent);
 WallStakes.spin(reverse);

 }
 else{

 WallStakes.stop(hold);


 }

}








void mogoOpen(){
MOGO.set(true);
mogo.set(false);


}












void TempCode(){

 if (rightMid.temperature(temperatureUnits::fahrenheit) > 130){
 Controller1.rumble("...");
 Controller1.Screen.print("STOP DRIVING!!!");
 }
 else if(rightMid.temperature(temperatureUnits::fahrenheit) < 120){
 
 }
 else{
 
 }
}
















/*---------------------------------------------------------------------------*/
/* */
/* User Control Task */
/* */
/* This task is used to control your robot during the user control phase of */
/* a VEX Competition. */
/* */
/* You must modify the code to add your own robot specific commands here. */
/*---------------------------------------------------------------------------*/


void usercontrol(void) {
 // User control code here, inside the loop
 //positionTask();

 while (1) {
 intakeCode(); 
 //TestCode();

 //SlowCode();
positionCode();

// ThrowAwayRed();
WallStakesCode();


 //simpleDrive();
 //UserBlueSort();
 //UserBlueSort();
IntakeUpCode();

descoreCode();

//positionCode();


 //redirectCode();
//ThrowAwayBlue();
 //DoinkerCode();



 MogoCode();
 //TempCode();
 //intakeCode();
 // drawLogo();
 chassis.control_arcade();
 wait(20, msec); // Sleep the task for a short amount of time to
 // prevent wasted resources.
 }
}

//jj
// Main will set up the competition functions and callbacks.
//

int main() {
 // Set up callbacks for autonomous and driver control periods.

 Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
    pre_auton();
 // Run the pre-autonomous function.
ColorSortBlue();
//ColorSortRed();
Controller1.Screen.clearScreen();
Controller1.Screen.setCursor(0,0);
Controller1.Screen.print("ThrowingAwayBlue");
 // Prevent main from exiting with an infinite loop.
 while (true) {
 wait(100, msec);
 }
}