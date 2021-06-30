/*

  TOMA DATOS DE OPENWEATHER DE BUENOS AIRES, LA PAMPA Y TIERRA DEL FUEGO, FILTRO LOS JSON Y MUESTRA EN PANTALLA WIND Y TEMP DE CADA CIUDAD

*/

#include <Arduino.h>
#include <ArduinoJson.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

#include <Servo.h>
Servo myservo;  // POR AHORA NO LO ESTOY USANDO


ESP8266WiFiMulti WiFiMulti;

const char* ssid = "FB912E";
const char* password = "100381192";

float main_temp_ba;
float wind_speed_ba;

float main_temp_lp;
float wind_speed_lp;

float main_temp_tf;
float wind_speed_tf;

void setup() {

  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  myservo.attach(2);  // attaches the servo on GIO2 to the servo object

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

  int pos; // DEL SERVO PERO SIN USO

  // wait for WiFi connection

  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;

    HTTPClient http;

    // CONECTO A ENDPOINT CON DATOS DE BUENOS AIRES
    //Serial.print("[HTTP] begin...\n");
    if (http.begin(client, "http://api.openweathermap.org/data/2.5/weather?id=3433955&units=metric&appid=b5250fb182e9500fd875d0e9865772df")) {

      //Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        // Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String input = http.getString();
          // Serial.print("los datos son:::  ");
          // Serial.println(input);

          //PARSE JSON

          StaticJsonDocument<64> filter;
          filter["main"]["temp"] = true;
          filter["wind"]["speed"] = true;

          StaticJsonDocument<128> doc;

          DeserializationError error = deserializeJson(doc, input, DeserializationOption::Filter(filter));

          if (error) {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
            return;
          }

          main_temp_ba = doc["main"]["temp"]; // 7.28
          wind_speed_ba = doc["wind"]["speed"]; // 5.14

          Serial.println("BUENOS AIRES:   ");
          Serial.print("Temperatura: ");
          Serial.println(main_temp_ba);
          Serial.print("Viento: ");
          Serial.println(wind_speed_ba);

        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: % s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP] Unable to connect\n");
    }
    //myservo.write((int)wind_speed_ba);


    // LA PAMPA
    //Serial.print("[HTTP] begin...\n");
    if (http.begin(client, "http://api.openweathermap.org/data/2.5/weather?id=3849574&units=metric&appid=b5250fb182e9500fd875d0e9865772df")) {  // HTTP

      //Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        // Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String input = http.getString();
          // Serial.print("los datos son:::  ");
          // Serial.println(input);

          //PARSE JSON
          // Stream& input;

          StaticJsonDocument<64> filter;
          filter["main"]["temp"] = true;
          filter["wind"]["speed"] = true;

          StaticJsonDocument<128> doc;

          DeserializationError error = deserializeJson(doc, input, DeserializationOption::Filter(filter));

          if (error) {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
            return;
          }

          main_temp_lp = doc["main"]["temp"]; // 7.28
          wind_speed_lp = doc["wind"]["speed"]; // 5.14

          Serial.println("LA PAMPA:   ");
          Serial.print("Temperatura: ");
          Serial.println(main_temp_lp);
          Serial.print("Viento: ");
          Serial.println(wind_speed_lp);

        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: % s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP] Unable to connect\n");
    }
    //myservo.write((int)wind_speed_lp);

    // TIERRA DEL FUEGO
    //Serial.print("[HTTP] begin...\n");
    if (http.begin(client, "http://api.openweathermap.org/data/2.5/weather?id=3834450&units=metric&appid=b5250fb182e9500fd875d0e9865772df")) {  // HTTP

      //Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        // Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String input = http.getString();
          // Serial.print("los datos son:::  ");
          // Serial.println(input);

          //PARSE JSON
          // Stream& input;

          StaticJsonDocument<64> filter;
          filter["main"]["temp"] = true;
          filter["wind"]["speed"] = true;

          StaticJsonDocument<128> doc;

          DeserializationError error = deserializeJson(doc, input, DeserializationOption::Filter(filter));

          if (error) {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
            return;
          }

          main_temp_tf = doc["main"]["temp"]; // 7.28
          wind_speed_tf = doc["wind"]["speed"]; // 5.14

          Serial.println("TIERRA DEL FUEGO:   ");
          Serial.print("Temperatura: ");
          Serial.println(main_temp_tf);
          Serial.print("Viento: ");
          Serial.println(wind_speed_tf);

        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: % s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP] Unable to connect\n");
    }
    //myservo.write((int)wind_speed_tf);

    delay(10000);

  }
}
