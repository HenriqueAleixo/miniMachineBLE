#include <Arduino.h>
#include "miniMachineBLE.h"

// Definições dos pinos do ESP32
int in1 = 22;
int in2 = 23;
int in3 = 12;
int in4 = 13;

void Forward()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void Backward()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void TurnRight()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void TurnLeft()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void ForwardLeft()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void ForwardRight()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
void BackwardLeft()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
void BackwardRight()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void Stop()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void handleDir(const String &dir)
{
  if (dir == "w")
    Forward();
  else if (dir == "s")
    Backward();
  else if (dir == "a")
    TurnLeft();
  else if (dir == "d")
    TurnRight();
  else if (dir == "q")
    ForwardLeft();
  else if (dir == "e")
    ForwardRight();
  else if (dir == "z")
    BackwardLeft();
  else if (dir == "c")
    BackwardRight();
  else
    Stop();
}

void setup()
{
  Serial.begin(115200);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Stop();
  miniMachineBLE_begin("MiniMachine_01", handleDir);
  
}

void loop()
{
  delay(100);
}
