// pre setup - LCD
// include the library code:
#include <LiquidCrystal.h>
#include <Wire.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// pre setup - thermocouple
#include <SPI.h>
#include "Adafruit_MAX31855.h"
// Example creating a thermocouple instance with software SPI on any three
// digital IO pins.
#define MAXDO   6
#define MAXCS   7
#define MAXCLK  8

#define RELAY1 9

// initialize the Thermocouple
Adafruit_MAX31855 thermocouple(MAXCLK, MAXCS, MAXDO);

void setup() {
  // put your setup code here, to run once:
  
  // setup - LCD
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setCursor(0,1);
  lcd.write("Mish Mash Labs");
  delay(1000);

  // setup - thermocouple
  Serial.begin(9600);

  while (!Serial) delay(1); // wait for Serial on Leonardo/Zero, etc

  Serial.println("MAX31855 test");
  // wait for MAX chip to stabilize
  delay(500);
  Serial.print("Initializing sensor...");
  if (!thermocouple.begin()) {
    Serial.println("ERROR.");
    while (1) delay(10);
  }

  // setup Relay
  pinMode(RELAY1, OUTPUT);
  digitalWrite(RELAY1, HIGH);

  
  Serial.println("DONE.");
  
}

void loop() {
  // read thermocouple
   // basic readout test, just print the current temp
   Serial.print("Internal Temp = ");
   double int_temp = thermocouple.readInternal();
   Serial.println(int_temp);

   double c = thermocouple.readCelsius();
   if (isnan(c)) {
     Serial.println("Something wrong with thermocouple!");
   } else {
     Serial.print("C = ");
     Serial.println(c);
   }

   // print on LCD
   lcd.clear();
   lcd.setCursor(0,1);
   lcd.write("Temp (C): ");
   lcd.print(c);


   if(c >= 15){
    digitalWrite(RELAY1, LOW);
    Serial.println("Light On");
   }
   else if(c < 15){
    digitalWrite(RELAY1, HIGH);
   }
   delay(1000);

   

}
