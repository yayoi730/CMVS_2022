#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <stdio.h>

#include "Adafruit_TSL2591.h"
#define TCAADDR 0x70
#define TCAADDR1 0x71

Adafruit_TSL2591 tsl_0;
Adafruit_TSL2591 tsl_1;
Adafruit_TSL2591 tsl_2;
Adafruit_TSL2591 tsl_3;
Adafruit_TSL2591 tsl_4;
Adafruit_TSL2591 tsl_5;
Adafruit_TSL2591 tsl_6;
Adafruit_TSL2591 tsl_7;
Adafruit_TSL2591 tsl_8;
void initialize_sensor(Adafruit_TSL2591 sensor, int sensor_num){
//*************INITIALIZING FIRST SENSOR*******************************
sensor.setGain(TSL2591_GAIN_MED);  // 25x gain
sensor.setTiming(TSL2591_INTEGRATIONTIME_300MS);
//**********************************************************************
}

void tcaselect (uint8_t i) {
  if (i > 7) return;

  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}

void sensorselect (uint8_t i) {
  if (i > 7) return;

  Wire.beginTransmission(TCAADDR1);
  Wire.write(1 << i);
  Wire.endTransmission();
}


void setup() {
  initialize_sensor(tsl_0,0);
  initialize_sensor(tsl_1,1);
  initialize_sensor(tsl_2,2);
  initialize_sensor(tsl_3,3);
  initialize_sensor(tsl_4,4);
  initialize_sensor(tsl_5,5);
  initialize_sensor(tsl_6,6);
  initialize_sensor(tsl_7,7);
  initialize_sensor(tsl_8,0);
  Serial.begin(9600);
  delay(100);

}
void sensorLuminance(Adafruit_TSL2591 sensor, int addr){
  delay(500);
  tcaselect(addr);
  Serial.print(addr);
  Serial.print(F(": Irradiance=\t"));
  Serial.print(sensor.getLuminosity(TSL2591_INFRARED));
  Serial.println();
}

void sensorLuminances(Adafruit_TSL2591 sensor, int addr){
  delay(500);
  sensorselect(addr);
  Serial.print(8);
  Serial.print(F(": Irradiance=\t"));
  Serial.print(sensor.getLuminosity(TSL2591_INFRARED));
  Serial.println();
}


void loop() {
  Wire.beginTransmission(TCAADDR1);
  Wire.write(0);  // no channel selected
  Wire.endTransmission();
  sensorLuminance(tsl_0,0);
  sensorLuminance(tsl_1,1);
  sensorLuminance(tsl_2,2);
  sensorLuminance(tsl_3,3);
  sensorLuminance(tsl_4,4);
  sensorLuminance(tsl_5,5);
  sensorLuminance(tsl_6,6);
  sensorLuminance(tsl_7,7);
  Wire.beginTransmission(TCAADDR);
  Wire.write(0);  // no channel selected
  Wire.endTransmission();
  sensorLuminances(tsl_8,0);
  
}
