#include <CapacitiveSensor.h>
#include <Volume.h>
#include "pitches.h"

#define SEND_PIN  4
#define RECV_PIN  6
#define SAMPLES   30

// Za svaku grafiku treba postaviti notu i prag (podraz. vr: 100)
#define NOTE      NOTE_AS4
#define THRESHOLD 100

#define VOL_LO    0
#define VOL_HI    255
#define VOL_INC   2
#define DELAY_MS  1

CapacitiveSensor sensor = CapacitiveSensor(SEND_PIN, RECV_PIN);

Volume speaker;  // pin 5
int volume = 0;

void setup() {
    // sensor.set_CS_AutocaL_Millis(0xFFFFFFFF);
    speaker.begin();
    Serial.begin(9600);
}

void loop() {
    long value = sensor.capacitiveSensor(SAMPLES);
    Serial.println(value);

    if (value >= THRESHOLD) {
        volume = constrain(volume+VOL_INC, VOL_LO, VOL_HI);
        speaker.tone(NOTE, volume);
    } else {
        volume = constrain(volume-VOL_INC, VOL_LO, VOL_HI);
        if (volume > VOL_LO) {
            speaker.tone(NOTE, volume);
        } else {
            speaker.noTone();
        }
    }

    speaker.delay(DELAY_MS);
}
