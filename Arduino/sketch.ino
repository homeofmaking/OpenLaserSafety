#include <SoftwareSerial.h>

#define MYPORT_TX 14
#define MYPORT_RX 12

SoftwareSerial myPort;


void setup() {
  Serial.begin(9200);
  myPort.begin(9200, SWSERIAL_8N1, MYPORT_RX, MYPORT_TX, false);
}


void loop() {
  Serial.println("Loop");
  Serial.println(myPort.readString());
  delay(300);
}
