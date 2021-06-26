/*

  TOMA DATOS DE DWEET Y MUESTRA EN PANTALLA
  
*/

#include <Arduino.h>
#include <ArduinoJson.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;

const char* ssid = "+CODE";
const char* password = "pluscodepass";

void setup() {

  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);

}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;

    HTTPClient http;

    //Serial.print("[HTTP] begin...\n");
    if (http.begin(client, "http://dweet.io/get/latest/dweet/for/wemos_ortuzar")) {  // HTTP


      //Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        // Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          // Serial.print("los datos son:::  ");
          //Serial.println(payload);

          //Parse JSON
          // Stream& input;

          StaticJsonDocument<384> doc;

          DeserializationError error = deserializeJson(doc, payload);

          if (error) {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
            return;
          }

          const char* _this = doc["this"]; // "succeeded"
          const char* by = doc["by"]; // "getting"
          const char* the = doc["the"]; // "dweets"

          JsonObject with_0 = doc["with"][0];
          const char* with_0_thing = with_0["thing"]; // "wemos_ortuzar"
          const char* with_0_created = with_0["created"]; // "2021-05-30T04:57:37.921Z"

          int with_0_content_light = with_0["content"]["light"]; // 238

          Serial.println(with_0_content_light);


        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: % s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP] Unable to connect\n");
    }
  }

  delay(10000);
}
