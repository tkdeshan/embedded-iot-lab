#include <SPI.h>       // SPI library for communication
#include <nRF24L01.h>  // nRF24L01 register definitions
#include <RF24.h>      // RF24 library to simplify using the nRF24L01

// RF24 object with CE and CSN pins
RF24 radio(7, 8);  // CE, CSN

// 5-byte pipe address (must be the same as receiver)
const byte address[6] = "Node1";

void setup() {
  Serial.begin(9600);  

  // Initialize the radio
  if (!radio.begin()) {
    Serial.println("nRF24 Module initialization failed!");
    while (1)
      ;  // Stop if initialization fails
  }

  // Open a writing pipe with the defined address (used to send data)
  radio.openWritingPipe(address);

  // Set Power Amplifier level to minimum (reduces power usage, helps when modules are close)
  radio.setPALevel(RF24_PA_MIN);

  // Set data rate to 250kbps (slower but longer range and better reliability)
  radio.setDataRate(RF24_250KBPS);

  // Set the module in transmitting mode 
  radio.stopListening();

  Serial.println("Ready to transmit!");
}

void loop() {
  const char text[] = "Hello World";

  if (radio.write(&text, sizeof(text))) {
    Serial.println("Transmission successful");
  } else {
    Serial.println("Transmission failed");
  }

  delay(1000);
}
