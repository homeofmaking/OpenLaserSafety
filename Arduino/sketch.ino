#include <SoftwareSerial.h>

#define MYPORT_TX D1
#define MYPORT_RX D2

SoftwareSerial myPort;


void setup() {
  Serial.begin(9200);
  myPort.begin(9200, SWSERIAL_8N1, MYPORT_RX, MYPORT_TX, false);
  pinMode(D5, INPUT);
}


void loop() {
  while (myPort.available() > 0) {
    Serial.write(myPort.read());
    yield();
  }
}
