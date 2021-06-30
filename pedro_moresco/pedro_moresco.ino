/*********************************************************
  This is a library for the MPR121 12-channel Capacitive touch sensor

  Designed specifically to work with the MPR121 Breakout in the Adafruit shop
  ----> https://www.adafruit.com/products/

  These sensors use I2C communicate, at least 2 pins are required
  to interface

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
**********************************************************/
#include "MedianFilterLib.h" //lib. filtro de mediana movil
int echo = 7;     // Pin para echo
int trigger = 4; // Pin para trigger
int control = 0;
int tiempoRespuesta;
int distancia = 0;
int distanciaAnterior = 0;
MedianFilter<int> medianFilter(20); // Inicia el filtro de mediana con una ventana de 20
#include <Wire.h>
#include "Adafruit_MPR121.h"
#include "MIDIUSB.h"
#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;



void setup() {
  Serial.begin(115200);

  pinMode(echo, INPUT_PULLUP);
  pinMode(trigger, OUTPUT);



  while (!Serial) { // needed to keep leonardo/micro from starting too fast!
    delay(10);
  }

  Serial.println("Adafruit MPR121 Capacitive Touch sensor test");

  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");

  cap.setThreshholds(100, 5);

}


void loop() {
  // Get the currently touched pads
  currtouched = cap.touched();

  //for (uint8_t i = 0; i < 12; i++) {
  // it if *is* touched and *wasnt* touched before, alert!
  if ((currtouched & _BV(0)) && !(lasttouched & _BV(0)) ) {
    Serial.print(0); Serial.println(" touched");
    noteOn(2, 48, 64);   // Channel 1, middle C, normal velocity
    MidiUSB.flush();
    delay(100);

  }
  // if it *was* touched and now *isnt*, alert!
  if (!(currtouched & _BV(0)) && (lasttouched & _BV(0)) ) {
    Serial.print(0); Serial.println(" released");
    noteOff(2, 48, 64);  // Channel 1, middle C, normal velocity
    MidiUSB.flush();
    delay(100);
  }

  if ((currtouched & _BV(1)) && !(lasttouched & _BV(1)) ) {
    Serial.print(1); Serial.println(" touched");
    noteOn(2, 49, 64);   // Channel 1, middle C, normal velocity
    MidiUSB.flush();
    delay(100);

  }
  // if it *was* touched and now *isnt*, alert!
  if (!(currtouched & _BV(1)) && (lasttouched & _BV(1)) ) {
    Serial.print(1); Serial.println(" released");
    noteOff(2, 49, 64);  // Channel 1, middle C, normal velocity
    MidiUSB.flush();
    delay(100);
  }

  if ((currtouched & _BV(2)) && !(lasttouched & _BV(2)) ) {
    Serial.print(2); Serial.println(" touched");
    noteOn(2, 50, 64);   // Channel 1, middle C, normal velocity
    MidiUSB.flush();
    delay(100);

  }
  // if it *was* touched and now *isnt*, alert!
  if (!(currtouched & _BV(2)) && (lasttouched & _BV(2)) ) {
    Serial.print(2); Serial.println(" released");
    noteOff(2, 50, 64);  // Channel 1, middle C, normal velocity
    MidiUSB.flush();
    delay(100);
  }

  if ((currtouched & _BV(3)) && !(lasttouched & _BV(3)) ) {
    Serial.print(3); Serial.println(" touched");
    noteOn(2, 51, 64);   // Channel 1, middle C, normal velocity
    MidiUSB.flush();
    delay(100);

  }
  // if it *was* touched and now *isnt*, alert!
  if (!(currtouched & _BV(3)) && (lasttouched & _BV(3)) ) {
    Serial.print(3); Serial.println(" released");
    noteOff(2, 51, 64);  // Channel 1, middle C, normal velocity
    MidiUSB.flush();
    delay(100);
  }

  if ((currtouched & _BV(4)) && !(lasttouched & _BV(4)) ) {
    Serial.print(4); Serial.println(" touched");
    noteOn(2, 52, 64);   // Channel 1, middle C, normal velocity
    MidiUSB.flush();
    delay(100);

  }
  // if it *was* touched and now *isnt*, alert!
  if (!(currtouched & _BV(4)) && (lasttouched & _BV(4)) ) {
    Serial.print(4); Serial.println(" released");
    noteOff(2, 52, 64);  // Channel 1, middle C, normal velocity
    MidiUSB.flush();
    delay(100);
  }

  if ((currtouched & _BV(5)) && !(lasttouched & _BV(5)) ) {
    Serial.print(5); Serial.println(" touched");
    noteOn(2, 53, 64);   // Channel 1, middle C, normal velocity
    MidiUSB.flush();
    delay(100);

  }
  // if it *was* touched and now *isnt*, alert!
  if (!(currtouched & _BV(5)) && (lasttouched & _BV(5)) ) {
    Serial.print(5); Serial.println(" released");
    noteOff(2, 53, 64);  // Channel 1, middle C, normal velocity
    MidiUSB.flush();
    delay(100);
  }

  if ((currtouched & _BV(6)) && !(lasttouched & _BV(6)) ) {
    Serial.print(6); Serial.println(" touched");
    noteOn(2, 54, 64);   // Channel 1, middle C, normal velocity
    MidiUSB.flush();
    delay(100);

  }
  // if it *was* touched and now *isnt*, alert!
  if (!(currtouched & _BV(6)) && (lasttouched & _BV(6)) ) {
    Serial.print(6); Serial.println(" released");
    noteOff(2, 54, 64);  // Channel 1, middle C, normal velocity
    MidiUSB.flush();
    delay(100);
  }

  if ((currtouched & _BV(7)) && !(lasttouched & _BV(7)) ) {
    Serial.print(7); Serial.println(" touched");
    noteOn(2, 55, 64);   // Channel 1, middle C, normal velocity
    MidiUSB.flush();
    delay(100);

  }
  // if it *was* touched and now *isnt*, alert!
  if (!(currtouched & _BV(7)) && (lasttouched & _BV(7)) ) {
    Serial.print(7); Serial.println(" released");
    noteOff(2, 55, 64);  // Channel 1, middle C, normal velocity
    MidiUSB.flush();
    delay(100);
  }

  if ((currtouched & _BV(8)) && !(lasttouched & _BV(8)) ) {
    Serial.print(8); Serial.println(" touched");
    noteOn(2, 56, 64);   // Channel 1, middle C, normal velocity
    MidiUSB.flush();
    delay(100);

  }
  // if it *was* touched and now *isnt*, alert!
  if (!(currtouched & _BV(8)) && (lasttouched & _BV(8)) ) {
    Serial.print(8); Serial.println(" released");
    noteOff(2, 56, 64);  // Channel 1, middle C, normal velocity
    MidiUSB.flush();
    delay(100);
  }




  //}

  // comment out this line for detailed data from the sensor!
  //return;


  // reset our state
  lasttouched = currtouched;

  // debugging info, what

  Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(cap.touched(), HEX);
  Serial.print("Filt: ");
  for (uint8_t i = 0; i < 12; i++) {
    Serial.print(cap.filteredData(i)); Serial.print("\t");
  }
  Serial.println();
  Serial.print("Base: ");
  for (uint8_t i = 0; i < 12; i++) {
    Serial.print(cap.baselineData(i)); Serial.print("\t");
  }
  Serial.println();

  // put a delay so it isn't overwhelming
  delay(100);


  /// DISTANCIA

  //se toman 20 muestras de la lectura de la distancia
  for (int i = 0; i < 2; i++) {
    medianFilter.AddValue(medir()); // Se agregan los valores analogicos al filtro de mediana movil
    delay(50);
  }

  distancia = medianFilter.GetFiltered(); //se filtra con la mediana
  Serial.print("SENSOR SR 04:    ");
  Serial.println(distancia);

  //discrimina para evitar errores
  if (distancia >= 10 && distancia <= 40 && distancia != distanciaAnterior) {

    int control = map(distancia, 10, 40, 0, 127); //escala el valor a un entero entre 0 y 127
    analogWrite(13, control); //genera un pwm en el led del pin 13 con un ancho de pulso proporcional a la distancia
    controlChange(0, 1, control); //usa la funcion de enviar cambios de control
    delay(10); //espera 10 ms
  }
  MidiUSB.flush(); //Refresca comunicacion USB HID MIDI
  distanciaAnterior = distancia;
  //FIN DISTANCIA


}

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}



//funcion general para mandar cambios de control

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

//funcion para medir la distancia de la mano al sensor en cm
int medir() {
  int x;
  digitalWrite(trigger, HIGH);            // Enviamos pulso de 10 microsegundos
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  tiempoRespuesta = pulseIn(echo, HIGH);  // Y esperamos pulso de vuelta
  x = tiempoRespuesta / 58;       // Calculo de distancia en cm
  Serial.println(x);
  return x;


}
