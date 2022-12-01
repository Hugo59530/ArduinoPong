#include <M5Stack.h>

// Pins

int vryOne = 26;
int vrxOne = 25;
int msOne = 3;
int vryTwo = 36;
int vrxTwo = 35;
int msTwo = 1;

// Joystick x / y

int xJoystickOne = 0;
int yJoystickOne = 0;
int xJoystickTwo = 0;
int yJoystickTwo = 0;

// M5 screen Max values

int screenMaxX = 320;
int screenMaxY = 240;

// Rectangles coordonates

int playerBarWidth = 70;
int playerBarHeight = 15;

int xRectOne = screenMaxX / 2 - playerBarWidth;
int yRectOne = 10;

int xRectTwo = screenMaxX / 2 - playerBarWidth;
int yRectTwo = screenMaxY - 10 - playerBarHeight;

void setup()
{
  M5.begin();       // Init M5Core. Initialize M5Core
  M5.Power.begin(); // Init Power module. Initialize the power module

  pinMode(msOne, INPUT);
  pinMode(vryOne, INPUT);
  pinMode(vrxOne, INPUT);
  pinMode(msTwo, INPUT);
  pinMode(vryTwo, INPUT);
  pinMode(vrxTwo, INPUT);
  M5.Lcd.setTextSize(50);
}

void clearSquares(int xRectOne, int yRectOne, int xRectTwo, int yRectTwo)
{
  M5.Lcd.fillRect(xRectOne, yRectOne, playerBarWidth, playerBarHeight, 0);
  M5.Lcd.fillRect(xRectTwo, yRectTwo, playerBarWidth, playerBarHeight, 0);
}

void moveRectangles(int xJoystickOne, int xJoystickTwo, int xRectOne, int yRectOne, int xRectTwo, int yRectTwo, int* xRectOnePointer, int* xRectTwoPointer)
{
  if (xJoystickOne > 10 && xRectOne <= screenMaxX - playerBarWidth)
  {
    clearSquares(xRectOne, yRectOne, xRectTwo, yRectTwo);
    *xRectOnePointer = *xRectOnePointer + 5;
  }
  if (xJoystickOne < -10 && xRectOne >= 0)
  {
    clearSquares(xRectOne, yRectOne, xRectTwo, yRectTwo);
    *xRectOnePointer = *xRectOnePointer - 5;
  }

  if (xJoystickTwo > 10 && xRectTwo <= screenMaxX - playerBarWidth)
  {
    clearSquares(xRectOne, yRectOne, xRectTwo, yRectTwo);
    *xRectTwoPointer = *xRectTwoPointer + 5;
  }
  if (xJoystickTwo < -10 && xRectTwo >= 0)
  {
    clearSquares(xRectOne, yRectOne, xRectTwo, yRectTwo);
    *xRectTwoPointer = *xRectTwoPointer - 5;
  }
}

void loop()
{
  int valOne = analogRead(vrxOne);
  xJoystickOne = map(valOne, 0, 4096, 50, -50);

  int valTwo = analogRead(vrxTwo);
  xJoystickTwo = map(valTwo, 0, 4096, 50, -50);

  moveRectangles(xJoystickOne, xJoystickTwo, xRectOne, yRectOne, xRectTwo, yRectTwo, &xRectOne, &xRectTwo);

  M5.Lcd.clear(BLACK);
  M5.Lcd.fillRect(xRectOne, yRectOne, playerBarWidth, playerBarHeight, 30465);
  M5.Lcd.fillRect(xRectTwo, yRectTwo, playerBarWidth, playerBarHeight, 50000);
  M5.Lcd.setCursor(0, 0);
  delay(25);
}