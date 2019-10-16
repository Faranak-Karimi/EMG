#include <ESP8266WiFi.h>
// #include <SPI.h>
 #include "SPISlave.h"
// int buffsize = 32;
 size_t kb_cnt = 0;
 size_t Mb_cnt = 0;
 uint8_t buff[256] ;
 
volatile byte indx;
volatile boolean process = false;

const char* ssid = "Ap";
const char* password =  "*srl*780#";
 
const uint16_t port = 8090;
const char * host = "192.168.43.42";

WiFiClient tcpclient;
 
void tcpconnection(const uint16_t port, const char* host)
{

unsigned int ret = tcpclient.connect(host, port);
    if (!ret) {
       // while(!tcpclient.connect(host, port)){
        Serial.println("Connection to host failed");
 
        delay(1000);
        return;
       // }
    }
 
 
else if (ret) {
  // tcpclient.setNoDelay(1);
   Serial.println("Connected to server successfuly!");
    tcpclient.print("Hello from ESP8266!");
}
}


void setup()
{
   Serial.begin(115200);


    WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
 }
  
   Serial.print("WiFi connected with IP: ");
   Serial.println(WiFi.localIP());
   SPISlave.begin();
  // SPI1C2 |= 1 << SPIC2MISODM_S;

 
  
 SPISlave.onData([](uint8_t * data, size_t len)  {

//  Serial.print(len);
 for(int i=0; i<32;i++) {
      
      buff [kb_cnt++] = data[i]; // save data in the next index in the array buff
      if(kb_cnt == 256)
      {
        kb_cnt = 0;
   //     Mb_cnt += 1;
        process = true;
      }
      }
      
    });


tcpconnection(port, host);
}

void loop()
{
   
 /* const unsigned char data[] = {
    0xA1, 0xB2, 0xC3, 0x0E,
    0x05, 0x06, 0x07, 0x08,
    0x09, 0x10, 0x11, 0x12,
    0x13, 0x14, 0x15, 0xDD,
    0x17
  };
*/
if (tcpclient.connected())
{
if (process) {

   process = false; //reset the process
 /*
   // Serial.println("i'm in process");
  
   // uint8_t dbuf[32];
 //   memcpy(dbuf, buff, 32);*/

   for(int i = 0; i < 256; i++){
      Serial.print (buff[i]); //print the array on serial monitor
      Serial.print(" , ");
      }
      
      Serial.println("done");
     
    tcpclient.write(buff,sizeof(buff));
     
     }
     
}

else
{
  tcpconnection(port, host);
}

  //tcpclient.stop();

   // delay(500);
}
   
