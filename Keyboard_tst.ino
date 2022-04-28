#include <Keyboard.h>
#include <KeyboardLayout.h>
#include <Mouse.h>
const int myScreenWidth   = 1920;       // screen width
const int myScreenHeight  =  1080;       // screen height
volatile unsigned long tickCount;
#define TicksPerRotaion 22
#define rpmThresh 5
unsigned long currentTime;
unsigned long prevTime;
int tmpTickCount;
int rotationChange;


void setup() {
  // make pin 2 an input and turn on the
  // pullup resistor so it goes high unless
  // connected to ground:
  attachInterrupt(digitalPinToInterrupt(0), rotationCount , FALLING);
  tickCount = 0;
  currentTime = 0;
  prevTime = 0;
  tmpTickCount = 0;


  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  // initialize control over the keyboard:
  Keyboard.begin();
  Mouse.begin();
}

void loop() {
  unsigned long currentTime = micros() - prevTime;

  if (currentTime > 100000) {
    prevTime = micros();
    rotationChange = tickCount - tmpTickCount;
    tmpTickCount = tickCount;
  }
  if (rotationChange > rpmThresh) {
    if (digitalRead(2) == HIGH) {
      Mouse.press();
      for (int i = 0; i < 10; i++) {
        Mouse.move(-20, 0); //left
        delay(15);
      }
      Mouse.release();
      delay(300);
      moveMouse2screenCenter();
    }
    if (digitalRead(3) == HIGH) {
      Mouse.press();
      for (int i = 0; i < 10; i++) {
        Mouse.move(0, 20); //down
        delay(15);
      }
      Mouse.release();
      delay(300);
      moveMouse2screenCenter();
    }
    if (digitalRead(4) == HIGH) {
      Mouse.press();
      for (int i = 0; i < 10; i++) {
        Mouse.move(0, -20); //up
        delay(15);
      }
      Mouse.release();
      delay(300);
      moveMouse2screenCenter();
    }
    if (digitalRead(5) == HIGH) {
      Mouse.press();
      for (int i = 0; i < 10; i++) {
        Mouse.move(20, 0); //right
        delay(15);
      }
      Mouse.release();
      delay(300);
      moveMouse2screenCenter();
    }
  }
}

void moveMouse2screenCenter() {
  int moveXtimes = (myScreenWidth / 127 / 2);
  int moveYtimes = (myScreenHeight / 127 / 2);
  signed char lastMoveX = (myScreenWidth / 2) - (moveXtimes * 127);
  signed char lastMoveY = (myScreenHeight / 2) - (moveYtimes * 127);
  moveMouse2UpperLeftCorner();
  for (int i = 0; i < moveXtimes; i++) {
    Mouse.move(127, 0, 0);
  }
  Mouse.move(lastMoveX, 0, 0);
  for (int i = 0; i < moveYtimes; i++) {
    Mouse.move(0, 127, 0);
  }
  Mouse.move(0, lastMoveY, 0);
}

void moveMouse2UpperLeftCorner() {
  int moveXtimes = (myScreenWidth / 127) + 1;
  int moveYtimes = (myScreenHeight / 127) + 1;
  for (int i = 0; i < moveXtimes; i++) {
    Mouse.move(-127, 0, 0);
  }
  for (int i = 0; i < moveYtimes; i++) {
    Mouse.move(0, -127, 0);
  }
}

void rotationCount()
{
  tickCount++;
}
