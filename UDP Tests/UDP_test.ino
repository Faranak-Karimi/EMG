
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <SPI.h>
WiFiUDP Udp;
#define localUdpPort 4210  // local port to listen on
byte sendPacket[11];
IPAddress remote;
int count = 0;

//int  DRDY = GPIO16 ;
void setup() {
  // put your setup code here, to run once:
ESP8266_config();
//ADS1298_config();
WifiConfig();
}

void loop() {
  // put your main code here, to run repeatedly:
 // delay(5);
 sendPacket[count] = SPI.transfer(0);
         
      sendPacket[count] = SPI.transfer(0);
         

  for (int i = 0 ; i < 3 ; i++) 
   {
      //Clock out each byte - 3x status bytes, plus 3x channel 1 bytes
  //    if(DRDY = 1)
 //     {
      sendPacket[count] = SPI.transfer(0);
      count++;      
      sendPacket[count] = SPI.transfer(0);
      count++;      
      sendPacket[count] = SPI.transfer(0);
      count++;      
   }

if (count >= 3)
{
    remote = Udp.remoteIP();
Udp.beginPacket(remote, localUdpPort);
      Udp.write(sendPacket,sizeof(sendPacket));
      Udp.endPacket();
      count = 0;
}

}
void ESP8266_config(void)
{
//Serial config:
Serial.begin(115200);
Serial.println();
Serial.println("________________________________________________________________");

//pin modes
/*pinMode(CS, OUTPUT);
pinMode(DRDY, INPUT);
pinMode(PDWN_RESET, OUTPUT);
*/
//SPI config:
SPI.begin();
SPI.beginTransaction(SPISettings(1000000,MSBFIRST, SPI_MODE1));
SPI.setBitOrder(MSBFIRST);
SPI.setDataMode(SPI_MODE1); //sets clock polaroty and phase 
}

byte WifiConfig(void)
{
  remote = Udp.remoteIP();
Serial.print("Setting up access point...");
Serial.print(remote);
const char *ssid = "Ap";
const char *password = "*srl*780#";
WiFiClient client;
client.setNoDelay(1);
WiFi.mode(WIFI_AP);
WiFi.softAP(ssid, password);
Udp.begin(localUdpPort);
Serial.printf("Success. Now listening at IP %s, UDP port %d\n", WiFi.softAPIP().toString().c_str(), localUdpPort);
}
