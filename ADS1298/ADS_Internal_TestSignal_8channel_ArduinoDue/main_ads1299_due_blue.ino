 #include "ads1298.h"
#include "adsCMD.h"
#include <SPI.h>  // include the SPI library:
int gMaxChan = 0;
int IDval = 0; //Device ID : lower 5 bits of  ID Control Register 
int RegVal = 0;
int j = 0 ; 
const int kPIN_LED = 13;//pin with light - typically 13. Only flashes if error status. n.b. on Teensy3, pin 13 is ALSO spi clock!
boolean isRDATAC = false;
long int t = 0;
char check_buf[3];

void sendOsc(void) { 
  if (digitalRead(IPIN_DRDY) == HIGH) return; 
  unsigned char serialBytes[27];  
  int i = 0;
  digitalWrite(IPIN_CS, LOW);
  delayMicroseconds(1); 
  serialBytes[i++]= SPI.transfer(0); //skip 1nd byte of header // EZAF SHOD
  serialBytes[i++]= SPI.transfer(0); //skip 2nd byte of header
  serialBytes[i++]= SPI.transfer(0); //skip 3rd byte of header
  for (int ch = 1; ch <= 8; ch++) {
    serialBytes[i++]= SPI.transfer(0);//delayMicroseconds(3); 
    serialBytes[i++]= SPI.transfer(0);//delayMicroseconds(3); 
    serialBytes[i++]= SPI.transfer(0);//delayMicroseconds(3); 
  }
  delayMicroseconds(1); 
  digitalWrite(IPIN_CS, HIGH);
  //SerialUSB.write(check_buf, 3);
  Serial2.write(serialBytes, 27);
}

void adsSetup() { 
    using namespace ADS1298;
    /************************  GPIO Register  ************************/
    // GPIO
    RegVal = adc_rreg(GPIO);
    Serial.print("\n\n******* GPIO configurations ******* \nGPIO Register was: \t\t");
    Serial.println(RegVal, BIN);
    adc_wreg(GPIO, 0x00); // 0
    RegVal = adc_rreg(GPIO);
    Serial.print("GPIO Register set to: \t\t");
    Serial.println(RegVal, BIN);

    /************************  Config1 Register  ************************/
    //DAISY - CLK - Data Rate
    RegVal = adc_rreg(CONFIG1);
    Serial.print("\n\n******* Config1 configurations ******* \nConfig1 Register was: \t\t");
    Serial.println(RegVal, BIN);
    adc_wreg(CONFIG1, 0x86);  // 95 500 sps
    RegVal = adc_rreg(CONFIG1);
    Serial.print("Config1 Register set to: \t");
    Serial.println(RegVal, BIN);

    /************************  Config2 Register  ************************/
    //TEST Source - TEST Amplitude - TEST Fequency
    RegVal = adc_rreg(CONFIG2);
    Serial.print("\n\n******* Config2 configurations ******* \nConfig2 Register was: \t\t");
    Serial.println(RegVal, BIN);
    adc_wreg(CONFIG2, 0x15);
    RegVal = adc_rreg(CONFIG2);
    Serial.print("Config2 Register set to: \t");
    Serial.println(RegVal, BIN);

    adc_wreg(PACE, 0x00);

    /************************  Config3 Register  ************************/
    // Reference Buffer - BIAS Measurement - BIASREF Signal - BIAS Buffer - BIAS Sense Function - BIAS Lead_off Status
    RegVal = adc_rreg(CONFIG3);
    Serial.print("\n\n******* Config3 configurations ******* \nConfig3 Register was: \t\t");
    Serial.println(RegVal, BIN);
    adc_wreg(CONFIG3, 0xC4);//0xE0); // 60 /////////////////////ine moshkeeeeeeeeeeeeellllllllllllllllll
    RegVal = adc_rreg(CONFIG3);
    Serial.print("Config3 Register set to: \t");
    Serial.println(RegVal, BIN);

    /************************  Miscellaneous 1 Register  ************************/
   // adc_wreg(0x15, 0x20);
    /************************  bias Register  ************************/
  //  adc_wreg(0x0D, 0x0F);
    
    /************************  Channels' Registers  ************************/
    Serial.print("\n\n******* Channel configurations *******");
    adc_wreg(CHnSET + 1,  0x65);

    for (int i = 2; i <= 8; ++i) {
      RegVal = adc_rreg(CHnSET + i);
      Serial.print("\nChannel ");Serial.print(i);Serial.print(" Register was: \t\t");
      Serial.println(RegVal, BIN);
      adc_wreg(CHnSET + i,  0x65); //create square wave
      RegVal = adc_rreg(CHnSET + i);
      Serial.print("\nChannel ");Serial.print(i);Serial.print(" Register set to: \t\t");
      Serial.println(RegVal, BIN);
  	}
  	Serial.print("\n\n+++++++++++++++++ ADS SETUP COMPELETED!! +++++++++++++++++\n");
//digitalWrite(PIN_START, HIGH);
}

void setup(){

    using namespace ADS1298;
    /************************  Pin configurations  ************************/
    //pinMode(PIN_SCLK, OUTPUT); //optional - SPI library will do this for us
    //pinMode(PIN_DIN, OUTPUT); //optional - SPI library will do this for us
    //pinMode(PIN_DOUT, INPUT); //optional - SPI library will do this for us
    pinMode(IPIN_CS, OUTPUT);
    pinMode(PIN_START, OUTPUT);
    pinMode(IPIN_DRDY, INPUT);
    pinMode(PIN_CLKSEL, OUTPUT);//*optional
    pinMode(IPIN_RESET, OUTPUT);//*optional
    pinMode(IPIN_PWDN, OUTPUT);//*optional
    
     
    /************************  Pin initial values  ************************/
    digitalWrite(PIN_CLKSEL, HIGH);
    digitalWrite(IPIN_PWDN, HIGH);
    digitalWrite(IPIN_RESET, HIGH);
    digitalWrite(IPIN_CS, HIGH);
  
    /************************  SPI configurations  ************************/
    SPI.begin();
    SPI.setBitOrder(MSBFIRST);
    SPI.setClockDivider(SPI_CLOCK_DIV4); //http://forum.pjrc.com/threads/1156-Teensy-3-SPI-Basic-Clock-Questions  
    SPI.setDataMode(SPI_MODE1);
  
    /************************  Serial configurations and start  ************************/
    Serial.begin(9600);
  //  check_buf[0] = 48; check_buf[1] = 49; check_buf[2] = 50;
   // SerialUSB.begin(2000000);
    Serial2.begin(460800);
  //  while(!SerialUSB);
  
    /************************  Start ADS1298  ************************/
    delay(500); //wait for the ads129n to be ready - it can take a while to charge caps
    digitalWrite(PIN_CLKSEL, HIGH);//*optional
    delay(1);digitalWrite(IPIN_PWDN, HIGH);//*optional - turn off power down mode
    digitalWrite(IPIN_RESET, HIGH);delay(100);//*optional
    digitalWrite(IPIN_RESET, LOW);delay(1);//*optional
    digitalWrite(IPIN_RESET, HIGH);delay(1);  //*optional Wait for 18 tCLKs AKA 9 microseconds, we use 1 millisec
  
    /************************  Stop Read Data Continuously mode(Send SDATAC Command)  ************************/
    delay(100); //pause to provide ads129n enough time to boot up...
    adc_send_command(SDATAC);
    delay(10);
  
    /************************  Reading IDvalue(model number)  ************************/
    IDval = adc_rreg(0); 
    switch (IDval & B00001111 ) { //least significant bits reports channels
      case  B00001110: //16
        gMaxChan = 99; //ads1299
        break;
      case B00000001: //17
        gMaxChan = 6; //ads1296
        break; 
      case B00000010: //18
        gMaxChan = 8; //ads1298
        break;
      case B00000110: //30
        gMaxChan = 7; //ads1299
        break;
      default: 
        gMaxChan = 89;
    }
   Serial.print(" \n******* ID check ******* \nchip ID: \t\t\t");
   Serial.println(gMaxChan);
    Serial.print("ID Register value: \t\t");
   Serial.println(IDval,BIN);
     
    /************************  ADS1298 setup  ************************/
    adsSetup(); //optional - sets up device - the PC can do this as well 

    /************************  ADS1298 start conversion  ************************/
    digitalWrite(PIN_START, HIGH); 
    delay(1000); 
    adc_send_command(RDATAC);
    delay(1000); 
  Serial.println("\n\n Initiating Conversion!! ");

}
int temp =  0;
bool checked;
void loop()
{
  if(!checked){
  temp = Serial2.read();
    if(temp == 0x47){
      Serial2.write("G");
      checked = 1;
    }
    }
    else{
      sendOsc(); //see if there are any new samples to report
      if(Serial2.available()){
        temp = Serial2.read();
     if(temp == 0x47){
      Serial2.write("G");
      checked = 0;        
        }
    }
    }

   
  
} //loop()
