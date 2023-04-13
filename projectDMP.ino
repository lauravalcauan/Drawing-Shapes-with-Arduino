 #include <Stepper.h>
#include <Servo.h>
#include <math.h>
#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial SerialS(10, 11); // RX, TX

// Horizontal stepper
#define stepper1DirPin 2
#define stepper1StepPin 5

float milliStepsX = 300.0;
float milliStepsY = 300.0;

int currentX = 0;
int currentY = 0;

// Vertical stepper
#define stepper2DirPin 6
#define stepper2StepPin 3

#define DriverA4988 1

#define stepsPerRevolution 200 // from technical specifications

//Define the stepper motors and the pins that will use
Servo gripperServo; 

// create Servo object to control a servo
Stepper stepper1(stepsPerRevolution, stepper1DirPin, stepper1StepPin);
Stepper stepper2(stepsPerRevolution, stepper2DirPin, stepper2StepPin);


void drawLine(float x1, float y1) {
  
  //  Convert coordinates to steps
  x1 = (int)(x1*milliStepsX);
  y1 = (int)(y1*milliStepsY);
  float x0 = currentX;
  float y0 = currentY;

  //  Let's find out the change for the coordinates
  long dx = abs(x1-x0);
  long dy = abs(y1-y0);
  int sx = x0<x1 ? 1 : -1;
  int sy = y0<y1 ? 1 : -1;

  long i;
  long over = 0;

  if (dx > dy) {
    for (i=0; i<dx; ++i) {
      stepper1.step(sx);
      over+=dy;
      if (over>=dx) {
        over-=dx;
        stepper2.step(sy);
      }
      delay(5);
    }
  }
  else {
    for (i=0; i<dy; ++i) {
      stepper2.step(sy);
      over+=dx;
      if (over>=dy) {
        over-=dy;
        stepper1.step(sx);
      }
      delay(5);
    }    
  }

  
  delay(30);
  
  currentX = x1;
  currentY = y1;
}


void setup() {

  // Serial.begin(115200);

  Serial.begin(9600);

  // wait for the serial connection to be ready
  while(!SerialS);
  
  stepper1.setSpeed(50);
  stepper2.setSpeed(50);

  gripperServo.write(0); 

}

void loop() {
  // Create a rectangle of 200x400 
    //  rectangleSteps(200, 400);

  gripperServo.attach(8);    

  // Drawing a house

  //    currentX = 0;
  //    currentY = 0;

  //    drawline(0,0);
    drawLine(0,-2);
    drawLine(4,-2);
    drawLine(4,0);
    drawLine(0,0);
    drawLine(2,2);
    drawLine(4,0);
    drawLine(0,0);
  

  delay(1000);

  gripperServo.detach();
}