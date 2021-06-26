/*

  TOMA DATOS DE AQI Y MUESTRA EN PANTALLA PM10 y PM25

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
    if (http.begin(client, "http://api.waqi.info/feed/buenosaires/?token=c0f82fbb51bfcd405d16ecd118dbc5ab1e8d5014")) {  // HTTP

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
          Serial.print("los datos son:::  ");
          Serial.println(payload);

          //PARSE JSON
          // Stream& input;

          // Stream& input;

          StaticJsonDocument<96> filter;

          JsonObject filter_data_iaqi = filter["data"].createNestedObject("iaqi");
          filter_data_iaqi["pm10"]["v"] = true;
          filter_data_iaqi["pm25"]["v"] = true;

          StaticJsonDocument<192> doc;

          DeserializationError error = deserializeJson(doc, payload, DeserializationOption::Filter(filter));

          if (error) {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
            return;
          }

          int data_iaqi_pm10_v = doc["data"]["iaqi"]["pm10"]["v"]; // 21

          int data_iaqi_pm25_v = doc["data"]["iaqi"]["pm25"]["v"]; // 59


          Serial.println(data_iaqi_pm10_v);
          Serial.println(data_iaqi_pm25_v);

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
