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

// Rectangles coordinates

int playerBarWidth = 70;
int playerBarHeight = 15;

int xRectOne = screenMaxX / 2 - playerBarWidth / 2;
int yRectOne = 10;

int xRectTwo = screenMaxX / 2 - playerBarWidth / 2;
int yRectTwo = screenMaxY - 10 - playerBarHeight;

// Player scores

int playerOneScore = 0;
int playerTwoScore = 0;

// Ball stuff

int xBall = screenMaxX / 2;
int yBall = screenMaxY / 2;
int ballRadius = 15;
int ballColor = 45000; 
bool xVector = true;
bool yVector = true;

void setup()
{
  M5.begin();       // Init M5Core
  M5.Power.begin(); // Init Power module

  pinMode(msOne, INPUT);
  pinMode(vryOne, INPUT);
  pinMode(vrxOne, INPUT);
  pinMode(msTwo, INPUT);
  pinMode(vryTwo, INPUT);
  pinMode(vrxTwo, INPUT);
  M5.Lcd.setTextSize(7);
}

bool score(int player)
{
  if (player == 1)
  {
    playerOneScore += 1;
    yVector = false;
  }
  else 
  {
    playerTwoScore += 1;
    yVector = true;
  }
  return true;
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

bool moveBall(int xBall, int yBall, int* xBallPointer, int* yBallPointer)
{
  if (xBall + ballRadius >= screenMaxX)
  {
    xVector = false;
  }
  if (xBall - ballRadius <= 0)
  {
    xVector = true;
  }
  if (yBall + ballRadius >= screenMaxY)
  {
    return score(1);
  }
  if (yBall - ballRadius <= 0)
  {
    return score(2);
  }
  *xBallPointer = xVector ? *xBallPointer + 3 : *xBallPointer - 3;
  *yBallPointer = yVector ? *yBallPointer + 3 : *yBallPointer - 3;
  return false;
}

void collisionDetection(int xBall, int yBall, int xRectOne, int yRectOne, int xRectTwo, int yRectTwo) 
{
  if (yBall - ballRadius > yRectOne && yBall - ballRadius < yRectOne + playerBarHeight)
  {
    if (xBall + ballRadius >= xRectOne && xBall - ballRadius <= xRectOne + playerBarWidth)
    {
      yVector = !yVector;
    }
  }

  if (yBall + ballRadius > yRectTwo && yBall + ballRadius < yRectTwo + playerBarHeight)
  {
    if (xBall + ballRadius >= xRectTwo && xBall - ballRadius <= xRectTwo + playerBarWidth)
    {
      yVector = !yVector;
    }
  }
}

void loop()
{
  bool game = false;
  while (!game) {
  // Read Joystick Values
  int valOne = analogRead(vrxOne);
  xJoystickOne = map(valOne, 0, 4096, 50, -50);
  int valTwo = analogRead(vrxTwo);
  xJoystickTwo = map(valTwo, 0, 4096, 50, -50);

  moveRectangles(xJoystickOne, xJoystickTwo, xRectOne, yRectOne, xRectTwo, yRectTwo, &xRectOne, &xRectTwo);
  collisionDetection(xBall, yBall, xRectOne, yRectOne, xRectTwo, yRectTwo);
  game = moveBall(xBall, yBall, &xBall, &yBall);

  M5.Lcd.clear(BLACK);
  M5.Lcd.fillRect(xRectOne, yRectOne, playerBarWidth, playerBarHeight, 30465);
  M5.Lcd.fillRect(xRectTwo, yRectTwo, playerBarWidth, playerBarHeight, 50000);
  m5.Lcd.drawCircle(xBall, yBall, ballRadius, ballColor);
  m5.Lcd.drawNumber(playerOneScore, 10, screenMaxY / 2 - 60);
  m5.Lcd.drawNumber(playerTwoScore, screenMaxX - 50, screenMaxY / 2 + 30);

  M5.Lcd.setCursor(0, 0);
  delay(25);
  }

  if (playerOneScore >= 5 || playerTwoScore >= 5)
  {
    playerOneScore = 0;
    playerTwoScore = 0;
  }

  xRectOne = screenMaxX / 2 - playerBarWidth / 2;
  yRectOne = 10;

  xRectTwo = screenMaxX / 2 - playerBarWidth / 2;
  yRectTwo = screenMaxY - 10 - playerBarHeight;
  
  xBall = screenMaxX / 2;
  yBall = screenMaxY / 2;
}