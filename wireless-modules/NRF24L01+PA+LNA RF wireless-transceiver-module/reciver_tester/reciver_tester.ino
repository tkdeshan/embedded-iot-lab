#include <SPI.h>       // SPI library for communication
#include <nRF24L01.h>  // nRF24L01 register definitions
#include <RF24.h>      // RF24 library to simplify using the nRF24L01

// RF24 object with CE and CSN pins
RF24 radio(2, 4);  // CE, CSN

// 5-byte pipe address (must be the same as in the transmitter)
const byte address[6] = "Node1";

void setup() {
  Serial.begin(9600);

  // Initialize the radio
  if (!radio.begin()) {
    Serial.println("nRF24 Module initialization failed!");
    while (1)
      ;  // Stop if initialization fails
  }

  // Open a reading pipe with the defined address
  radio.openReadingPipe(0, address);

  // Set Power Amplifier level to minimum (to reduce power usage and noise)
  radio.setPALevel(RF24_PA_MIN);

  // Set the data rate to 250kbps (better range and stability)
  radio.setDataRate(RF24_250KBPS);

  // Start listening for incoming messages
  radio.startListening();

  Serial.println("Ready to receive!");
}

void loop() {
  if (radio.available()) {
    char text[32] = "";  // Buffer to store the incoming message

    // Read the received message into the buffer
    radio.read(&text, sizeof(text));

    Serial.print("Received: ");
    Serial.println(text);
  }
}
