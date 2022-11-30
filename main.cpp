#include <M5Stack.h>

// Pins 

int vryOne = 26;
int vrxOne = 25;
int msOne = 3;

int vryTwo = 36;
int vrxTwo = 35;
int msTwo = 1;

// Rectangles coordonates

int xOne = 0;
int yOne = 0;
int xTwo = 0;
int yTwo = 0;

int xRectOne = 100;
int yRectOne = 100;

int xRectTwo = 200;
int yRectTwo = 200;

void setup(){
  M5.begin(); //Init M5Core. Initialize M5Core
  M5.Power.begin(); //Init Power module. Initialize the power module
  
  pinMode(msOne, INPUT);
  pinMode(vryOne, INPUT);
  pinMode(vrxOne, INPUT);
  pinMode(msTwo, INPUT);
  pinMode(vryTwo, INPUT);
  pinMode(vrxTwo, INPUT);
  M5.Lcd.setTextSize(50);
}

void clearSquares(int xRectOne, int yRectOne, int xRectTwo, int yRectTwo) {
  M5.Lcd.fillRect(xRectOne, yRectOne, 50, 50, 0);
  M5.Lcd.fillRect(xRectTwo, yRectTwo, 50, 50, 0);
}

void loop() {
    int valOne = analogRead(vryOne);
    yOne = map(valOne, 0, 4096, 50, -50);
    valOne = analogRead(vrxOne);
    xOne = map(valOne, 0, 4096, 50, -50);

    int valTwo = analogRead(vryTwo);
    yTwo = map(valTwo, 0, 4096, 50, -50);
    valTwo = analogRead(vrxTwo);
    xTwo = map(valTwo, 0, 4096, 50, -50);
    
    if (yOne > 10 && yRectOne <= 450) {
      clearSquares(xRectOne, yRectOne, xRectTwo, yRectTwo);
      yRectOne++;
    }
    if (yOne < -10 && yRectOne >= 0) {
      clearSquares(xRectOne, yRectOne, xRectTwo, yRectTwo);
      yRectOne--;
    }
    if (xOne > 10 && xRectOne <= 450) {
      clearSquares(xRectOne, yRectOne, xRectTwo, yRectTwo);
      xRectOne++;
    }
    if (xOne < -10 && xRectOne >= 0) {
      clearSquares(xRectOne, yRectOne, xRectTwo, yRectTwo);
      xRectOne--;
    }

    if (yTwo > 10 && yRectOne <= 450) {
      clearSquares(xRectOne, yRectOne, xRectTwo, yRectTwo);
      yRectTwo++;
    }
    if (yTwo < -10 && yRectTwo >= 0) {
      clearSquares(xRectOne, yRectOne, xRectTwo, yRectTwo);
      yRectTwo--;
    }
    if (xTwo > 10 && xRectOne <= 450) {
      clearSquares(xRectOne, yRectOne, xRectTwo, yRectTwo);
      xRectTwo++;
    }
    if (xTwo < -10 && xRectTwo >= 0) {
      clearSquares(xRectOne, yRectOne, xRectTwo, yRectTwo);
      xRectTwo--;
    }

    M5.Lcd.clear(BLACK);
    M5.Lcd.fillRect(xRectOne, yRectOne, 50, 50, 30465);
    M5.Lcd.fillRect(xRectTwo, yRectTwo, 50, 50, 50000);
    M5.Lcd.setCursor(0, 0);
    delay(25);
}