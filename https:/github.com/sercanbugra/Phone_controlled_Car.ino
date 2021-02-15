
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <Blynk.h>
#include <BlynkSimpleEsp8266.h>


#define RightMotorSpeed  14          // Enable/speed motors Right        GPIO14(D5)
#define LeftMotorSpeed  12        // Enable/speed motors Left 

#define RightMotorDir1   15     // L298N in1 motors Right           GPIO15(D8)
#define RightMotorDir2   13     // L298N in2 motors Right           GPIO13(D7)

#define LeftMotorDir1    2      // L298N in3 motors Left            GPIO2(D4)
#define LeftMotorDir2    0     // L298N in4 motors Left            GPIO0(D3)

char auth[] = "xVGQy0ru1MdAjFf1I0dRaVTyG8yWimGh";
char ssid[] = "FiberHGW_TP6392_2.4GHz";
char pass[] = "UHwPufPX";

int minRange = 312;
int maxRange = 712;

int minSpeed = 450;
int maxSpeed = 1020;
int noSpeed = 0;


void moveControl(int x, int y)
{

  if(y >= maxRange && x >= minRange && x <= maxRange) //zataci R
  {
    digitalWrite(RightMotorDir1,HIGH); 
    digitalWrite(RightMotorDir2,LOW);
    digitalWrite(LeftMotorDir1,HIGH);
    digitalWrite(LeftMotorDir2,LOW);
    analogWrite(RightMotorSpeed,maxSpeed);
    analogWrite(LeftMotorSpeed,maxSpeed);
  }
 
  // move forward right
  else if(x >= maxRange && y >= maxRange)   //zataci R
  {
   digitalWrite(RightMotorDir1,HIGH); 
    digitalWrite(RightMotorDir2,LOW);
    digitalWrite(LeftMotorDir1,HIGH);
    digitalWrite(LeftMotorDir2,LOW);
    analogWrite(RightMotorSpeed,noSpeed);
    analogWrite(LeftMotorSpeed,maxSpeed);
  }

  // move forward left
  else if(x <= minRange && y >= maxRange)
  {
    digitalWrite(RightMotorDir1,HIGH); 
    digitalWrite(RightMotorDir2,LOW);
    digitalWrite(LeftMotorDir1,HIGH);
    digitalWrite(LeftMotorDir2,LOW);
    analogWrite(RightMotorSpeed,maxSpeed);
    analogWrite(LeftMotorSpeed,noSpeed);
  }

  // neutral zone
  else if(y < maxRange && y > minRange && x < maxRange && x > minRange)
  {
    analogWrite(RightMotorSpeed,noSpeed);
    analogWrite(LeftMotorSpeed,noSpeed);
  }

 // move back
  else if(y <= minRange && x >= minRange && x <= maxRange)
  {
    digitalWrite(RightMotorDir1,LOW); 
    digitalWrite(RightMotorDir2,HIGH);
    digitalWrite(LeftMotorDir1,LOW);
    digitalWrite(LeftMotorDir2,HIGH);
   analogWrite(RightMotorSpeed,maxSpeed);
    analogWrite(LeftMotorSpeed,maxSpeed);
  }

  // move back and right
 else if(y <= minRange && x <= minRange)
  {
    digitalWrite(RightMotorDir1,LOW); 
    digitalWrite(RightMotorDir2,HIGH);
    digitalWrite(LeftMotorDir1,LOW);
    digitalWrite(LeftMotorDir2,HIGH);
    analogWrite(RightMotorSpeed,noSpeed);
    analogWrite(LeftMotorSpeed,maxSpeed); 
  }

  // move back and left
  else if(y <= minRange && x >= maxRange)
  {
    digitalWrite(RightMotorDir1,LOW); 
    digitalWrite(RightMotorDir2,HIGH);
    digitalWrite(LeftMotorDir1,LOW);
    digitalWrite(LeftMotorDir2,HIGH);
    analogWrite(RightMotorSpeed,maxSpeed);
    analogWrite(LeftMotorSpeed,noSpeed);
  }
}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
 
  // initial settings for motors off and direction forward
  pinMode(RightMotorSpeed, OUTPUT);
  pinMode(LeftMotorSpeed, OUTPUT);
  pinMode(RightMotorDir1, OUTPUT);
  pinMode(LeftMotorDir1, OUTPUT);
  pinMode(RightMotorDir2, OUTPUT);
  pinMode(LeftMotorDir2, OUTPUT);

 
    digitalWrite(RightMotorDir1,HIGH); 
    digitalWrite(RightMotorDir2,LOW);
    digitalWrite(LeftMotorDir1,HIGH);
    digitalWrite(LeftMotorDir2,LOW);

 
 }


void loop()
{
 
  Blynk.run();
}


BLYNK_WRITE(V1)
{
  int x = param[0].asInt();
  int y = param[1].asInt();
 
  Serial.print("x value is: ");
  Serial.println(x);
  Serial.print("y value is: ");
  Serial.println(y);

  moveControl(x,y);
}
