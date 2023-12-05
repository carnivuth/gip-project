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

Servo Servo1;

int ledRed = 7;
int ledYellow = 8;
int ledGreen = 9;

int button = 13;

// SYSTEM PARAMETERS
//eficiency
int EFICIENCY=100;

// TO BE SET FOR OPTIMAL DEMO 
int WARNING_TRESHOLD=90;
int CRITICAL_TRESHOLD=80;

int buttonState=0;

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
  lcd.print("Pannello sporco pulizia necessaria");  
  digitalWrite(ledRed,HIGH);
  digitalWrite(ledGreen,LOW);
  digitalWrite(ledYellow,LOW);
  Servo1.write(180);
  delay(1000);
  // end cleanup process
  clearDisplay();
  lcd.print("Pulizia completata");  
  Servo1.write(0);
  //digitalWrite(ledRed,LOW);
  //digitalWrite(ledGreen,LOW);
  //digitalWrite(ledYellow,LOW);
  EFICIENCY=100;

}

void setup() {  
  // circuit setup
  pinMode(ledGreen,OUTPUT);
  pinMode(button,INPUT);
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
  lcd.print("OSMOS");  
  delay(1000);


}  
  
void loop() {  
  clearDisplay();
  EFICIENCY-=1;
  buttonState = digitalRead(button);
  if(buttonState == HIGH){
    startCleanUp();
  }
  if(EFICIENCY > WARNING_TRESHOLD){
    lcd.print("Efficienza:");  
    lcd.print(EFICIENCY);  
    digitalWrite(ledGreen,HIGH);
    digitalWrite(ledYellow,LOW);
    digitalWrite(ledRed,LOW);
  }
  if(EFICIENCY <= WARNING_TRESHOLD && EFICIENCY > CRITICAL_TRESHOLD ){
    lcd.print("Efficienza:");  
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