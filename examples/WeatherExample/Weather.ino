#include <TinyGPS++.h>
#include <SoftwareSerial.h>
/*
read from 120wx weatherStation
   This sample sketch demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
static const int RXPin = 10, TXPin = 11;
static const uint32_t weatherStationBaud = 4800;

// The TinyGPS++ object
TinyGPSPlus weatherStation;

// The serial connection to the weatherStation device
SoftwareSerial station(RXPin, TXPin);

void setup()
{
  Serial.begin(9600);
  station.begin(weatherStationBaud);

  Serial.println(F("weatherStation.ino"));
  Serial.println(F("A simple demonstration of TinyGPS++ with an attached weatherStation module"));
  Serial.println();
}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (station.available() > 0){
    if (weatherStation.encode(station.read()))
      displayInfo();
  }

  if (millis() > 5000 && weatherStation.charsProcessed() < 10)
  {
    Serial.println(F("No weatherStation detected: check wiring."));
    while(true);
  }
}

void displayInfo()
{
  Serial.print(F("weatherStation: ")); 
  if (weatherStation.windSpeed.isValid())
  {
    Serial.print(F("Wind speed: ")); 
    Serial.print(weatherStation.windSpeed.value(), 6);
  }
  else
  {
    Serial.print(F("wind speed INVALID"));
  }

  Serial.print(F(" "));
  if (weatherStation.windDirection.isValid())
  {
    Serial.print(F("Wind direction: ")); 
    Serial.print(weatherStation.windDirection.value(), 6);
  }
  else
  {
    Serial.print(F("windDirection INVALID"));
  }

  Serial.print(F(" "));
  if (weatherStation.barometric.inHg())
  {
    Serial.print(F("Barometric pressure: ")); 
    Serial.print(weatherStation.barometric.inHg(), 6);
  }
  else
  {
    Serial.print(F("barometric INVALID"));
  }

  Serial.print(F(" "));
  if (weatherStation.tempature.isValid())
  {
    Serial.print(F("Tempature: ")); 
    Serial.print(weatherStation.tempature.Fahrenheit(), 6);
    Serial.print(F(" Canada: ")); 
    Serial.print(weatherStation.tempature.C(), 6);
  }
  else
  {
    Serial.print(F("tempature INVALID"));
  }

  Serial.println();
}
