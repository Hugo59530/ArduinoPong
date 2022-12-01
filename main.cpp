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

// Rectangles coordonates

int xRectOne = 100;
int yRectOne = 100;

int xRectTwo = 200;
int yRectTwo = 200;

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
  M5.Lcd.fillRect(xRectOne, yRectOne, 50, 50, 0);
  M5.Lcd.fillRect(xRectTwo, yRectTwo, 50, 50, 0);
}

void moveRectangles(int yJoystickOne, int xJoystickOne, int yJoystickTwo, int xJoystickTwo, int xRectOne, int yRectOne, int xRectTwo, int yRectTwo)
{
  if (yJoystickOne > 10 && yRectOne <= 350)
  {
    clearSquares(xRectOne, yRectOne, xRectTwo, yRectTwo);
    yRectOne++;
  }
  if (yJoystickOne < -10 && yRectOne >= 0)
  {
    clearSquares(xRectOne, yRectOne, xRectTwo, yRectTwo);
    yRectOne--;
  }
  if (xJoystickOne > 10 && xRectOne <= 350)
  {
    clearSquares(xRectOne, yRectOne, xRectTwo, yRectTwo);
    xRectOne++;
  }
  if (xJoystickOne < -10 && xRectOne >= 0)
  {
    clearSquares(xRectOne, yRectOne, xRectTwo, yRectTwo);
    xRectOne--;
  }

  if (yJoystickTwo > 10 && yRectOne <= 350)
  {
    clearSquares(xRectOne, yRectOne, xRectTwo, yRectTwo);
    yRectTwo++;
  }
  if (yJoystickTwo < -10 && yRectTwo >= 0)
  {
    clearSquares(xRectOne, yRectOne, xRectTwo, yRectTwo);
    yRectTwo--;
  }
  if (xJoystickTwo > 10 && xRectOne <= 350)
  {
    clearSquares(xRectOne, yRectOne, xRectTwo, yRectTwo);
    xRectTwo++;
  }
  if (xJoystickTwo < -10 && xRectTwo >= 0)
  {
    clearSquares(xRectOne, yRectOne, xRectTwo, yRectTwo);
    xRectTwo--;
  }
}

void loop()
{
  int valOne = analogRead(vryOne);
  yJoystickOne = map(valOne, 0, 4096, 50, -50);
  valOne = analogRead(vrxOne);
  xJoystickOne = map(valOne, 0, 4096, 50, -50);

  int valTwo = analogRead(vryTwo);
  yJoystickTwo = map(valTwo, 0, 4096, 50, -50);
  valTwo = analogRead(vrxTwo);
  xJoystickTwo = map(valTwo, 0, 4096, 50, -50);

  moveRectangles(yJoystickOne, xJoystickOne, yJoystickTwo, xJoystickTwo, xRectOne, yRectOne, xRectTwo, xRectTwo);

  M5.Lcd.clear(BLACK);
  M5.Lcd.fillRect(xRectOne, yRectOne, 50, 50, 30465);
  M5.Lcd.fillRect(xRectTwo, yRectTwo, 50, 50, 50000);
  M5.Lcd.setCursor(0, 0);
  delay(25);
}