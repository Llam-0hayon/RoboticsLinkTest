
/*
  Voltmeter using LCD 

  Program Goal:
  - Utilize reading of analog inputs to calculate and display the voltage.
  - Present the voltage reading on an LCD using LiquidCrystal libraries.

  Main Theme:
  Convert reading of analog input to voltage using map function/
  Then display the results of this conversion on a lcd display using LiquidCrystal Libraries.

  LiquidCrystal Commands and Functions Used:
  - lcd.begin(cols, rows): Initializes the LCD with the specified number of columns and rows.
  - lcd.setCursor(col, row): Sets the LCD cursor position to the specified column and row.
  - lcd.print(str): Prints the specified string on the LCD.
  - lcd.clear(): Clears the entire LCD display.

 lcd Pin Configuration:
  - LCD RS pin to digital pin 12
  - LCD Enable pin to digital pin 11
  - LCD D4 pin to digital pin 5
  - LCD D5 pin to digital pin 4
  - LCD D6 pin to digital pin 3
  - LCD D7 pin to digital pin 2 

*/

#include <LiquidCrystal.h> // Includes LiquidCrystal llibrary which is used to program with lcd.

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; //Defines the lcd pin configuration.
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // // Initializes LiquidCrystal object and tells what pins are being used on lcd.


void setup() {
  
  Serial.begin(9600);  // Initialize serial communication at 9600 baud.
  lcd.begin(16, 2);  // Initialize the LCD with 16 columns and 2 rows.
 // The first line and colunm are line and colunm 0.

}

void loop() {
 
  int sensorValue = analogRead(A0);  // sensorValue variable is equal to reading of analog value of pin A0.
  Serial.print("BitValue:");  // Prints exactly what's in "" on Serial Monitor.
  Serial.print(sensorValue);  // Print the value of sensorValue on Serial Monitor.
 
 float voltX = map(sensorValue, 0,1023, 0,5000);// Using map function converts from anaolog reading to millivolts
 float voltage = (voltX/1000);// Divides voltX by 1000 to get value in volts.
 // had to convert to millis cause map function cannot be a float varriable so to get decimal places must first convert value to milli then to volts.
 
  Serial.print("Voltage:");  // Print exactly hwta in "" label to the serial monitor.
  Serial.println(voltage);  // print value for voltage Serial Monitor.ln makes it so that everything printed after this print, is printed on a new line every time code is looped.
  delay(100);// delay for readability in the serial monitor.

  lcd.clear();  // Clears the lcd display.This is done to refresh display to prevent any artifacting.

  lcd.setCursor(0, 0);  // Set the cursor to column 0, line 0. 
  lcd.print("Volts:");  // // Prints exactly whats in "" on lcd starting from last place cursor was set.
  lcd.setCursor(0, 1);  //// Set the cursor to column 0, line 1.
  lcd.print(voltage);  //Prints the updated value for voltage on lcd starting from last place cursor was set.
  lcd.print("V");  // Display the unit "V" on lcd starting from most last location of cursor in this case after voltage value.
}
