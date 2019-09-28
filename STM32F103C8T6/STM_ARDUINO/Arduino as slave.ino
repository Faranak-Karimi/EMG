//SPI Slave Code for Arduino
//SPI Communication between STM32F103C8 & Arduino
//Circuit Digest

#include<SPI.h>                           // Including Library for using SPI Communication
volatile boolean received;
volatile byte SlaveReceived,Slavesend;
volatile byte s [50];
int cnt = 0;
void setup()

{ 
  
  Serial.begin(112500);                     // Starts Serial Communication at Baud Rate 9600
  
  pinMode(MISO,OUTPUT);                   // Sets MISO as OUTPUT (Have to Send data to Master IN (STM32F103C8)
  pinMode(MOSI,INPUT);
  SPCR |= _BV(SPE);                       // Turn on SPI in Slave Mode
  received = false;
  SPI.attachInterrupt();                  // Interuupt ON is set for SPI commnucation
}

ISR (SPI_STC_vect)                        // Inerrrput routine function 
{
  
  //SlaveReceived = SPDR;                   // Value received from master STM32F103C8 is stored in variable slavereceived
  s[cnt] = SPDR;
  if(cnt<49)
  {
  cnt++;}
  else{cnt = 0;
     //Serial.write(s, 3);
          received = true;                        // Sets received as True 

      }

}

void loop()
{ 
//  int pot = analogRead(A0);               // Analog read the input pot value from analog pin A0
//  Slavesend = map(pot,0,1023,0,255);      // Converts the value pot (0-1023) to (0-255) for sending to master stm32 
                              
//  SPDR = 0x5a     ;                  // Sends the salvesend value to master STM32F103C8 via SPDR 
  if(received){
  Serial.println("Master STM32 to Slave Arduino");
  for(int i = 0; i <= 49; i++)
  {
  Serial.print(s[i]);                   // Puts the received value from Master STM32F103C8 at Serial Monitor                          
  Serial.print(",");                   // Puts the received value from Master STM32F103C8 at Serial Monitor                           
  //  delay(500);
  }
  Serial.println("done");
  received = false;
  delay(350);}
}//SPI Slave Code for Arduino
//SPI Communication between STM32F103C8 & Arduino
//Circuit Digest
