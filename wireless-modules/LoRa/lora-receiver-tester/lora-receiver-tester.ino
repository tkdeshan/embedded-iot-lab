#include <SPI.h>
#include <LoRa.h>

// 3.3V 3.3V
// GND GND
// MOSI 23
// MISO 19
// SCK 18
// RST 14
// NSS 5
// DI00 2

#define SS 5
#define RST 14
#define DIO0 2

void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;

  Serial.println("LoRa Receiver - ESP32");

  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1)
      ;
  }
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}
