

#include "SPISlave.h"

void setup()
{
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    Serial.println();

    // data has been received from the master. Beware that len is always 32
    // and the buffer is autofilled with zeroes if data is less than 32 bytes long
    // It's up to the user to implement protocol for handling data length
    SPISlave.onData([](uint8_t * data, size_t len) {
        String message = String((char *)data);
        char answer[33];
        if(message.equals("Hello Slave!")) {
            strcpy(answer, "Hello Master!");
        } else if(message.equals("Are you alive?")) {
            sprintf(answer, "Alive for %u seconds!", millis() / 1000);
        } else {
            strcpy(answer, "Say what?");
        }
        SPISlave.setData(answer);
        Serial.printf("Question: %s\Answer: %s\n", (char *)data, answer);
    });

    // The master has read out outgoing data buffer
    // that buffer can be set with SPISlave.setData
    SPISlave.onDataSent([]() {
        Serial.println("Answer Sent");
    });

    // status has been received from the master.
    // The status register is a special register that bot the slave and the master can write to and read from.
    // Can be used to exchange small data or status information
    SPISlave.onStatus([](uint32_t data) {
        Serial.printf("Status: %u\n", data);
        SPISlave.setStatus(millis()); //set next status
    });

    // The master has read the status register
    SPISlave.onStatusSent([]() {
        Serial.println("Status Sent");
    });

    // Setup SPI Slave registers and pins
    SPISlave.begin();

    // Additional setting to have MISO change on falling edge
    SPI1C2 |= 1 << SPIC2MISODM_S;

    // Set the status register (if the master reads it, it will read this value)
    SPISlave.setStatus(millis());

    // Sets the data registers. Limited to 32 bytes at a time.
    // SPISlave.setData(uint8_t * data, size_t len); is also available with the same limitation
    SPISlave.setData("Ask me a question!");
}

void loop() {}
