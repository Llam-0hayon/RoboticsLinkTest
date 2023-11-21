/* 
  Ohm Meter using LCD and 1kOhm Pull-Up Resistor

  Program Goal:
  - Utilize using reading of analog inputs calculate the resistance (Ohms).
  - Display the Ohms value on an LCD with omega symbol using LiquidCrystal libraries.
  
  Main Theme:
  Using reading analog input to calculate voltage, current, and ultimately the Ohms value using Ohm's Law and float variables . 
  Using LiquidCryslal libraries have the results displayed on an LCD, with a custom character (Omega symbol) to represent Ohms.

  LiquidCrystal Commands and Functions Used:
  - lcd.begin(cols, rows)
  - lcd.createChar(index, charArray)
  - lcd.setCursor(col, row)
  - lcd.print(str)
  - lcd.clear()
  - lcd.write(char)

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

// Create a custom character using binary to say which cells are illmuanted and which are not.
byte customChar[8] = { 

  0b00000,  
  0b11111,  
  0b10001,  
  0b10001,  
  0b10001,  
  0b11011,  
  0b01010,  
  0b11011  

};

void setup() {  

Serial.begin(9600); //  // Initialize serial communication at 9600 baud.
lcd.begin(16, 2); // Definess how many rows and collumns there are on lcd being used.
// The first line and colunm are line and colunm 0.
lcd.createChar(0, customChar); // Initializes first custom character.

}  

void loop() {  

int sensorValue = analogRead (A0); // sensorValue variable is equal to reading of analog value of pin A0.
Serial.print("BitValue:");// Prints out exactly whats in "" on Serial Monitor.
Serial.print(sensorValue);// Prints out value of sensorValue variable.  

float voltage = sensorValue* (5.0/1023.0);// Converts the analog reading (0 - 1023 or 16bit) to  voltage (0 - 5V) by multiplying bit value by the rate of change of the linear relationship between bits and volts. 
Serial.print("\t");// Prints space on Serial Monitor.
Serial.print ("voltage:");// Prints exactly what's in "" on Serial Monitor.
Serial.print(voltage);// print out voltage value on to on Serial Monitor.
delay(100);// // delay for readability in the serial monitor.

// Finding current in Amperes using ohms law (I=V/R). 1000ohms is reisitance cause that is resistance of pull up resistor. 
float vAcross = (5.0 - voltage);
float current = (vAcross/1000);
Serial.print("\t");// Prints space on Serial Monitor.
Serial.print ("current(amps)t:");// Prints exactly what's in "" on Serial Monitor.
Serial.print(current,5);// Print out value for current on Serial Monitor with five decimal places.
delay(100);// delay for readability in the serial monitor.

float Ohms=  (voltage/current);// Divides value of voltage and value of current to find ohms value acording to Ohms law R=V/I.
Serial.print("\t");// prints space on Serial Monitor.
Serial.print("\t");// prints a second space on Serial Monitor.
Serial.print ("Ohms:");// prints exactly what's in "" 
Serial.println(Ohms);// Print value of Ohms to Serial Monitor.ln makes it so that everything printed after this print, is printed on a new line every time code is looped.
delay(100);// delay for readability in the serial monitor.

lcd.clear(); // Clear the lcd display.This is done to refresh display to prevent any artifacting.

lcd.setCursor(0, 0); // Set the cursor to column 0, line 0.
lcd.print("Ohms:"); // Prints exactly whats in "" on lcd starting from last place cursor was set.
lcd.setCursor(0, 1); // Set the cursor to column 0, line 1.
lcd.print(Ohms);  // Prints the updated value for Ohms on lcd starting from last place cursor was set.
lcd.write(8); // Prints custom character in this case omega symbol on lcd starting from most last location of cursor in this case after ohm value.
}  