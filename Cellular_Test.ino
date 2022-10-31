#include <Notecard.h>
#include <NotecardPseudoSensor.h> 
using namespace blues;
#define usbSerial Serial
#define productUID "edu.wpi.orockrohr:cmvs_cloud"
Notecard notecard;
NotecardPseudoSensor sensor(notecard);

void setup() {
  delay(2500);
  usbSerial.begin(115200);  
  notecard.begin();
  notecard.setDebugOutputStream(usbSerial);
  J *req = notecard.newRequest("hub.set");
  JAddStringToObject(req, "product", productUID);
  JAddStringToObject(req, "mode", "continuous");
  notecard.sendRequest(req);
}

void loop() {
  float temperature = sensor.temp();
  float humidity = sensor.humidity();
  
  usbSerial.print("Temperature = ");
  usbSerial.print(temperature);
  usbSerial.println(" *C");
  usbSerial.print("Humidity = ");
  usbSerial.print(humidity);
  usbSerial.println(" %");
  J *req = notecard.newRequest("note.add");
  if (req != NULL)
  {
    JAddStringToObject(req, "file", "sensors.qo");
    JAddBoolToObject(req, "sync", true);
    J *body = JAddObjectToObject(req, "body");
    if (body)
    {
      JAddNumberToObject(body, "temp", temperature);
      JAddNumberToObject(body, "humidity", humidity);
    }
    notecard.sendRequest(req);
  }

  delay(15000);

}
