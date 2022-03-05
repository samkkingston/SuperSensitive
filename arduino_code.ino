/*
  Super Sensitive
  Sam Kingston
  DIGF-3010-001 Advanced Wearable Electronics
  OCAD University
  Created on 2022-03-04

  Servo Library Used: https://github.com/Locoduino/SlowMotionServo
*/


//INCLUDE LIBRARIES
#include <Adafruit_CircuitPlayground.h>
#include <Servo.h>
#include <SlowMotionServo.h> //This library takes in speed as a parameter for servo movement allowing more tuning control.
#include <Wire.h>
#include <SPI.h> //used to control multiple servo movements simultaneously, not used in this sketch.


SMSSmooth myServo; //declaring servo as SMSSmooth with the SlowMotionServo library makes the servo movement ramp into and down from maximum speed using a sine wave. gives softer movement.

//DECLARE VARIABLES
float target = 0.0;
int pos = 0;
int frontPin = A6;
int backPin = A5;
int frontCheck;
int backCheck;

void setup() {

  CircuitPlayground.begin();

  //these paramaters are needed for SlowMotionServo and are not necessary for the regular servo library
  myServo.setInitialPosition(target); //this variable can be changed to max and min var (seen below) to set angle targets
  myServo.setMinMax(700, 2000); //max and min values
  myServo.setSpeed(2.0); //float can be changed to speed up or down movement

  myServo.setPin(A7);//servo data pin connected to A7. Must use PWM pin.
}


void loop() {

  frontCheck = (analogRead(frontPin)); //check the value of the front photoresistor
  backCheck = (analogRead(backPin)); //check the value of the back photoresistor


  if (frontCheck > backCheck) { //if it's brighter in front of the user...
    target = 1.0; //change target to 1.0. Target is triggered as a float where 0.0 == minimum value declared in setup and 1.0 ==maximum value
  }


  else {
    target = 0.0; //change target to 0.0 (minimum value).
  }

  myServo.goTo(target); //move the servo arm to the target set by conditions above
  SlowMotionServo::update(); //update servo position

  delay(1000); //makes the arduino check photoresistor values once a second. While using closed-loop delays is not ideal or recommended, it works with such a simple sketch.
}
