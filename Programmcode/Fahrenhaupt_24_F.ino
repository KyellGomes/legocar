//libarys einbinden nur Innen

 #include<Servo.h>         
 Servo Lenkung;
 //#include "Adafruit_VL53L0X.h"



//Knopf
 //const int Knopf = 6;      //Knopf auf Pin 6
 int Knopf = 12;

// Gleichstrommotor 1     
 //int ENA = 12;          //
 int ENA = 6;        // Knopf getauscht mit ENA wg. PWM
 int in1 =17;          //Fahrmotor auf Pin 6,16,17
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
 int Kurvenfahrzeit = 1500;   
 long Kurvenzeit = 0;
 long Geradezeit = 2000;
 
 
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




//---------
void vorne() {
 Lenkung.write(90);
}
//---------
void links() {
 Lenkung.write(70);
}
//---------
void rechts() {
 Lenkung.write(120);
}
//---------
void geradeaus(int PWM) {
  digitalWrite(in1, HIGH);   // Motor 1 Starten
  digitalWrite(in2, LOW);    //Low mit High Tauschen für Richtung
  analogWrite(ENA, PWM);     //maximale Geschwindigkeit ist 255!!!
} 
//---------  
void Bremse() {
  digitalWrite(in1, LOW);    // Motor 1 Starten
  digitalWrite(in2, LOW);    //Low mit High Tauschen für Richtung
  analogWrite(ENA, 0);
}

 
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
  delay(20);
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
  delay(20);

/*
  Serial.print("L: ");
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
  delay(20);

  }




void Finde_Kurve_S1()   // Startplatz 1: Ohne Ausrichten, schnell auf Kurve reagieren
{
  messen_L();
  messen_R();
  if (L>60)  
  {

   Lenkung.write(70);        //Wenn Messung größer als 1000 dann voll nach rechts einlenken
   digitalWrite(AMPELgelb,HIGH); 
   Kurven = Kurven+1;
   delay (Kurvenfahrzeit); 
   Kurvenzeit = millis();
   vorne();
   messen_L();
   while (L>80)
   {
     delay(20);
     messen_L();     
   }   
   
    digitalWrite(AMPELgelb,LOW);    
    Lenkrichtung = -1;
  }
  else if (R > 60)
  {
    Lenkung.write(120);        //Wenn Messung größer als 60 dann voll nach links einlenken
    digitalWrite(AMPELrot,HIGH); 
    Kurven = Kurven+1;
    delay (Kurvenfahrzeit);
    Kurvenzeit = millis(); 
    vorne();
    messen_R();
    while (R>80)
    {
     delay(20);
     messen_R();     
    }     
    digitalWrite(AMPELrot,LOW);  
    Lenkrichtung = 1;   
  } 
  
}


void Finde_Kurve_S2() //Startplatz 2: mit Ausrichten in der Mitte
{
  messen_L();
  messen_R();
  if (L>60)  
  {

   Lenkung.write(70);        //Wenn Messung größer als 1000 dann voll nach rechts einlenken
   digitalWrite(AMPELgelb,HIGH); 
   Kurven = Kurven+1;
   delay (Kurvenfahrzeit); 
   Kurvenzeit = millis();
   vorne();
   messen_L();
   while (L>80)
   {
     delay(20);
     messen_L();     
   }   
   
    digitalWrite(AMPELgelb,LOW);    
    Lenkrichtung = -1;
  }
  else if (R > 60)
  {
    Lenkung.write(120);        //Wenn Messung größer als 60 dann voll nach links einlenken
    digitalWrite(AMPELrot,HIGH); 
    Kurven = Kurven+1;
    delay (Kurvenfahrzeit);
    Kurvenzeit = millis(); 
    vorne();
    messen_R();
    while (R>80)
    {
     delay(20);
     messen_R();     
    }     
    digitalWrite(AMPELrot,LOW);  
    Lenkrichtung = 1;   
  } 
  else  // Mitte halten
  {
    a = (R-L)*0.5 +90;
  
    if(a>100){                      //Abhängig davon lenkt er stärker oder schwächer in den Positiven oder Negativen Bereich
    a = 100;
    }
    else if (a<80){
      a = 80;
    }
    Lenkung.write(a);               //Stärke der Lenkung anhand der Variable ändern 
    delay(10);
     
  } 
  
}



//==============================================================================================================================================================================
void setup(){  //Festlegen der In+Out + Start/Erste Aktionen 
  
   Serial.begin(9600);
  
   int knopfstatus;
   int counter;  
   int startplatz = 0;
  
  
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
 /*
    pinMode(SHT_LOX1, OUTPUT);
    pinMode(SHT_LOX2, OUTPUT);
 */   
    digitalWrite(AMPELrot,HIGH);         //Ampel Rot
  /*  
    Serial.println(F("Shutdown pins inited..."));
 
    digitalWrite(SHT_LOX1, LOW);
    digitalWrite(SHT_LOX2, LOW);

 
    Serial.println(F("Both in reset mode...(pins are low)"));
   
   
    Serial.println(F("Starting..."));
    setID();                             //Set ID

       
  */ 
  
   //Start der Aktivitätt im Setup- - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   messen_R();
   messen_L();  
   messen_V();

 //Bestimme Startposition

   if (L < 10)    //Steht an der Linken InnenWand
   {
     Lenkrichtung = -1;
   } 

   if (R < 10)    //Steht an der Rechten InnenWand
   {
     Lenkrichtung = 1;
   } 
   if (V > 130)
   {
     startplatz = 2;  //hinterer Startplatz
   }
   else
   {
     startplatz = 1;
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
   
	//Starten mit langsam Geradeaus fahren---------------+
   geradeaus(180);  
       
  // Wenn weiter hinten direkt an der Wand gestartet, Wand ausweichen	   
   if ((Lenkrichtung == 1) && (startplatz == 2))
   {
      
      Lenkung.write(80);
      delay(700);
      vorne();
      delay(700);
      Lenkung.write(100);
      delay(700); 
      vorne(); 
      delay(100);       
      
   }  
   else if ((Lenkrichtung == -1)  && (startplatz == 2)) 
   {
    
      Lenkung.write(100);
      delay(700);
      vorne();
      delay(700);
      Lenkung.write(80);
      delay(700); 
      vorne();
      delay(100);
         
   }  
   else if ((Lenkrichtung != 0)  && (startplatz == 1))
   {
     delay(200);  // leicht nach vorne fahren
   }

   if (startplatz == 1) 
   {  
    
      while (Lenkrichtung == 0)
      {
          Finde_Kurve_S1();
      }
   } 
   else
   {                            
      while (Lenkrichtung == 0)
      {
          Finde_Kurve_S2();
      }
   }   
}

//================================================================================================================================================================================
void loop()
{ 
   
  messen_L();
  messen_R();

//Wenn Messung größer als 80 dann voll nach rechts einlenken
  if ((Lenkrichtung == -1) && (L>80) && (millis()-Kurvenzeit > Geradezeit))  
  {

   Lenkung.write(70);        
   digitalWrite(AMPELgelb,HIGH); 
   Kurven = Kurven+1;
   delay (Kurvenfahrzeit); 
   Kurvenzeit = millis();
   vorne();
   messen_L();
   while (L>80)
   {
     delay(20);
     messen_L();     
   }   
   delay(100);
   digitalWrite(AMPELgelb,LOW);    
  
  }
  //Wenn Messung größer als 80 dann voll nach links einlenken
  else if ((Lenkrichtung == 1) && (R > 80) && (millis()-Kurvenzeit > Geradezeit))
  {
    Lenkung.write(120);        
    digitalWrite(AMPELrot,HIGH); 
    Kurven = Kurven+1;
    delay (Kurvenfahrzeit);
    Kurvenzeit = millis(); 
    vorne();
    messen_R();
    while (R>80)
    {
     delay(20);
     messen_R();     
    } 
    delay(100);   
    digitalWrite(AMPELrot,LOW);  
    
  } 
  else  // keine Kurve
  {
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
     
  } 

 if (Kurven == 12)
 {
  delay(1300);
  Bremse();
  digitalWrite(AMPELgelb,HIGH); 
  digitalWrite(AMPELgrun,HIGH); 
  digitalWrite(AMPELrot,HIGH); 
 }  
}
//---------------------------------------------------------------------------------------------------------