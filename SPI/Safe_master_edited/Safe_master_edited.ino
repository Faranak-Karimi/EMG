/*
    SPI Safe Master Demo Sketch
    Connect the SPI Master device to the following pins on the esp8266:
    GPIO    NodeMCU   Name  |   Uno
   ===================================
     15       D8       SS   |   D10
     13       D7      MOSI  |   D11
     12       D6      MISO  |   D12
     14       D5      SCK   |   D13
    Note: If the ESP is booting at a moment when the SPI Master has the Select line HIGH (deselected)
    the ESP8266 WILL FAIL to boot!
    This sketch tries to go around this issue by only pulsing the Slave Select line to reset the command
    and keeping the line LOW all other time.
*/
#include <SPI.h>

size_t cnt = 0;
#define SPI2_NSS_PIN PB12   //SPI_2 Chip Select pin is PB12. You can change it to the STM32 pin you want.
#define SPI1_NSS_PIN PA15
SPIClass SPI_2(2); //Create an instance of the SPI Class called SPI_2 that uses the 2nd SPI Port

     uint8_t data2[32];

class ESPSafeMaster {
  private:
    uint8_t _ss_pin;
    void _pulseSS() {
      digitalWrite(_ss_pin, HIGH);
      delayMicroseconds(5);
      digitalWrite(_ss_pin, LOW);
    }
  public:
    ESPSafeMaster(uint8_t pin): _ss_pin(pin) {}
    void begin() {
      pinMode(_ss_pin, OUTPUT);
      _pulseSS();
    }

    uint32_t readStatus() {
      _pulseSS();
      SPI.transfer(0x04);
      uint32_t status = (SPI.transfer(0) | ((uint32_t)(SPI.transfer(0)) << 8) | ((uint32_t)(SPI.transfer(0)) << 16) | ((uint32_t)(SPI.transfer(0)) << 24));
      _pulseSS();
      return status;
    }

    void writeStatus(uint32_t status) {
      _pulseSS();
      SPI.transfer(0x01);
      SPI.transfer(status & 0xFF);
      SPI.transfer((status >> 8) & 0xFF);
      SPI.transfer((status >> 16) & 0xFF);
      SPI.transfer((status >> 24) & 0xFF);
      _pulseSS();
    }

    void readData(uint8_t * data) {
      _pulseSS();
      for (uint8_t i = 0; i < 256; i++) {
        if(i%32 == 0){
          SPI.transfer(0x03);
          SPI.transfer(0x00);
        //  delayMicroseconds(5);
          }
        data[i] = SPI.transfer(0);
      }
      _pulseSS();
    }

    void writeData(const uint8_t * data, size_t len, size_t s) {
      size_t i = 0;

 //     Serial.println();
//       Serial.write(data, len);
      _pulseSS();
       SPI.transfer(0x02);
       SPI.transfer(0x00);     
      while (len-- && i < 32) {
//        if(i%32 == 0){
//      SPI.transfer(0x02);
//      SPI.transfer(0x00);}
        //Serial.print(data[i+s]);
        SPI.transfer(data[s + i]);
   //     delayMicroseconds(5);
           i++;

     //   Serial.print(" , ");
//        Serial.println(i);
      }
      while (i++ < 32) {
        SPI.transfer(0);
      }
      Serial.println();
      _pulseSS();
    }

    String readData() {
      char data[33];
      data[32] = 0;
      readData((uint8_t *)data);
      return String(data);
    }

    void writeData(const char * data) {
      writeData((uint8_t *)data, strlen(data), 0);
    }
};

ESPSafeMaster esp(SS);

void send(const uint8_t * message,size_t len, size_t s) {
 // Serial.print("Master: ");
 
 // Serial.print(len);
  esp.writeData(message, len, s);
  delay(10);
// // Serial.print("Slave: ");
//  Serial.println(esp.readData());
//  Serial.println();
}


void send(const char * message) {
  Serial.print("Master: ");
 // Serial.println(message);
  esp.writeData(message);
  delay(1);
//  Serial.print("Slave: ");
 // Serial.println(esp.readData());
 // Serial.println();
}

void sendSPI2()
{
  digitalWrite(SPI2_NSS_PIN, LOW); // manually take CSN low for SPI_2 transmission
 // for(size_t j =0; j<32; j++){
      data2[0] = SPI_2.transfer(0x55); //Send the HEX data  0x55 over SPI-2 port and store the received byte to the <data> variable.
   // }
  digitalWrite(SPI2_NSS_PIN, HIGH); // manually take CSN high between spi transmissions
}


void sendSPI1()
{
  digitalWrite(SPI1_NSS_PIN, LOW); // manually take CSN low for SPI_2 transmission
 // for(size_t j =0; j<32; j++){
      data2[0] = SPI_2.transfer(0x55); //Send the HEX data  0x55 over SPI-2 port and store the received byte to the <data> variable.
   // }
  digitalWrite(SPI1_NSS_PIN, HIGH); // manually take CSN high between spi transmissions
}

     uint8_t arr[256];
     uint8_t arr2[32];
void setup() {
  Serial.begin(115200);
  for(size_t i=0; i<256; i++){
    arr[i]=i;
    }
//     for(size_t i=0; i<32; i++){
//    arr2[i]=i+32;
//    }  
   //  SPI1C2 |= 1 << SPIC2MISODM_S;
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV4);  // Use a different speed to SPI 1
  esp.begin();
  SPI_2.begin(); //Initialize the SPI_2 port.
  SPI_2.setBitOrder(MSBFIRST); // Set the SPI_2 bit order
  SPI_2.setDataMode(SPI_MODE0); //Set the  SPI_2 data mode 0
  SPI_2.setClockDivider(SPI_CLOCK_DIV4);  // Use a different speed to SPI 1
  pinMode(SPI2_NSS_PIN, OUTPUT);
  pinMode(SPI1_NSS_PIN, OUTPUT);

  delay(1000);
  //send("Hello Slave!");
}
size_t j = 0;
void loop() {
//  if(cnt<255)
//  cnt++;
//  else
//  cnt=0;
 // delay(300);
//  send(arr,32, 32*j);
//  if(j<7){
//   j++;}
 //  else{j =0;}
   

 // delay(100);
  sendSPI2();
    //delay(100);

  //Serial.println(data2[0]);
//  send(data2,32);
}
