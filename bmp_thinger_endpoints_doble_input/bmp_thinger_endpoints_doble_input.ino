#define _DEBUG_

#include <ThingerESP8266.h>
#include <Arduino.h>
#include <Wire.h>
#include <BMx280I2C.h>


#define USERNAME "cristianreynaga"
#define DEVICE_ID "wemos"
#define DEVICE_CREDENTIAL "ewOWjL0GdSn@JD"

#define SSID "FB912E"
#define SSID_PASSWORD "100381192"

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

#define I2C_ADDRESS 0x77
BMx280I2C bmx280(I2C_ADDRESS);

#define LED 2
#define MaxTemp 15

void setup() {
  Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);


  Wire.begin();
  if (!bmx280.begin())
  {
    while (1);
  }
  bmx280.resetToDefaults();
  bmx280.writeOversamplingPressure(BMx280MI::OSRS_P_x16);
  bmx280.writeOversamplingTemperature(BMx280MI::OSRS_T_x16);

  thing.add_wifi(SSID, SSID_PASSWORD);


//  thing["presion"] >> outputValue(bmx280.getPressure());
//  thing["temperatura"] >> outputValue(bmx280.getTemperature());

 thing["BMP"] >> [](pson& out){
    out["temperatura"] = random(0, 100);
    out["presion"] = random(400, 500);
  };

    thing["led"] << digitalPin(LED_BUILTIN);


}

void loop() {
  thing.handle();
  bmx280.measure();
//  Serial.print("Temperatura: "); Serial.println(bmx280.getTemperature());
//  Serial.print("Presión: "); Serial.println(bmx280.getPressure());

  



}
