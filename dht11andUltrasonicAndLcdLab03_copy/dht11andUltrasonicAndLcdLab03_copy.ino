
/*
  Ultrasonic Sensor with DHT11 Integration

  Program Goal:
  - Use the DHT.h library to read temperature and humidity from a DHT11 sensor.
  - Use the Ultrasonic sensor and NewPing.g to measure distance based on the speed of sound, considering temperature and humidity readings.
  - Using LiquidCrystal libraries display temperature, humidity and distance on 16x2 lcd.
  - Display temperature and humidity on a single that scrolls. While distance displayed stagnantly on a seperate line.
  
  Main Theme:
  This program combines data from a DHT11 sensor, which measures temperature and humidity, with an Ultrasonic sensor to improve the accuracy of distance measurements.
  These measurements are read using the dht.h library. 
  The Ultrasonic sensor's speed of sound calculation takes into account temperature and humidity.
  The duration which these calculations are based on are read using the dht.h library.
  This is important because Ultrasonic sensor's accuracy depends on the speed of sound, which is influenced by temperature and humidity.
  Considering these factors in the speed of sound calculation the accuracy of the sensor is improved. These calculations are odne with float variable to improve accuracy.
  The duration which these calculations are based on are read using the NewPing.g library.
  Once these values are obtained they are tehen displayed on a lcd using the Liquid Crystal library.
  The scrolling portion of the lcd is achieved via string manipulation.

 Text Scrolling:
 In this program, string manipulation is used to create a scrolling effect for displaying temperature and humidity on one lien while distance remains stagnant.
 This is done by creating a variable named 'scrollText' then using it to hold the temperature and humidity information, like "temp" nad temp values.
 Then using function called 'substring'  pick out the part of the text that I wnat to display on LCD screen. 
 When the program runs, this selected piece of text is what is seen scrolling across lcd, creating a scrolling effect.
 The LCD screen has limited characters it can display, so by continually updating and displaying different portions of 'scrollText' in a loop, we achieve a scrolling effect.
 A void function is utilized to seperate the scrolling logic from rest of loop toimproving code readability.

  dht.h Commands and Functions Used:
  - DHT.read11(pin)
  - DHT.temperature
  - DHT.humidity

  Ultrasonic Sensor Commands and Functions Used:
  - sonar.ping_median(iterations): Measures distance using Ultrasonic sensor considering median for accuracy.
  
  LiquidCrystal Commands and Functions Used:
  - lcd.begin(cols, rows)
  - lcd.setCursor(col, row)
  - lcd.print(str)
  - lcd.clear()
  - lcd.write(char)

  - LCD Pin Configuration:
  - LCD RS pin to digital pin 12
  - LCD Enable pin to digital pin 11
  - LCD D4 pin to digital pin 5
  - LCD D5 pin to digital pin 4
  - LCD D6 pin to digital pin 3
  - LCD D7 pin to digital pin 2 

*/

#include <dht.h> // Includes dht.h library which is used to program with dht11.
#include <LiquidCrystal.h> // Includes LiquidCrystal llibrary which is used to program with lcd.
#include <NewPing.h>  // Include NewPing library used to program with ultrasonic sensor.

dht DHT;  // Declaration of an object 'DHT' of  dht' class reading DHT11 sensor data.
#define DHT11_PIN 7  //define pin corresponding to signal pin on dht11.

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;  // Define lcd pin configuration.
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);  //Initializes LiquidCrystal object and tells what pins are being used on lcd.

#define TRIGGER_PIN  10  // Define which pin corresponds to trigger pin on ultrasonic sensor.
#define ECHO_PIN     13  // Define which pin corresponds to echo pin on ultrasonic sensor.
#define MAX_DISTANCE 400  // Define maximum distance for ultrasonic sensor.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);// Create an instance of the ultrasonic sensor.

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

void setup() { 
  Serial.begin(9600);  // Start serial communication at 9600 baud 
  lcd.begin(16, 2);   // Definess how many rows and collumns there are on lcd being used.
  // The first line and colunm are line and colunm 0.
  lcd.createChar(0, customChar);  // Initializes first custom character.
}

void loop() {
  DHT.read11(DHT11_PIN);  // Read data from the DHT sensor.

  float hum = DHT.humidity;  // Get humidity value from the sensor.
  float temp = DHT.temperature;  // Get temperature value from the sensor.

  float duration = sonar.ping_median(5); // Measure distance using ultrasonic sensor with median filtering.

  float soundsp = 331.4 + (0.606 * temp) + (0.0124 * hum);  // Calculate speed of sound based on temperature and humidity.
  float soundcm = soundsp / 10000;  // Convert speed of sound to centimeters per microsecond.

  float distance = (duration / 2) * soundcm;  //Divide duration by two beacuse the duration is time there and back. Time of one way is = distance. multiply by soundcm to convert from ms to cm.

  displayTempHumDistance(temp, hum, distance);// Calling void function cretaed to display TempHumDistance values on lcd.

  Serial.print("Temp: "); // Prints exactly what's in "" to Serial Monitor.
  Serial.print(temp); // Prints temp value to Serial Monitor.
  Serial.print("C, Hum: ");  // Print label for humidity
  Serial.print(hum);  // Print the humidity value
  Serial.print("%, Distance: ");  /// Prints exactly what's in "" to Serial Monitor.
  Serial.println(distance);  // Prints distance value to Serial Monitor on a a new line of the serial monitor every time it loops.
  
  lcd.setCursor(8, 0);  // Set the cursor to column 8, line 0.
  lcd.write(8);  // Prints custom character in this case degree symbol on lcd starting from most last location cursor was set.
}

void displayTempHumDistance(float temp, float hum, float distance) { // defining Function to display Humidity Temperature and disatnce on lcd.
  // Text to be scrolled
  String scrollText = "Temp: " + String(temp) + (char)8 + "C, Hum: " + String(hum) + "%";  // Create a string with temperature and humidity information.

  
  int delayTime = 400;  // Set the delay between scrolling steps in milliseconds for readibility.

  // Scroll the text.
  for (int i = 0; i <= scrollText.length(); i++) {
    lcd.clear();  // Clear the LCD display.

    // Display the scrolling text on the first line.
    lcd.setCursor(0, 0);  // Set the cursor to column 0, line 0.
   lcd.print(scrollText.substring(i, i + 16)); // Displays a window of 16-characters of scrollText value, shifting that window evey loop creating a scrolling effect on the LCD.

    // Display stationary text distance on the second line.
    lcd.setCursor(0, 1);   // Set the cursor to column 0, line 1.
    lcd.print("Dist: ");  // Prints exactly whats in "" on lcd starting from last place cursor was set.
  
    if (distance >= 400 || distance <= 2) { //if the following parameters follow commands below..
      lcd.print("OutOfRange");  // Display "OutOfRange" on the LCD if the measured distance is either too far or too close
    } else { // if the parameters above where not met follow commands bellow.
      lcd.print(distance);  // Prints the measured distance on the LCD.
      lcd.print(" cm");  // Prints unit "cm" last place cursor was set in this case after the measured distance.
    }

    delay(delayTime);// Delay for readbility.
  }
}
