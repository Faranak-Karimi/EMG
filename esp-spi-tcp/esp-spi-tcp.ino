#include <ESP8266WiFi.h>
 #include <SPI.h>
 #include "SPISlave.h"
uint8_t buff [50];
volatile byte indx;
volatile boolean process;

const char* ssid = "Ap";
const char* password =  "*srl*780#";
 
const uint16_t port = 8090;
const char * host = "192.168.43.42";


void setup()
{
  
 
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }

     Serial.begin (115200);
 //  SPI.setDataMode(SPI_MODE3);
   //pinMode(MISO, OUTPUT); // have to send on master in so it set as output
 //  SPCR |= _BV(SPE); // turn on SPI in slave mode
   indx = 0; // buffer empty
   process = false;
  // SPI.attachInterrupt(); // turn on interrupt
 
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());


     SPISlave.onData([](uint8_t * data, size_t len)  {
 while (indx < len) {
      buff [indx++] = data[indx++]; // save data in the next index in the array buff
 }
//if (process) {
    process = true; //reset the process
//     Serial.println (data); //print the array on serial monitor
  //     tcpclient.write(data, sizeof(data));
     indx= 0; //reset button to zero
  // }
 

    });
       

    SPISlave.begin();
   SPI1C2 |= 1 << SPIC2MISODM_S;

 
}
/*
ISR (SPI_STC_vect) // SPI interrupt routine 
{ 
   byte c = SPDR; // read byte from SPI Data Register
   if (indx < sizeof buff) {
      buff [indx++] = c; // save data in the next index in the array buff
   }
     else
     {
      process = true;
   }
}
 */
void loop()
{
   
  WiFiClient tcpclient;
unsigned int ret = tcpclient.connect(host, port);
    if (!ret) {
 
        Serial.println("Connection to host failed");
 
        delay(1000);
        return;
    }
 
   
else if (ret) {
   Serial.println("Connected to server successful!");
 
  //  tcpclient.print("Hello from ESP8266!");
    
 /* const unsigned char data[] = {
    0xA1, 0xB2, 0xC3, 0x0E,
    0x05, 0x06, 0x07, 0x08,
    0x09, 0x10, 0x11, 0x12,
    0x13, 0x14, 0x15, 0xDD,
    0x17
  };
*/
if (process) {
    process = false; //reset the process
      //Serial.println (data); //print the array on serial monitor
       tcpclient.write(buff, sizeof(buff));
     // indx= 0; //reset button to zero
  }

}
    tcpclient.stop();
 
    delay(10000);
   
}
