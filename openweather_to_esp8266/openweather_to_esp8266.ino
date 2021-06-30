/*

<<<<<<< HEAD
  TOMA DATOS DE AQI Y MUESTRA EN PANTALLA PM10 y PM25
=======
  TOMA DATOS DE OPENWEATHER Y MUESTRA EN PANTALLA WIND Y TEMP
>>>>>>> c46534796480ea82f220fddd0843a1ab63ae36ec

*/

#include <Arduino.h>
#include <ArduinoJson.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;

<<<<<<< HEAD
const char* ssid = "+CODE";
const char* password = "pluscodepass";
=======
const char* ssid = "FB912E";
const char* password = "100381192";
>>>>>>> c46534796480ea82f220fddd0843a1ab63ae36ec

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
    if (http.begin(client, "http://api.openweathermap.org/data/2.5/weather?id=3433955&units=metric&appid=b5250fb182e9500fd875d0e9865772df")) {  // HTTP

      //Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        // Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
<<<<<<< HEAD
          String payload = http.getString();
          Serial.print("los datos son:::  ");
          Serial.println(payload);
=======
          String input = http.getString();
          Serial.print("los datos son:::  ");
          Serial.println(input);
>>>>>>> c46534796480ea82f220fddd0843a1ab63ae36ec

          //PARSE JSON
          // Stream& input;


<<<<<<< HEAD
          StaticJsonDocument<1024> doc;

          DeserializationError error = deserializeJson(doc, payload);
=======
          StaticJsonDocument<64> filter;
          filter["main"]["temp"] = true;
          filter["wind"]["speed"] = true;

          StaticJsonDocument<128> doc;

          DeserializationError error = deserializeJson(doc, input, DeserializationOption::Filter(filter));
>>>>>>> c46534796480ea82f220fddd0843a1ab63ae36ec

          if (error) {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
            return;
          }

<<<<<<< HEAD
          float coord_lon = doc["coord"]["lon"]; // -58.45
          float coord_lat = doc["coord"]["lat"]; // -34.6

          JsonObject weather_0 = doc["weather"][0];
          int weather_0_id = weather_0["id"]; // 300
          const char* weather_0_main = weather_0["main"]; // "Drizzle"
          const char* weather_0_description = weather_0["description"]; // "light intensity drizzle"
          const char* weather_0_icon = weather_0["icon"]; // "09d"

          const char* base = doc["base"]; // "stations"

          JsonObject main = doc["main"];
          float main_temp = main["temp"]; // 9.3
          float main_feels_like = main["feels_like"]; // 8.56
          float main_temp_min = main["temp_min"]; // 7.75
          float main_temp_max = main["temp_max"]; // 10.62
          int main_pressure = main["pressure"]; // 1016
          int main_humidity = main["humidity"]; // 78

          int visibility = doc["visibility"]; // 9000

          JsonObject wind = doc["wind"];
          float wind_speed = wind["speed"]; // 1.79
          int wind_deg = wind["deg"]; // 248
          float wind_gust = wind["gust"]; // 4.02

          int clouds_all = doc["clouds"]["all"]; // 90

          long dt = doc["dt"]; // 1624740345

          JsonObject sys = doc["sys"];
          int sys_type = sys["type"]; // 2
          long sys_id = sys["id"]; // 2031595
          const char* sys_country = sys["country"]; // "AR"
          long sys_sunrise = sys["sunrise"]; // 1624705279
          long sys_sunset = sys["sunset"]; // 1624740714

          int timezone = doc["timezone"]; // -10800
          long id = doc["id"]; // 3433955
          const char* name = doc["name"]; // "Buenos Aires F.D."
          int cod = doc["cod"]; // 200

  
=======
          float main_temp = doc["main"]["temp"]; // 7.28

          float wind_speed = doc["wind"]["speed"]; // 5.14
>>>>>>> c46534796480ea82f220fddd0843a1ab63ae36ec



          Serial.println(main_temp);
          Serial.println(wind_speed);

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
