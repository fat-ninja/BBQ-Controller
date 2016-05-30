




/*
 * Part List
 * 1: MAX6675 Thermo Couple drive + K Typer Thermo couple
 * 1: 1.7A Cabable Mosfet 
 * 1: 12v 1.7 amp poweer supply  
 * 1: 12v 4500RPM blower Fan
 * 1: 16x2 LCD compatible with (compatible with Hitachi HD44780 driver) 
 * 
 * Libraries 
 * Adafruit MX6675 Library
 * Adafruit LCD 
 * br3ttb Arduino-PID-Library (https://github.com/br3ttb/Arduino-PID-Library/)
 * 
 * 
 */
 #include <LiquidCrystal.h>
 #include <PID_v1.h>
 #include <max6675.h>

//Theromo1
int thermoS0  = 12;
int thermoCS  = 11;
int thermoCLK = 10;
MAX6675 thermocouple(thermoCLK, thermoCS, thermoS0);
int vccPin = 9;
int gndPin = 8;

 
void setup() {
Serial.begin(9600);
//Thermo 1 pins
pinMode(vccPin, OUTPUT); digitalWrite(vccPin, HIGH);
pinMode(gndPin, OUTPUT); digitalWrite(gndPin, LOW);

Serial.println("Colum you should be working");
delay(500);


}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("C = "); 
   Serial.println(thermocouple.readCelsius());

   delay(1000);

}
