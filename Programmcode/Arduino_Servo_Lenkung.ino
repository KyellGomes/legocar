#include<Servo.h>
Servo Lenkung;

void setup() 
{
Lenkung.attach(7);
}

void loop()
{
 Lenkung.write(120);
 delay(3000);
 Lenkung.write(90);
 delay(3000); 
 Lenkung.write(65);
 delay(3000); 
}
