#include <ArduinoJson.h>
#include "SparkFunMPL3115A2.h" //Pressure sensor - Search "SparkFun MPL3115" and install from Library Manager
#include "SparkFunHTU21D.h" //Humidity sensor - Search "SparkFun HTU21D" and install from Library Manager

// Sparkfun weather shield
MPL3115A2 myPressure; //Create an instance of the pressure sensor
HTU21D myHumidity; //Create an instance of the humidity sensor

StaticJsonBuffer<200> jsonBuffer;
JsonObject& weather = jsonBuffer.createObject();

const byte LIGHT = A1;
const byte REFERENCE_3V3 = A3;

float temperature, humidity, pressure, lightLevel;
float startTime, currentTime;

void setup()
{
    Serial.begin(9600);
    
    myPressure.begin(); // Get sensor online
    myPressure.setModeBarometer(); // Measure pressure in Pascals from 20 to 110 kPa
    myPressure.setOversampleRate(7); // Set Oversample to the recommended 128
    myPressure.enableEventFlags(); // Enable all three pressure and temp event flags
    myHumidity.begin();

}


void loop()
{
    temperature = myHumidity.readTemperature();
    humidity = myHumidity.readHumidity();
    //tempPreC = myPressure.readTemp();
    pressure = myPressure.readPressure()/100;
    lightLevel = getLightLevel();
    
    currentTime = (millis() - startTime) / 1000;
    
    weather["sensor"] = "Temperature";
    weather["time"] = currentTime;
    weather["value"] = temperature;
    weather["unit"] = "Celsius";  
    weather.printTo(Serial);
    Serial.println("");

    weather["sensor"] = "Humidity";
    weather["time"] = currentTime;
    weather["value"] = humidity;
    weather["unit"] = "RelativeHumidity";
    weather.printTo(Serial);
    Serial.println("");

    weather["sensor"] = "Pressure";
    weather["time"] = currentTime;
    weather["value"] = pressure;
    weather["unit"] = "hPa";
    weather.printTo(Serial);
    Serial.println("");
    
    weather["sensor"] = "LightLevel";
    weather["time"] = currentTime;
    weather["value"] = lightLevel;
    weather["unit"] = "Percentage";
    weather.printTo(Serial);
    Serial.println("");
    
    delay(2000);
}

float getLightLevel()
{
    float operatingVoltage = analogRead(REFERENCE_3V3);
    float lightSensor =  analogRead(LIGHT);

    lightSensor = lightSensor / operatingVoltage; 

    return(lightSensor);
}

