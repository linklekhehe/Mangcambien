#include <Wire.h>
#include <BH1750.h>
#include <Arduino.h>
BH1750 lightMeter;

void setup() {
    Serial.begin(115200);
    Wire.begin();
    
    if (lightMeter.begin()) {
        Serial.println("BH1750 initialized!");
    } else {
        Serial.println("BH1750 initialization failed!");
    }
}

void loop() {
    float lux = lightMeter.readLightLevel();
    Serial.print("Light Intensity: ");
    Serial.print(lux);
    Serial.println(" lx");
    delay(1000); 
}
