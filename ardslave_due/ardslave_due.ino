#include <SPI.h>
char buff [50];
volatile byte indx;
volatile boolean process;

void setup (void) {
   Serial.begin (115200);
pinMode(PIN_SPI_MISO,OUTPUT);
 REG_SPI0_MR = REG_SPI0_MR & 0xFF0F00B6;
 REG_SPI0_WPMR = REG_SPI0_WPMR & 0xFF0F00FE;
 
 REG_SPI0_CR=0x1;
 
 REG_SPI0_CSR=0x00000400; //Configured to 8bit transfer & 21MHz


 //SPI.setDataMode(SPI_MODE3);
  // pinMode(MISO, OUTPUT); // have to send on master in so it set as output
//   SPCR |= _BV(SPE); // turn on SPI in slave mode
   indx = 0; // buffer empty
   process = false;
   SPI.attachInterrupt(); // turn on interrupt
}

void loop (void) {
   if (process) {
      process = false; //reset the process
      Serial.println (buff); //print the array on serial monitor
      indx= 0; //reset button to zero
   }
}



ISR (SPI_STC_vect) // SPI interrupt routine 
{ 
   byte c = SPDR; // read byte from SPI Data Register
   if (indx < sizeof buff) {
      buff [indx++] = c; // save data in the next index in the array buff
      if (c == '\r') //check for the end of the word
      process = true;
   }
}
