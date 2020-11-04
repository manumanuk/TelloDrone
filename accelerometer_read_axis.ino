#include <Mouse.h>
#include <stdlib.h>

const int xInput = A0;
const int yInput = A1;
const int zInput = A2;

// initialize minimum and maximum Raw Ranges for each axis
int RawMin = 0;
int RawMax = 1023;

// Take multiple samples to reduce noise
const int sampleSize = 10;

struct gForce {
  float x;
  float y;
  float z;
} currentGForceVal, prevGForceVal;

void setup() 
{
  Mouse.begin();
  analogReference(EXTERNAL);
  Serial.begin(9600);
  prevGForceVal = measureG(prevGForceVal);
}

void loop() 
{

  currentGForceVal = measureG(currentGForceVal);
//  Serial.print("X, Y, Z  :: ");
//  Serial.print(currentGForceVal.x);
//  Serial.print("G, ");
//  Serial.print(currentGForceVal.y);
//  Serial.print("G, ");
//  Serial.print(currentGForceVal.z);
//  Serial.println("G");

  int mouseMoveX = int(((prevGForceVal.x-currentGForceVal.x)*100) + 0.5);
  int mouseMoveY = int(((prevGForceVal.y-currentGForceVal.y)*100) + 0.5);
  mouseMoveY = -mouseMoveY;
  if (abs(mouseMoveX)<3)
    mouseMoveX = 0;
  if (abs(mouseMoveY)<3)
    mouseMoveY = 0;
//  Serial.print(mouseMoveX);
//  Serial.print(", ");
//  Serial.print(mouseMoveY);
//  Serial.println();
  //Mouse.move(mouseMoveX, mouseMoveY, 0);
//  if (mouseMoveX == 0) {
//    
//  } else if (mouseMoveX<0) {
//    int amount = map(mouseMoveX, 0, 60, 20, 500);
//    Serial.print("left ");
//    Serial.println(abs(amount));
//  } else if (mouseMoveX>0) {
//    int amount = map(mouseMoveX, 0, 60, 20, 500);
//    Serial.print("right ");
//    Serial.println(abs(amount));
//  }
//  if (mouseMoveY == 0) {
//    
//  } else if (mouseMoveY>0) {
//    int amount = map(mouseMoveY, 0, 60, 20, 500);
//    Serial.print("forward ");
//    Serial.println(abs(amount));
//  }
//  else if (mouseMoveY<0) {
//    int amount = map(mouseMoveY, 0, 60, 20, 500);
//    Serial.print("back ");
//    Serial.println(abs(amount));
//  }
  int amountX = map(mouseMoveX, -60, 60, -100, 100);
  int amountY = map(mouseMoveY, -60, 60, -100, 100);
  Serial.print("rc ");
  Serial.print(amountX);
  Serial.print(" ");
  Serial.print(amountY);
  Serial.println(" 0 0");

  delay(20);
}

// Take samples and return the average
int ReadAxis(int axisPin)
{
  long reading = 0;
  analogRead(axisPin);
  delay(1);
  for (int i = 0; i < sampleSize; i++)
  {
  reading += analogRead(axisPin);
  }
  return reading/sampleSize;
}

gForce measureG (gForce givenStruct) {
  //Read raw values
  int xRaw = ReadAxis(xInput);
  int yRaw = ReadAxis(yInput);
  int zRaw = ReadAxis(zInput);

  // Convert raw values to 'milli-Gs"
  long xScaled = map(xRaw, RawMin, RawMax, -3000, 3000);
  long yScaled = map(yRaw, RawMin, RawMax, -3000, 3000);
  long zScaled = map(zRaw, RawMin, RawMax, -3000, 3000);

  // re-scale to fractional Gs
  givenStruct.x = xScaled / 1000.0;
  givenStruct.y = yScaled / 1000.0;
  givenStruct.z = zScaled / 1000.0;

  return givenStruct;
}
