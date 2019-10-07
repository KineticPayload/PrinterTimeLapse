/*******************************************
Created by Colin Smith
October 7, 2019
 ********************************************/
// TODO
// Add debounce to the limit switch to prevent extra photos from being taken

#include <multiCameraIrControl.h>

const int cameraIrPin = 13;
const int limitSwitchPin = 2;
volatile int photoNum = 0;
unsigned long last_interrupt_time = 0;
Canon Eos7D(cameraIrPin);

void setup(){
  Serial.begin(9600);
  //connect the limit switch directly between limitSwitchPin and GND
  pinMode(limitSwitchPin, INPUT_PULLUP);
  // call the function whenever the switch is triggered
  attachInterrupt(digitalPinToInterrupt(limitSwitchPin), limitFun, FALLING);
//  pinMode(cameraIrPin, OUTPUT);
}

void loop(){
  delay(1000); // slow it down so it doesn't use much power
  digitalWrite(cameraIrPin, LOW);
  Serial.print("Photo Number: ");
  Serial.println(photoNum);
}

void limitFun(){
  // when limit switch is triggered, take a photo and increment the photo count
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 200){
    Eos7D.shotNow();
//    digitalWrite(cameraIrPin, HIGH);
    photoNum += 1;
  }
  last_interrupt_time = interrupt_time;
}
