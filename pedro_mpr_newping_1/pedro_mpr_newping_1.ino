
/*
   Este código:
   analiza 8 sensores del MPR y los asigna a las notas 49 a 56 con noteOn y noteOff
   recorre dos objetos newping y los mapea con controlChange
*/
#include <Wire.h>
#include "Adafruit_MPR121.h"
#include "MIDIUSB.h"
#include <NewPing.h>


#define SONAR_NUM 2      // Number of sensors.
#define MAX_DISTANCE 50 // Maximum distance (in cm) to ping.

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(4, 5, MAX_DISTANCE), // D1, D2 Each sensor's trigger pin, echo pin, and max distance to ping.
  NewPing(6, 7, MAX_DISTANCE) // D7, D6
};

#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

int notasMidi[] = {49, 50, 51, 52, 53, 54, 55, 56};

void setup() {
  Serial.begin(9600);

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
}

void loop() {

  currtouched = cap.touched();

  // MPR121
  for (uint8_t i = 0; i < sizeof(notasMidi) - 1; i++) {
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" touched");
      noteOn(2, notasMidi[i], 64);
    }

    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" released");
      noteOff(2, notasMidi[i], 64);
    }
  }

  // NewPING
  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through each sensor and display results.
    delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    Serial.print(i);
    Serial.print("=");
    Serial.print(sonar[i].ping_cm());
    Serial.print("cm ");

    int control = map(sonar[i].ping_cm(), 10, 40, 0, 127); //escala el valor a un entero entre 0 y 127
    controlChange(0, i, control); //usa la funcion de enviar cambios de control
    delay(10); //espera 10 ms
  }
  Serial.println();



  // reset our state
  lasttouched = currtouched;

  // comment out this line for detailed data from the sensor!
  return;

  // debugging info, what
  /*
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
  */
  MidiUSB.flush(); //Refresca comunicacion USB HID MIDI


  // put a delay so it isn't overwhelming
  delay(100);

}

// FUNCIONES MIDI

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
