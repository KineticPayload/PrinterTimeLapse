/*******************************************
Created by Colin Smith
October 7, 2019
 ********************************************/
// TODO
// Add debounce to the limit switch to prevent extra photos from being taken

#include <multiCameraIrControl.h>

const int cameraIrPin = 13;
const int limitSwitchPin = 2;
Canon Eos7D(cameraIrPin);

int photoNum = 0;
unsigned long last_millis = 0;
unsigned long this_millis = 0;

bool lastSwitch = HIGH;
bool currentSwitch = HIGH;

void setup(){
  Serial.begin(9600);
  //connect the limit switch directly between limitSwitchPin and GND
  pinMode(limitSwitchPin, INPUT_PULLUP); 
}

void loop(){
  currentSwitch = digitalRead(limitSwitchPin);
  if (currentSwitch < lastSwitch) { // if we see a falling edge
    this_millis = millis();
    if (this_millis - last_millis > 200){ // make sure it's not a bounce
      Eos7D.shotNow(); // take a photo
      photoNum += 1;      
    }
    last_millis = this_millis;
  }
  Serial.print("Photo Number: ");
  Serial.println(photoNum);
  lastSwitch = currentSwitch;
}
