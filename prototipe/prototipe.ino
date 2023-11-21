#include <LiquidCrystal.h>
#include <Servo.h>
/*
Circuito: 
 * pin RS collegato al pin digitale 12 
 * pin E (Enable) collegato al pin digitale 11 
 * pin D4 collegato al pin digitale 5 
 * pin D5 collegato al pin digitale 4 
 * pin D6 collegato al pin digitale 3 
 * pin D7 collegato al pin digitale 2 
 * pin R/W collegato al GND 
 * pin 1 e pin 4 collegati a GND 
 * pin 2 collegato a +Vcc 
 * centrale del potenziometro/trimmer da 10 KOhm collegato al pin 3 del'LCD 
 * pin SX potenziometro/trimmer collegato a +Vcc 
 * pin DX potenziometro/trimmer collegato a GND 
 * i pin SX e DX del potenziometro/trimmer possono essere interscambiati 
*/  
 
  
/* 
   Viene creata l'istanza dell'oggetto LiquidCrystal chiamata lcd in cui 
   sono indicati i pin dell'LCD collegati alle uscite digitali di Arduino 
*/ 

// CIRCUIT ELEMENTS
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  
int ledRed = 7;
int ledYellow = 8;
int ledGreen = 9;
Servo Servo1;

// SYSTEM PARAMETERS
//eficiency
int EFICIENCY=100;

// TO BE SET FOR OPTIMAL DEMO 
int WARNING_TRESHOLD=95;
int CRITICAL_TRESHOLD=90;

// DISPLAY FUNCTIONS
// Clear display
void clearDisplay(){
  lcd.clear();
  lcd.setCursor(0,0);
}

// LOW EFICIENCY PROCEDURE
void startCleanUp(){
  // start cleanup process
  clearDisplay();
  lcd.print("pannello sporco pulizia necessaria");  
  digitalWrite(ledRed,HIGH);
  digitalWrite(ledGreen,LOW);
  digitalWrite(ledYellow,LOW);
  Servo1.write(90);
  delay(1000);
  // end cleanup process
  clearDisplay();
  lcd.print("pulizia completata");  
  Servo1.write(0);
  digitalWrite(ledRed,LOW);
  digitalWrite(ledGreen,LOW);
  digitalWrite(ledYellow,LOW);
  EFICIENCY=100;

}

void setup() {  
  // circuit setup
  pinMode(ledGreen,OUTPUT);
  pinMode(ledRed,OUTPUT);
  pinMode(ledYellow,OUTPUT);
  Servo1.attach (6);
  lcd.begin(16, 2);

  //reset leds
  digitalWrite(ledRed,LOW);
  digitalWrite(ledGreen,LOW);
  digitalWrite(ledYellow,LOW);

  // reset servo
  Servo1.write(0);

  // hello 
  lcd.print("Corte di napoli");  
  delay(1000);


}  
  
void loop() {  
  clearDisplay();
  EFICIENCY-=1;
  
  if(EFICIENCY > WARNING_TRESHOLD){
    lcd.print("efficienza:");  
    lcd.print(EFICIENCY);  
    digitalWrite(ledGreen,HIGH);
    digitalWrite(ledYellow,LOW);
    digitalWrite(ledRed,LOW);
  }
  if(EFICIENCY <= WARNING_TRESHOLD && EFICIENCY > CRITICAL_TRESHOLD ){
    lcd.print("efficienza:");  
    lcd.print(EFICIENCY);  
    digitalWrite(ledRed,LOW);
    digitalWrite(ledGreen,LOW);
    digitalWrite(ledYellow,HIGH);
  }
  if(EFICIENCY <= CRITICAL_TRESHOLD){
    startCleanUp();
  }

  delay(1000);
}  


// numero che decrementa ogni secondo, printa valore in display
// sotto soglia colora led, 
// sotto soglia critica 
// se pulsante premuto attiva soglia critica


