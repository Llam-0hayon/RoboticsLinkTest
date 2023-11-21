/*
  DHT11 Temperature and Humidity Sensor with LCD Display

  Program Goal:
  - Utilize the DHT.h library to read temperature and humidity from a DHT11 sensor.
  - Display the temperature and humidity values on an LCD using LiquidCrystal libraries.
  
  Main Theme:
  This program reads temperature and humidity values from a DHT11 sensor using the DHT.h library. The readings are then displayed on a 16x2 LCD using the LiquidCrystal library.
  A custom character (degree symbol) is usedfor displacing degrees celcius on the LCD.

  Libraries Used:
  - DHT.h: Provides functions for reading temperature and humidity from DHT sensors.
  - LiquidCrystal.h: Facilitates communication with the LCD.

  LiquidCrystal Commands and Functions Used:
  - lcd.begin(cols, rows)
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

  dht.h Commands and Functions Used:
  - DHT.read11(pin): Reads temperature and humidity from the DHT11 sensor connected to the specified pin.
  - DHT.temperature: Retrieves the temperature value from the DHT11 sensor.
  - DHT.humidity: Retrieves the humidity value from the DHT11 sensor.

*/

#include <dht.h> // Includes dht.h library which is used to program with dht11.
#include <LiquidCrystal.h> // Includes LiquidCrystal llibrary which is used to program with lcd..

dht DHT;// Declaration of an object 'DHT' of the 'dht' class reading DHT11 sensor data.

#define DHT11_PIN 7 //define pin corresponding to signal pin on dht11.
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; //Defines the lcd pin configuration.
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //Initializes LiquidCrystal object and tells what pins are being used on lcd.

// Create a custom character using binary to say which cells are illmuanted and which are not.
byte customChar[8] = {
 B11100,
  B10100,
  B11100,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

void setup(){
  Serial.begin(9600); //  // Initialize serial communication at 9600 baud.
lcd.begin(16, 2); // Definess how many rows and collumns there are on lcd being used.
// The first line and colunm are line and colunm 0.
lcd.createChar(0, customChar); // Initializes first custom character.
} 

void loop(){

  DHT.read11(DHT11_PIN);  // Read data from the DHT sensor.
  Serial.print("Temperature = ");// Prints exactly what's in "" on Serial Monitor.
  Serial.println(DHT.temperature);// Prints temperature detected by dht11 to Serial Monitor. ln makes it so that everything printed after this print, is printed on a new line every time code is looped.
  Serial.print("Humidity = ");// Prints exactly what's in "" on Serial Monitor.
  Serial.println(DHT.humidity); //Prints humdity detected by dht11 to Serial Monitor.ln makes it so that everything printed after this prin is printed on a new line every time code is looped.
  delay(1000);// delay for readability in the serial monitor.
 
  lcd.clear();  // Clears the lcd display.This is done to refresh display to prevent any artifacting.

  lcd.setCursor(0, 0); // Set the cursor to column 0, line 0.
  lcd.print("Temp: "); // Prints exactly whats in "" on lcd starting from last place cursor was set.
  lcd.print(DHT.temperature); // Prints the updated value for DHT.temperature on lcd starting from last location of cursor. In this case after "Temp".
   lcd.write(8); // Prints custom character in this case degree symbol on lcd starting from most last location of cursor in this case after DHT.temperature value.
  lcd.print("C");// Prints exactly whats in "" on lcd starting from last location of cursor. In this case after customChar[8].
  lcd.setCursor(0, 1); // Set the cursor to column 0, line 1.
  lcd.print("Humidity: "); // Prints exactly whats in "" on lcd starting from last place cursor was set.
  lcd.print(DHT.humidity);// Prints the updated value for DHT.humidity on lcd starting from last location of cursor. In this case after "Humidity".
  lcd.print("%");//// Prints exactly whats in "" on lcd starting from last location of cursor. In this case after value of DHT.Humidity.

}
