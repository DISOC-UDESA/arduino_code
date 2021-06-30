#include <ThingerESP8266.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS     10000
#define REPORTING_TO_DEVICE     60000
#define LED_On_Period 100

int LED_PERIOD_MS = 0;

// PulseOximeter is the higher level interface to the sensor
// it offers:
//  * beat detection reporting
//  * heart rate calculation
//  * SpO2 (oxidation level) calculation
PulseOximeter pox;

uint32_t tsLastReport = 0;
uint32_t tsLastReportDevice = 0;
uint32_t tsLastLEDOn = 0;

#define LED13 13

#define USERNAME "Jazmin"
#define DEVICE_ID "Casa_Corazon_1"
#define DEVICE_CREDENTIAL "#S37!whoZBDdV1h4"

#define SSID "CLARO5"
#define SSID_PASSWORD "14602788"

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

int bpm_Mio;
int bpm_Externo;

// Callback (registered below) fired when a pulse is detected
void onBeatDetected()
{
  Serial.println("Beat!");
}

void setup()
{
  pinMode(LED13, OUTPUT);

  Serial.begin(115200);

  Serial.print("Initializing pulse oximeter..");

  if (!pox.begin()) {
    Serial.println("FAILED");
    for (;;);
  } else {
    Serial.println("SUCCESS");
  }

  pox.setOnBeatDetectedCallback(onBeatDetected);

  thing["Corazon_Externo"] << [](pson & in) {
    bpm_Externo = in["bpm_Mio"];
  };
  thing["Corazon_Mio"] >> [](pson & out) {
    out["bpm_Mio"] = bpm_Mio;
  };
}

void loop()
{
  // Make sure to call update as fast as possible
  pox.update();
  thing.handle();

  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    Serial.print("Heart rate:");
    Serial.print(bpm_Mio = pox.getHeartRate());
    Serial.print("bpm");

    tsLastReport = millis();

    Serial.println(LED_PERIOD_MS);

    if (bpm_Externo >= 1) {
      LED_PERIOD_MS = (60 / bpm_Externo) * 1000;
    } else {
      LED_PERIOD_MS = 0;
    }
  }
  if (millis() - tsLastReportDevice > REPORTING_TO_DEVICE)
  {
    thing.call_device("Casa_Corazon_2", "Corazon_Externo", thing["Corazon_Mio"]);
    tsLastReportDevice = millis();
  }
  if (millis() - tsLastLEDOn > LED_PERIOD_MS && LED_PERIOD_MS > 0)
  {
    PrendoLed();
    tsLastLEDOn = millis();
  }
  if (millis() - tsLastLEDOn > LED_On_Period && LED_PERIOD_MS > 0)
  {
    ApagoLed();
    tsLastLEDOn = millis();
  }
}

void PrendoLed() {
  digitalWrite(LED13, HIGH);
  Serial.println("prendiendo");

}

void ApagoLed() {
  digitalWrite(LED13, LOW);
}
