
// Gleichstrommotor 1
int ENA = 12;
int in1 = 17;
int in2 = 16;


void setup(){
  
  pinMode(ENA, OUTPUT);     //gsm1 gsm = GleichStromMotor
  pinMode(in1, OUTPUT);     //in1
  pinMode(in2, OUTPUT);    //in2
}


void loop(){

 
  digitalWrite(in1, LOW);  // Motor 1 beginnt zu rotieren
  digitalWrite(in2, HIGH);

  analogWrite(ENA, 130);   // Motor 1 soll mit der Geschwindigkeit "200" (max. 255) rotieren 
 
}
