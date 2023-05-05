//libarys einbinden nur Innen

 #include<Servo.h>         
 Servo Lenkung;
 #include "Adafruit_VL53L0X.h"
 #include "Adafruit_TCS34725.h" 
 #include "HUSKYLENS.h"
 HUSKYLENS huskylens;
 



//Knopf
 const int Knopf = 12;      //Knopf auf Pin 6

// Gleichstrommotor 1 
 int ENA = 6;          //
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
 int Linie = 0;
 //Block
 int B_ID = 0;
 int B_x = 0;
 int B_y = 0;
 int B_hoch = 0;
 int B_breit = 0;
 int B_Unterkante = 0;

 long Kurvenzeit = 0;
 long Geradezeit = 4000;
 
//Farbsensor 
 Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);
 uint16_t white, red, green, blue, white_ref;

//Ampel
 int AMPELgrun = 4;
 int AMPELgelb = 3;
 int AMPELrot = 2;


//Messsensoren
 /*#define LOX1_ADDRESS 0x30
 #define LOX2_ADDRESS 0x31*/
 #define V_PIN A1
 #define L_PIN A6
 #define R_PIN A7
 #define VELOCITY_TEMP(temp)       ( ( 331.5 + 0.6 * (float)( temp ) ) * 100 / 1000000.0 ) // The ultrasonic velocity (cm/us) compensated by temperature


 /*// set the pins to shutdown
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

*/

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
  analogWrite(ENA, 188);     //maximale Geschwindigkeit ist 255!!!
} 
//---------
void zurruck() {
  digitalWrite(in1, LOW);   // Motor 1 Starten
  digitalWrite(in2, HIGH);    //Low mit High Tauschen für Richtung
  analogWrite(ENA, 220);     //maximale Geschwindigkeit ist 255!!!
}
//---------  
void Bremse() {
  digitalWrite(in1, LOW);    // Motor 1 Starten
  digitalWrite(in2, LOW);    //Low mit High Tauschen für Richtung
  analogWrite(ENA, 0);
}
//---------  
void Linienfinder() {
   tcs.getRawData(&red, &green, &blue, &white);
  
   /*Serial.print("Rot: ");
   Serial.println(red);
   Serial.print("Gruen: ");
   Serial.println(green);
   Serial.print("Blau: ");
   Serial.println(blue);
   Serial.print("Weiss: ");
   Serial.println(white);*/
 

 
  if (white < white_ref*0.8)
  {
    
    if ((red > blue) && (red > green))
    {
      Linie = 1;
      Serial.println("orange");

    }
    else if ((blue > red) && (red < green))
    {
      Linie = 2;    
      Serial.println("blau");      
    }
    else
    {
     Linie = 0;
     //Serial.println("weiss");      

    }
  }
  else
  {
     Linie = 0;
  }

}

//---------------------------------
/*void messen_TOF() {
  
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

}*/
 
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

  V =  distance;
  delay(20) ;
  /*
  Serial.print(F("V: "));
  Serial.println(V);
*/
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

  L =  distance;
  delay(20) ;    
/*
  Serial.print(F("L: "));
  Serial.println(L);
*/
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

  R =  distance;
  delay(20) ;
  /*
  Serial.print(F("R: "));
  Serial.println(R);
*/
}
//----------
void Finde_Block()
 {
    int unterkante = 0;
    B_ID = 0;
    B_x = 0;
    B_y = 0;
    B_hoch = 0;
    B_breit = 0;
    B_Unterkante = 0;    
 

    if (huskylens.requestBlocksLearned())
    {
      // nur vordersten Block speichern
        for (int i = 0; i < huskylens.count(); i++)
        {
            HUSKYLENSResult result = huskylens.get(i);
            unterkante = result.yCenter + result.height/2;
            if (unterkante > 125)
            {
                if (unterkante > B_Unterkante )
                {
                  HUSKYLENSResult result = huskylens.read();
                  
                  B_ID = result.ID;
                  B_x = result.xCenter;
                  B_y = result.yCenter;
                  B_hoch = result.height;
                  B_breit = result.width;
                  B_Unterkante = unterkante;

                }
            }
        }
    }
    Serial.print("Block: ");
    Serial.println(B_ID);    
   
 }
//----------





//==============================================================================================================================================================================
void setup(){  //Festlegen der In+Out + Start/Erste Aktionen 
  
   Serial.begin(9600);
   Wire.begin();   
  
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
 
    /*pinMode(SHT_LOX1, OUTPUT);
    pinMode(SHT_LOX2, OUTPUT);*/
    
    digitalWrite(AMPELrot,HIGH);         //Ampel Rot
    
    /*Serial.println(F("Shutdown pins inited..."));
 
    digitalWrite(SHT_LOX1, LOW);
    digitalWrite(SHT_LOX2, LOW);

 
    Serial.println(F("Both in reset mode...(pins are low)"));
   
   
    Serial.println(F("Starting..."));
    setID();                             //Set ID*/

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

    Serial1.begin(9600);  //Hardware-Serial Verbindung zur Kamera
    while (! Serial1) { delay(1); }  //warte auf Kameraport
    while (!huskylens.begin(Serial1))

     {
        Serial.println(F("Begin failed!"));
        delay(100);
     }

       
   //Start der Aktivitätt im Setup- - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   
   messen_R();
   messen_L();   
   if (L < 10)    //Steht an der Linken InnenWand
   {
     Lenkrichtung = -1;
   } 

   if (R < 10)    //Steht an der Rechten InnenWand
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
 
   Kurvenzeit = millis() + Geradezeit + 1; 

   geradeaus();                             //Starten mit Geradeaus fahren
  
}

//================================================================================================================================================================================
void loop(){ 

  Linienfinder();
  
  //Lenkung
 if (Lenkrichtung == 0)
 {
   if (Linie == 2)
   {
      Lenkrichtung = -1;   
   }
   else if (Linie == 1)
   {
      Lenkrichtung = 1;  
   }
 }

 

  Finde_Block();

  if(B_ID == 1)  //Rotes Hindernis gesehen 
  {
    Lenkung.write(110);
    digitalWrite(AMPELrot,HIGH);      
    while(B_ID ==1)
    {
      Finde_Block();
    }
    vorne();
    delay(1300);
    Lenkung.write(65);
    delay(500);
    vorne();
    delay(50);    
    Lenkung.write(105);
    delay(50);
    vorne();    
    
    digitalWrite(AMPELrot,LOW);      
    
  }

  else if(B_ID == 2)  //Grünes Hindernis gesehen 
  {
    Lenkung.write(65);
    digitalWrite(AMPELgrun,HIGH);
    while(B_ID ==2)
    {
      Finde_Block();
    }
    vorne();
    delay(1300);
    Lenkung.write(110);
    delay(500);
    vorne();
    delay(50);    
    Lenkung.write(70);
    delay(50);
    vorne();

    
    digitalWrite(AMPELgrun,LOW);
  }
  else  //Kein Hindernis
  {
    messen_L();
    messen_R();
    if (R < 20)
    {
      a = 110;
    }
    else if (L < 20)
    {
      a = 70;
    }
    else
    {
      a = 90;
    }

    /*    
    a = (R - L)*0.27 + 90;         //a ist der Rechte Wert minus den Linke Wert Mal Faktor + 95(Mitte der Lenkung vom Servo)
    if(a>125){                      //Abhängig davon lenkt er stärker oder schwächer in den Positiven oder Negativen Bereich
    a = 125;
    }

    if(a<70){
    a = 70;
    } 
   */         
    Lenkung.write(a);      
    
  }
      

 

 /*//Links
 if ((Linie != 0) && (Lenkrichtung == -1) && (millis() - Kurvenzeit > Geradezeit))
 {
   messen_V();
   while(V > 15)
   { 
     delay(50);
     messen_V();
   }   
   Serial.print("Linie Links ");
   Bremse();
   digitalWrite(AMPELgelb,HIGH); 
   delay(150);
   Lenkung.write(115);
   zurruck(); 
   delay(2200);
   Bremse();   
   vorne();
   Kurven = Kurven+1;
   Kurvenzeit = millis();
   digitalWrite(AMPELgelb,LOW);
   geradeaus();    
 }
 //Rechts
  else if ((Linie != 0) && (Lenkrichtung == 1) && (millis() - Kurvenzeit > Geradezeit))
 {
   messen_V();
   while(V > 15)
   { 
     delay(50);
     messen_V();
   }   
      
   Serial.print("Linie Rechts ");
   Bremse();
   digitalWrite(AMPELgelb,HIGH);    
   delay(150);
   Lenkung.write(65);
   zurruck(); 
   delay(2600);
   Bremse(); 
   vorne();
   Kurven = Kurven+1;
   Kurvenzeit = millis();  
   digitalWrite(AMPELgelb,LOW);
   geradeaus();   
 }*/

   
  if (Lenkrichtung == 1)
    {
        a = (R-20)*0.6 +90;
      
        if(a>100){                      //Abhängig davon lenkt er stärker oder schwächer in den Positiven oder Negativen Bereich
        a = 100;
        }
        else if (a<80){
          a = 80;
        }
        Lenkung.write(a);               //Stärke der Lenkung anhand der Variable ändern 
        delay(50);

    }
    else if (Lenkrichtung == -1)
    {
        a = (20-L)*0.6 +90;
      
        if(a>100){                      //Abhängig davon lenkt er stärker oder schwächer in den Positiven oder Negativen Bereich
        a = 100;
        }
        else if (a<80){
          a = 80;
        }
        Lenkung.write(a);               //Stärke der Lenkung anhand der Variable ändern 
        delay(50);

    }
    else
    {
        a = (R-L)*0.6 +90;
      
        if(a>100){                      //Abhängig davon lenkt er stärker oder schwächer in den Positiven oder Negativen Bereich
        a = 100;
        }
        else if (a<80){
          a = 80;
        }
        Lenkung.write(a);               //Stärke der Lenkung anhand der Variable ändern 
        delay(50);

    }    
     

     
 /*if ((Linie != 0) && (Lenkrichtung == -1) && (millis() - Kurvenzeit > Geradezeit))
 {
   while((B_ID ==2)
   { 
     Lenkung.write(65);
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
 
} // end loop
//-----------------------------------------------------------------------------------