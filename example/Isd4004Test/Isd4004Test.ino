
#include <SPI.h>
#include <ISD4004T.h>

#define recordPin  13

/*    MOSI 23  ,SCLK 18     */
//ISD4004 voice(14, 22); //ss,int
ISD4004 voice(12, 34); //ss,int //ss,int  ESP32


void setup() {

  pinMode(recordPin, INPUT_PULLUP);
  voice.begin();
  Serial.begin(9600);
}

void loop() {

  if (!digitalRead(recordPin)){
    delay(20);
    Serial.println("Start record");
    voice.StartRecord(0);
    while (!digitalRead(recordPin));
    Serial.println("Stop record");
    voice.StopRecord();
    Serial.println("Start play");
    voice.PlayInt(0);
    Serial.println("Stop play");
  }
}
