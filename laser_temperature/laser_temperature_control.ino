// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);


// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

/*
 * The setup function. We only start the sensors here
 */
void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");
  
  // Start up the library
  sensors.begin();
  lcd.begin();
  lcd.backlight();
  //lcd.print("Hello, world!");
}

/*
 * Main function, get and show the temperature
 */
   unsigned long int previousmsec = 0;
void loop(void)
{ 

  int n, m;
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
  Serial.print("Temperature for the device 1 (index 0) is: ");
  Serial.println(sensors.getTempCByIndex(0));
  Serial.println(sensors.getTempCByIndex(1));
  Serial.println(sensors.getTempCByIndex(2));
  for(n = 0; n < 14;){
  if(n < 9){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("RES:  ");
  lcd.print(sensors.getTempCByIndex(0));
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("O/P:  ");
  lcd.print(sensors.getTempCByIndex(1));
  lcd.print((char)223);
  lcd.print("C");
  delay(1000);
  }
  else if( n > 9){
  unsigned long int sec = millis()/1000;
  unsigned long int min = millis()/60000;
  sec = sec % 60;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("AMB:  ");
  lcd.print(sensors.getTempCByIndex(2));
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("TIME: ");
  lcd.print(min);
  lcd.print(":");
  lcd.print(sec);
  delay(1000);
  }
  else if (n > 14)
  n = 0;
  n++;
  }
  }
  
