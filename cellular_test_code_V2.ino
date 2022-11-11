#include <Notecard.h>
//#include <NotecardPseudoSensor.h>
#include "Adafruit_TSL2591.h"
#include <Adafruit_Sensor.h>

//using namespace blues;

#define usbSerial Serial
#define productUID "edu.wpi.orockrohr:cmvs_cloud"

Notecard notecard;
Adafruit_TSL2591 tsl_0;
//NotecardPseudoSensor sensor(notecard);


void setup() 
{
  delay(2500);
  usbSerial.begin(115200);
  notecard.begin();
  notecard.setDebugOutputStream(usbSerial);
  J *req = notecard.newRequest("hub.set");
  JAddStringToObject(req, "product", productUID);
  JAddStringToObject(req, "mode", "continuous");
  notecard.sendRequest(req);

    delay(1000);
//Init Light Sensor and wait for text feedback
    tsl_0.begin(); // Init DHT11
    Serial.println("Waiting sensor to init...");
    delay(10000);

}

void loop() 
{
//  float temperature = sensor.temp();
//  float humidity = sensor.humidity();
//  
//  usbSerial.print("Temperature = ");
//  usbSerial.print(temperature);
//  usbSerial.println(" *C");
//  usbSerial.print("Humidity = ");
//  usbSerial.print(humidity);
//  usbSerial.println(" %");

    double l = tsl_0.getLuminosity(TSL2591_INFRARED);
    usbSerial.println(l);

  //Send data from notecard to notehub.io
  J *req = notecard.newRequest("note.add");
  if (req != NULL)
  {
    JAddStringToObject(req, "file", "sensors.qo");
    JAddBoolToObject(req, "sync", true);
    J *body = JAddObjectToObject(req, "body");
    if (body)
    {
      JAddNumberToObject(body, "temp", l);
      //JAddNumberToObject(body, "humidity", humidity);
    }
    notecard.sendRequest(req);
  }
  
  usbSerial.println("------------------------------------------------");
  delay(10000);

}
