#include <ThingerESP8266.h>


#define USERNAME "cristianreynaga"
#define DEVICE_ID "wemos"
#define DEVICE_CREDENTIAL "ewOWjL0GdSn@JD"

#define SSID "FB912E"
#define SSID_PASSWORD "100381192"
ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  thing.add_wifi(SSID, SSID_PASSWORD);

  // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
  thing["led"] << digitalPin(LED_BUILTIN);

  // resource output example (i.e. reading a sensor value)
  thing["millis"] >> outputValue(millis());

  thing["dummy_sensor"] >> [](pson& out){
    out["temperatura"] = random(0, 100);
    out["presion"] = random(400, 500);
  };

  // more details at http://docs.thinger.io/arduino/
}

void loop() {
  thing.handle();
}
