/*

  openweather_multirequest_to_esp8266_servo.ino

  TOMA DATOS DE OPENWEATHER DE BUENOS AIRES, LA PAMPA Y TIERRA DEL FUEGO, FILTRO LOS JSON Y MUESTRA EN PANTALLA WIND Y TEMP DE CADA CIUDAD
  Actualizo posición de servos en base a datos de viento
  Envío los datos de temperatura de BA a Telegram

*/

//cambié lugar del servo_ba. verificar con los otros servos

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <Servo.h>
#include <WiFiClient.h>
#include <UniversalTelegramBot.h>

// Telegram BOT Token (Get from Botfather)
#define BOT_TOKEN "1820451195:AAGL9uopYm_K50lneWevr2cTg30QRS6n6aA"

const unsigned long BOT_MTBS = 1000; // mean time between scan messages

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime; // last time messages' scan has been done

#define CHAT_ID "65570042"


const int ledPin = LED_BUILTIN;
int ledStatus = 0;

//Creo objetos Servo para cada motor
Servo servo_ba, servo_lp, servo_tf;

//Asigno los pines del ESP8266 para cada motor
int servo_ba_pin = D1;
int servo_lp_pin = D2;
int servo_tf_pin = D3;

//Creo variables para ajustar el mapeo de los datos de viento y los ángulos del motor
int viento_min = 0;
int viento_max = 10;
int servo_min = 10;
int servo_max = 170;

/*
   Creo una variable inicial que se ejecuta en el setup.
   Esto es importante para que al iniciar la instalación arranquen en posición cero y evitar comportamientos erráticos que puedan dañar motores o elementos vinculados a los motores

*/
int pos_inicial = 0;
int timer_segs = 1 * 60 * 1000;

ESP8266WiFiMulti WiFiMulti;

const char* ssid = "FB912E";
const char* password = "100381192";

//Creo 6 variables globales, dos por cada ciudad

float main_temp_ba;
float wind_speed_ba;

float main_temp_lp;
float wind_speed_lp;

float main_temp_tf;
float wind_speed_tf;


void setup() {

  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  pinMode(ledPin, OUTPUT); // initialize digital ledPin as an output.
  delay(10);
  digitalWrite(ledPin, HIGH); // initialize pin as off (active LOW)


  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);
  configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
  secured_client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org


  //SERVOS
  servo_ba.attach(servo_ba_pin);
  servo_lp.attach(servo_lp_pin);
  servo_tf.attach(servo_tf_pin);

  servo_ba.write(pos_inicial);
  servo_lp.write(pos_inicial);
  servo_tf.write(pos_inicial);

  delay(100);

  servo_ba.detach();
  servo_lp.detach();
  servo_tf.detach();

  delay(2000);

}

void loop() {

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


    //SERVOS
    servo_ba.attach(servo_ba_pin);
    servo_lp.attach(servo_lp_pin);
    servo_tf.attach(servo_tf_pin);
    delay(100);

    // Actualizo servo_lp
    servo_ba.write(map((int)wind_speed_ba, viento_min, viento_max, servo_min, servo_max));
    //servo_ba.write(wind_speed_ba);

    if (main_temp_ba > 10) {
      String chat_temp_ba = (String)main_temp_ba;
      Serial.print("envio chat");
      bot.sendMessage(CHAT_ID, "Temperatura BA: " + chat_temp_ba + "ºC", "");
    }


    // Actualizo servo_lp
    servo_lp.write(map((int)wind_speed_lp, viento_min, viento_max, servo_min, servo_max));
    //servo_lp.write(constrain(wind_speed_lp, 0, 100));

    // Actualizo servo_tf
    servo_tf.write(map((int)wind_speed_tf, viento_min, viento_max, servo_min, servo_max));
    //servo_tf.write(constrain(wind_speed_tf, 0, 100));

    delay(1000);

    servo_ba.detach();
    servo_lp.detach();
    servo_tf.detach();

    //Hago una pausa de 2 minutos antes de volver a consultar la API
    delay(timer_segs);
  }
}
