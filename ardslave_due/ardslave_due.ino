
//Arduino SPI slave test code that I found on https://github.com/manitou48/DUEZoo/blob/master/spislave.ino
// * Nice one Manitou, it worked first time

#include <SPI.h>

byte in;
  byte out[32];
// assumes MSB
static BitOrder bitOrder = MSBFIRST;

void slaveBegin(uint8_t _pin) {
  SPI.begin(_pin);
  REG_SPI0_CR = SPI_CR_SWRST;     // reset SPI
  REG_SPI0_CR = SPI_CR_SPIEN;     // enable SPI
  REG_SPI0_MR = SPI_MR_MODFDIS;     // slave and no modefault
  REG_SPI0_CSR = SPI_MODE0;    // DLYBCT=0, DLYBS=0, SCBR=0, 8 bit transfer
}


byte transfer(uint8_t _pin, uint8_t _data) {
    // Reverse bit order
    if (bitOrder == LSBFIRST)
        _data = __REV(__RBIT(_data));
    uint32_t d = _data;

    while ((REG_SPI0_SR & SPI_SR_TDRE) == 0) ;
    REG_SPI0_TDR = d;

    while ((REG_SPI0_SR & SPI_SR_RDRF) == 0) ;
    d = REG_SPI0_RDR;
    // Reverse bit order
    if (bitOrder == LSBFIRST)
        d = __REV(__RBIT(d));
    return d & 0xFF;
}

#define PRREG(x) Serial.print(#x" 0x"); Serial.println(x,HEX)

void prregs() {
  Serial.begin(115200);
  while(!Serial);
 // PRREG(REG_SPI0_MR);
 // PRREG(REG_SPI0_CSR);
 // PRREG(REG_SPI0_SR);
}


#define SS 10
void setup() {
  slaveBegin(SS);
  prregs();  // debug

    for(int i =0 ; i<32; i++)
    {
       out[i] = i + 32;
       //Serial.println(out[i]);
       //transfer(SS, out);
    }
}



void loop() {
  
    for(int i =0 ; i<32; i++)
    {
       //out = i + 32;
       transfer(SS, out[i]);
    }
  
  //out = in;
}
