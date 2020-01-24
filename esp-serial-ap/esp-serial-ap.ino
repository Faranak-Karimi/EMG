#include <ESP8266WiFi.h>
//#include <WifiClient.h>
//#include <ESP8266WiFi.h>
//#include <RCSwitch.h>
//#include <IRremoteESP8266.h>

// NETWORK: Static IP details...
IPAddress ip(192, 168, 100, 10);
IPAddress gateway(192, 168, 100, 1);
IPAddress subnet(255, 255, 255, 0);

uint8_t buff[27];
volatile byte indx;
int temp = 0;
int temp1 = 0;
int temp2 = 0;
volatile boolean process;
volatile boolean checked = 0;
volatile boolean closed = 0;

const char* ssid = "Ap";
const char* password =  "*srl*780#";
 
//const uint16_t port =8090;// 65100; //
//const char * host ="192.168.43.42"; //"192.168.100.10";
//

//WiFiClient tcpclient;
WiFiServer tcpserver(65100 );
/*void tcpconnection(const uint16_t port, const char* host)
{

unsigned int ret = tcpclient.connect(host, port);
    if (!ret) {
      process = 0;
       // while(!tcpclient.connect(host, port)){
       // Serial.println("Connection to host failed");
        Serial.print('H');
        delay(1000);
        return;
       // }
    }
 
 
else if (ret) {
  // Serial.println("Connected to server successfuly!");
   // tcpclient.print("Hello from ESP8266!");
    process = 1;
    Serial.print('G');
}
}*/
void setup()
{
  
  Serial.begin(460800);
  WiFi.mode(WIFI_STA);
  // Static IP Setup Info Here...
WiFi.config(ip, gateway, subnet);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
//    Serial.println("...");
  }

//
//Serial.print("Connected to "); Serial.println(ssid);
//  Serial.print("IP Address: "); Serial.println(WiFi.localIP());
//  Serial.print("IP Address: "); Serial.println(WiFi.localIP());
//  Serial.println(ip);
 
  // Start the TCP server
  tcpserver.begin();

 //tcpconnection(port, host);
 // Serial.print("WiFi connected with IP: ");
 // Serial.println(WiFi.localIP());

}
void loop()
{

  WiFiClient tcpclient = tcpserver.available();
  tcpclient.setNoDelay(true); // does not do much if anything
  /*
if (tcpclient.connected())
{
  Serial.print("Hi");
while (Serial.available()) {
  buff[indx++] = Serial.read();
 
 if(indx == 4)
 {
        tcpserver.write(buff, sizeof(buff));
        indx = 0;
      }
//    }
//  }*/
  while (tcpclient.connected())
    { 
//    Serial.print("hello");
     if(!checked)
     {
     if(tcpclient.available())
     {
       temp = tcpclient.read();
//      Serial.write(temp);
     
      
      if(temp == 'G')
    {  
        tcpclient.write('G');
         Serial.print('G');
        checked = 1;
     }
     }
    }
     else
     {

         if(tcpclient.available())
          {
          temp = tcpclient.read();
            if(temp == 'G')
            { 
              Serial.print('G');
              // tcpserver.write('G');
              checked = 0;
               }
                   }
         while (Serial.available() && checked ) {

           temp1 = Serial.read();
           temp2 = Serial.read();
           if (temp1 == 0x48 && temp2 == 0x49)
           {
            buff[indx++] = temp1;
            buff[indx++] = temp2;
            
           while(indx != 27)
           {
           buff[indx++] = Serial.read();
           }
           if(indx == 27 && !tcpclient.available())
            {
                                 
               tcpclient.write(buff, sizeof(buff));
               indx = 0;
//               delay(10);
               }
           
           }
         }
      }
         }
    

    
    
  //  Serial.println("Client disconnected.");
//    delay(1000);
 //   tcpclient.stop();
  }

     
     

/*else
{
  tcpconnection(port, host);
}*/
   
