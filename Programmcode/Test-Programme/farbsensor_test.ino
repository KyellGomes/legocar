
#include <Wire.h>
#include "Adafruit_TCS34725.h"
int farbe = 0;
int farbe_save = 0;

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);
uint16_t white, red, green, blue, white_ref;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Serial.println("Color View Test!");
  
  while (!tcs.begin()) {
    Serial.println("No TCS34725 found ... check your connections");
    delay(100);
  }
  Serial.println("Found sensor");
  tcs.setInterrupt(false);      // turn on LED

  // Bestimme Referenzwert weiss
  delay(60);  // takes 50ms to read 
  
  tcs.getRawData(&red, &green, &blue, &white_ref);
  Serial.print("Weiss ref:\t"); Serial.println(white_ref);  
}


void loop() {

  delay(50);  // takes 50ms to read 
  
  tcs.getRawData(&red, &green, &blue, &white);
  
   Serial.print("Rot: ");
   Serial.println(red);
   Serial.print("Gruen: ");
   Serial.println(green);
   Serial.print("Blau: ");
   Serial.println(blue);
   Serial.print("Weiss: ");
   Serial.println(white);
 

 
  if (white < white_ref*0.8)
  {
    
    if ((red > blue) && (red > green))
    {
      farbe = 1;
      Serial.println("orange");

    }
    else if ((blue > red) && (red < green))
    {
      farbe = 2;    
      Serial.println("blau");      
    }
    else
    {
     farbe = 0;
     //Serial.println("weiss");      

    }
  }
  else
  {
     farbe = 0;
  }

  if (farbe_save != farbe)
  {
    Serial.println(farbe);
    Serial.print("Grauwert:\t"); Serial.println(white);  
  }

  farbe_save = farbe;


}

