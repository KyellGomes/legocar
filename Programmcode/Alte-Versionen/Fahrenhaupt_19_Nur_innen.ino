//libarys einbinden nur Innen

 #include<Servo.h>         
 Servo Lenkung;
 #include "Adafruit_VL53L0X.h"



//Knopf
 const int Knopf = 6;      //Knopf auf Pin 6

// Gleichstrommotor 1 
 int ENA = 12;          //
 int in1 =17;          //Fahrmotor auf Pin 12,16,17
 int in2 =16;         //

//Variablen
 int a = 0;
 int b = 0;
 int c = 0;
 int width = 0;
 int norm = 1000;
 int V = 0;
 int R = 0;
 int L = 0;
 int Rr = 0;
 int Ll = 0;
 int Seitemessen = 0;
 int Maxmessen = 1000;
 int Lenkrichtung = 0;
 int Kurven = 0;
 int Kurvenfahrzeit = 770;   
 long Kurvenzeit = 0;
 long Geradezeit = 800;
 
 
//Ampel
 int AMPELgrun = 4;
 int AMPELgelb = 3;
 int AMPELrot = 2;


//Messsensoren
 #define LOX1_ADDRESS 0x30
 #define LOX2_ADDRESS 0x31
 #define V_PIN A1
 #define L_PIN A6
 #define R_PIN A7
 #define VELOCITY_TEMP(temp)       ( ( 331.5 + 0.6 * (float)( temp ) ) * 100 / 1000000.0 ) // The ultrasonic velocity (cm/us) compensated by temperature


 // set the pins to shutdown
 #define SHT_LOX1 8
 #define SHT_LOX2 9     //Abstandsmesser auf Pin 8,9,14
 #define SHT_LOX3 14


 // objects for the vl53l0x
 Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
 Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();

 // this holds the measurement
 VL53L0X_RangingMeasurementData_t measure1;
 VL53L0X_RangingMeasurementData_t measure2;



 void setID() {
  // all reset
  digitalWrite(SHT_LOX1, LOW);    
  digitalWrite(SHT_LOX2, LOW);


  delay(10);
  // all unreset
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, HIGH);


  delay(10);

  // activating LOX1 and resetting LOX2
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, LOW);

  // initing LOX1
  if(!lox1.begin(LOX1_ADDRESS)) {
    Serial.println(F("Failed to boot first VL53L0X"));
    while(1);
  }
  delay(10);

  // activating LOX2
  digitalWrite(SHT_LOX2, HIGH);
    
  delay(10);

  //initing LOX2
  if(!lox2.begin(LOX2_ADDRESS)) {
    Serial.println(F("Failed to boot second VL53L0X"));
    while(1);
  }

}



//---------
void vorne() {
 Lenkung.write(90);
}
//---------
void links() {
 Lenkung.write(75);
}
//---------
void rechts() {
 Lenkung.write(110);
}
//---------
void geradeaus() {
  digitalWrite(in1, HIGH);   // Motor 1 Starten
  digitalWrite(in2, LOW);    //Low mit High Tauschen für Richtung
  analogWrite(ENA, 130);     //maximale Geschwindigkeit ist 255!!!
} 
//---------
void Bremse() {
  digitalWrite(in1, LOW);    // Motor 1 Starten
  digitalWrite(in2, LOW);    //Low mit High Tauschen für Richtung
  analogWrite(ENA, 0);
}

//---------------------------------
void messen_TOF() {
  
   lox1.rangingTest(&measure1, false); // pass in 'true' to get debug data printout!
   lox2.rangingTest(&measure2, false); // pass in 'true' to get debug data printout!   


   // print sensor one reading
   Serial.print(F("R: "));
   if(measure1.RangeStatus != 4) {     // if not out of range
     if(measure1.RangeMilliMeter < Maxmessen)
      {
        R = measure1.RangeMilliMeter;
      }
     else
     {
       R = Maxmessen;
        if (Lenkrichtung == 0) 
        {
          Lenkrichtung =1;
        }             
      }           
     Serial.print(R);       
     Rr = 0;
   }
     


    else {
     Serial.print(F("Out of range"));
     Rr = 1 ;  
           if (Lenkrichtung == 0) 
        {
          Lenkrichtung =1;
        }             
  
   }
   Serial.print(F("      L: "));   
  if(measure2.RangeStatus != 4) {     // if not out of range
    if(measure2.RangeMilliMeter < Maxmessen)
    {
      L = measure2.RangeMilliMeter;      
    }   
    else
     {
       L = Maxmessen;
       if (Lenkrichtung == 0) 
        {
          Lenkrichtung =-1;
        }             
     }  
    Ll = 0;    
    Serial.println(L);

   L = measure2.RangeMilliMeter;
  }

   
  else {
     Serial.print(F("Out of range"));
     Ll = 1;
          if (Lenkrichtung == 0) 
        {
          Lenkrichtung =-1;
        }             

  }

}
 
//---------------------------------
 
//----------
void messen_V()
{
  uint16_t distance;
  uint32_t pulseWidthUs;

 //Vorderer Messsensor    
  pinMode(V_PIN,OUTPUT);
  digitalWrite(V_PIN,LOW);

  digitalWrite(V_PIN,HIGH);  //Set the trig pin High
  delayMicroseconds(10);     //Delay of 10 microseconds
  digitalWrite(V_PIN,LOW);   //Set the trig pin Low

  pinMode(V_PIN,INPUT);    //Set the pin to input mode
  pulseWidthUs = pulseIn(V_PIN,HIGH);  //Detect the high level time on the echo pin, the output high level time represents the ultrasonic flight time (unit: us)

  distance = pulseWidthUs * VELOCITY_TEMP(20) / 2.0;  //The distance can be calculated according to the flight time of ultrasonic wave,/

  V =  distance * 10;

  Serial.print(F("V: "));
  Serial.println(V);

}  


void messen_L(){
  uint16_t distance;
  uint32_t pulseWidthUs; 
   
  //Linker Messsensor
  pinMode(L_PIN,OUTPUT);
  digitalWrite(L_PIN,LOW);

  digitalWrite(L_PIN,HIGH);  //Set the trig pin High
  delayMicroseconds(10);     //Delay of 10 microseconds
  digitalWrite(L_PIN,LOW);   //Set the trig pin Low

  pinMode(L_PIN,INPUT);      //Set the pin to input mode
  pulseWidthUs = pulseIn(L_PIN,HIGH);  //Detect the high level time on the echo pin, the output high level time represents the ultrasonic flight time (unit: us)

  distance = pulseWidthUs * VELOCITY_TEMP(20) / 2.0;  //The distance can be calculated according to the flight time of ultrasonic wave,/

  L =  distance * 10;  

  Serial.print(F("L: "));
  Serial.println(L);

}

void messen_R(){
  uint16_t distance;
  uint32_t pulseWidthUs;

  //Rechter Messsensor
  pinMode(R_PIN,OUTPUT);
  digitalWrite(R_PIN,LOW);

  digitalWrite(R_PIN,HIGH);  //Set the trig pin High
  delayMicroseconds(10);     //Delay of 10 microseconds
  digitalWrite(R_PIN,LOW);   //Set the trig pin Low

  pinMode(R_PIN,INPUT);  //Set the pin to input mode
  pulseWidthUs = pulseIn(R_PIN,HIGH);  //Detect the high level time on the echo pin, the output high level time represents the ultrasonic flight time (unit: us)

  distance = pulseWidthUs * VELOCITY_TEMP(20) / 2.0;  //The distance can be calculated according to the flight time of ultrasonic wave,/

  R =  distance * 10;

  Serial.print(F("R: "));
  Serial.println(R);}

  
//----------






//=============================================================================================
void setup(){  //Festlegen der In+Out + Start/Erste Aktionen 
  
   Serial.begin(9600);
  
   int knopfstatus;
   int counter;  
  
  
   pinMode(AMPELrot, OUTPUT);    //Ampelrot Pin 2
   pinMode(AMPELgelb, OUTPUT);   //Ampelgelb Pin 3
   pinMode(AMPELgrun, OUTPUT);   //Ampelgrun Pin 4  
   pinMode(Knopf, INPUT);        //Knopf Pin 6
   Lenkung.attach(7);            //Lenkung auf Pin 7
   pinMode(ENA, OUTPUT);         //ENA = GleichStromMotor1(Geschwindigkeitsregelung) auf Pin 12
   pinMode(in1, OUTPUT);         //in1 des Antriebmotors auf Pin 17
   pinMode(in2, OUTPUT);         //in2 des Antriebmotors auf Pin 16
   //Messsensoren
     
    digitalWrite(AMPELrot,HIGH);         //Ampel Rot
    // wait until serial port opens for native USB devices
    while (! Serial) { delay(1); }
 
    pinMode(SHT_LOX1, OUTPUT);
    pinMode(SHT_LOX2, OUTPUT);
    
    digitalWrite(AMPELrot,HIGH);         //Ampel Rot
    
    Serial.println(F("Shutdown pins inited..."));
 
    digitalWrite(SHT_LOX1, LOW);
    digitalWrite(SHT_LOX2, LOW);

 
    Serial.println(F("Both in reset mode...(pins are low)"));
   
   
    Serial.println(F("Starting..."));
    setID();                             //Set ID

       
     
  
   //Start der Aktivitätt im Setup- - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   messen_R();
   messen_L();   
   if (L < 100)    //Steht an der Linken InnenWand
   {
     Lenkrichtung = -1;
   } 

   if (R < 100)    //Steht an der Rechten InnenWand
   {
     Lenkrichtung = 1;
   } 
   
   digitalWrite(AMPELrot,LOW);              //Rot aus
   digitalWrite(AMPELgelb,HIGH);            //Ampel Gelb 

   knopfstatus = digitalRead(Knopf);
   while (knopfstatus==LOW){
     delay(20);
     knopfstatus = digitalRead(Knopf);
    }         


   digitalWrite(AMPELgelb,LOW);             //Gelb aus
   digitalWrite(AMPELgrun,HIGH);            //Ampel Grün
 

   geradeaus();                             //Starten mit Geradeaus fahren
  
}

//=========================================================================================================
void loop(){ 

  
if (Lenkrichtung == 1)
{
  messen_R();
}
else if (Lenkrichtung == 1)
{
   messen_L();  
}
else
{
  messen_R();
  messen_L();
  
}  

  
  //Lenkung
 if ((Lenkrichtung == 0) && (L > 800))
 {
   Lenkrichtung = -1;   
 }

 if ((Lenkrichtung == 0) && (R > 800))
 {
   Lenkrichtung = 1;   
 }

 if (Kurven == 0)
 {
   Kurvenzeit = millis() + Geradezeit + 1; 
 } 

  //if(((R>=600) ) && (Lenkrichtung == 1) && (millis() - Kurvenzeit > Geradezeit))
  if((R>600) && (Lenkrichtung == 1) && (millis() - Kurvenzeit > Geradezeit))
  {
       
   digitalWrite(AMPELrot,HIGH); 
   Lenkung.write(115);        //Wenn Messung größer als 1000 dann voll nach links einlenken
   Kurven = Kurven+1;
   delay (Kurvenfahrzeit);
   Kurvenzeit = millis();
   vorne();
   messen_R();
   while (R>600)
   {
     delay(50);
     messen_R();     
   }   
   
   digitalWrite(AMPELrot,LOW);    
  }


  //if(((L>=1000) || (Ll==1)) && (Lenkrichtung == -1) && (millis() - Kurvenzeit > Geradezeit))
  if((L>600) && (Lenkrichtung == -1) && (millis() - Kurvenzeit > Geradezeit))
  {
   digitalWrite(AMPELgelb,HIGH); 
   Lenkung.write(75);        //Wenn Messung größer als 1000 dann voll nach rechts einlenken
   Kurven = Kurven+1;
   delay (Kurvenfahrzeit); 
   Kurvenzeit = millis();
   vorne();
   messen_L();
   while (L>600)
   {
     delay(50);
     messen_L();     
   }   
   
   digitalWrite(AMPELgelb,LOW);          
  }

 if (Lenkrichtung == 1) 
 {
    a = (R - 250)*0.0312 + 92;         //a ist der Rechte Wert minus den Linke Wert Mal Faktor + 95(Mitte der Lenkung vom Servo)
      if(a>125){                      //Abhängig davon lenkt er stärker oder schwächer in den Positiven oder Negativen Bereich
      a = 125;
      }

      if(a<70){
      a = 70;
    }
    Serial.print("Lenkung: " + a); 
    Lenkung.write(a);               //Stärke der Lenkung anhand der Variable ändern 
  
 }
 else if (Lenkrichtung == -1)
 {
    a = (250 - L)*0.0312 + 92;         //a ist der Rechte Wert minus den Linke Wert Mal Faktor + 95(Mitte der Lenkung vom Servo)
      if(a>125){                      //Abhängig davon lenkt er stärker oder schwächer in den Positiven oder Negativen Bereich
      a = 125;
      }

      if(a<70){
      a = 70;
    }
    Serial.print("Lenkung: " + a); 
    Lenkung.write(a);               //Stärke der Lenkung anhand der Variable ändern 
  
 }
 else
 {
    a = (R - L)*0.0312 + 92;         //a ist der Rechte Wert minus den Linke Wert Mal Faktor + 95(Mitte der Lenkung vom Servo)
      if(a>125){                      //Abhängig davon lenkt er stärker oder schwächer in den Positiven oder Negativen Bereich
      a = 125;
      }

      if(a<70){
      a = 70;
    }
    Serial.print("Lenkung: " + a); 
    Lenkung.write(a);               //Stärke der Lenkung anhand der Variable ändern 
 
 }
 


 /*if(V<10){
  if(L>R){
   digitalWrite(AMPELgelb,HIGH); 
   Lenkung.write(75);
   Kurven = Kurven+1;
   delay (Kurvenfahrzeit); 
   Kurvenzeit = millis();   
   digitalWrite(AMPELgelb,LOW); 
   messen();
  }
 else{
   Lenkung.write(105);
   Kurven = Kurven+1;
   delay (Kurvenfahrzeit);
   Kurvenzeit = millis();
   digitalWrite(AMPELrot,LOW);
  }
 }*/

 if (Kurven == 12)
 {
  delay(500);
  Bremse();
  digitalWrite(AMPELgelb,HIGH); 
  digitalWrite(AMPELgrun,HIGH); 
  digitalWrite(AMPELrot,HIGH); 
 } 
 
}
//---------------------------------------------------------------------------------------------------------
