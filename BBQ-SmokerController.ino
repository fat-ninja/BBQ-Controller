/*

  BBQ Controller

  Parts List:
    HD44780 Button Module
    Thermocouple with driver board (MAX6675)
    12v 1A tolerant MOSFET
    12v FAN

  Outstanding Functionality:
    Ability to set Temp High and Temp Low
    Storage of Temp High and Temp Low in EEPROM
    PWM Sensing from FAN Tach (OPTIONAL)

*/

// Include Libraries
#include <LiquidCrystal.h>
#include <max6675.h>

// Pin Definitions
#define BUTTON_PIN   0

#define LCD_D4       4
#define LCD_D5       5
#define LCD_D6       6
#define LCD_D7       7
#define LCD_RS       8
#define LCD_EN       9

#define THERMO_SCK   12
#define THERMO_CS    11
#define THERMO_S0    10

#define FAN_OUT      13

// State Definitions
#define BUTTON_RIGHT 0
#define BUTTON_UP    1
#define BUTTON_LEFT  2
#define BUTTON_DOWN  3
#define BUTTON_IDLE  4

#define GUI_IDLE     0
#define GUI_SET_TH   1
#define GUI_SET_TL   2

// Constants
#define FAN_MINPWM   100
#define FAN_STARTPWM 150

// Global Variables
char _guiState = GUI_IDLE;
float _currentTemp = 0;
float _tempHigh    = 30.0;
float _tempLow     = 25.0;

// Function Prototypes
int readButton(void);
float readThermo1(void);
void updateDisplay(void);
void guiDrawIdle(void);
void setFanSpeed(void);

// Program Space

// Initialize Classes
MAX6675 thermo1(THERMO_SCK, THERMO_CS, THERMO_S0);
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void setup() {
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" BBQ Controller ");
  lcd.setCursor(0,1);
  lcd.print("  NOM NOM NOM");
  delay(3000);
}

void loop() {
  _currentTemp = readThermo1();
  updateDisplay();
  setFanSpeed();
  delay(1000);
}

// Function Space

/*
 * Function: readButton()
 * Returns: int (see BUTTON_* definitions)
 */
int readButton(void) {
  int adcValue = analogRead(BUTTON_PIN);

  if(adcValue < 50) {
    return BUTTON_RIGHT;
  } else if(adcValue > 200 && adcValue < 250) {
    return BUTTON_UP;
  } else if(adcValue > 450 && adcValue < 500) {
    return BUTTON_DOWN;
  } else if(adcValue > 725 && adcValue < 775) {
    return BUTTON_LEFT;
  } else {
    return BUTTON_IDLE;
  }
}

/*
 * Function readThermo1(void)
 * Returns: float
 */
 float readThermo1(void) {
  return thermo1.readCelsius();
 }

/*
 * Function: updateDisplay(void)
 * Returns: void
 */
void updateDisplay(void) {
  switch(_guiState) {
    case GUI_SET_TH:
      guiDrawIdle();
      break;
    case GUI_SET_TL:
      guiDrawIdle();
      break;
    default:
      guiDrawIdle();
      break;
  }
}

/*
 * Function: guiDrawIdle(void)
 * Returns: void
 */
void guiDrawIdle(void) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Thermo1: ");
  lcd.print(_currentTemp);
  lcd.print((char)223);
  lcd.print("C");
}

//TODO: Fix Pin Assignments Here re: FAN
//      Clean up function to allow for ramped (simulated PID) response
/*
 * Function: setFanSpeed(void)
 * returns: void
 */
void setFanSpeed(void) {
  if(_currentTemp < _tempHigh && _currentTemp > _tempLow) {
    analogWrite(13, 255);
  } else if(_currentTemp > _tempHigh) {
    analogWrite(13, 0);
  } else {
    analogWrite(13,127);
  }
}

