/*******************************************
Created by Colin Smith
October 7, 2019
 ********************************************/

#include <multiCameraIrControl.h>

const int cameraIrPin = 13;
const int limitSwitchPin = 2;
volatile int photoNum = 0;
Canon Eos7D(cameraIrPin);

void setup(){
  //connect the limit switch directly between limitSwitchPin and GND
  pinMode(limitSwitchPin, INPUT_PULLUP);
  // call the function whenever the switch is triggered
  attachInterrupt(limitSwitchPin, limitFun, FALLING);
}

void loop(){
  delay(1000); // slow it down so it doesn't use much power
  Serial.print("Photo Number: ");
  Serial.println(photoNum);
}

void limitFun(){
  // when limit switch is triggered, take a photo and increment the photo count
  Eos7D.shotNow();
  photoNum += 1;
}
