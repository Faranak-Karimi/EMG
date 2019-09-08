 #include <SPI.h>

class ESPSafeMaster
{
private:
    uint8_t _ss_pin;
    void _pulseSS()
    {
        digitalWrite(_ss_pin, HIGH);
        delayMicroseconds(5);
        digitalWrite(_ss_pin, LOW);
    }
public:
    ESPSafeMaster(uint8_t pin):_ss_pin(pin) {}
    void begin()
    {
        pinMode(_ss_pin, OUTPUT);
        _pulseSS();
    }

    uint32_t readStatus()
    {
        _pulseSS();
        SPI.transfer(0x04);
        uint32_t status = (SPI.transfer(0) | ((uint32_t)(SPI.transfer(0)) << 8) | ((uint32_t)(SPI.transfer(0)) << 16) | ((uint32_t)(SPI.transfer(0)) << 24));
        _pulseSS();
        return status;
    }

    void writeStatus(uint32_t status)
    {
        _pulseSS();
        SPI.transfer(0x01);
        SPI.transfer(status & 0xFF);
        SPI.transfer((status >> 8) & 0xFF);
        SPI.transfer((status >> 16) & 0xFF);
        SPI.transfer((status >> 24) & 0xFF);
        _pulseSS();
    }

    void readData(uint8_t * data)
    {
        _pulseSS();
        SPI.transfer(0x03);
        SPI.transfer(0x00);
        for(uint8_t i=0; i<32; i++) {
            data[i] = SPI.transfer(0)>>1;
        }
        _pulseSS();
    }

    void writeData(uint8_t * data, size_t len)
    {
        uint8_t i=0;
        _pulseSS();
        SPI.transfer(0x02);
        SPI.transfer(0x00);
        while(len-- && i < 32) {
            SPI.transfer(data[i++]);
        }
        while(i++ < 32) {
            SPI.transfer(0);
        }
        _pulseSS();
    }

    String readData()
    {
        char data[33];
        data[32] = 0;
        readData((uint8_t *)data);
        return String(data);
    }

    void writeData(const char * data)
    {
        writeData((uint8_t *)data, strlen(data));
    }
};

ESPSafeMaster esp(SS);

void send(const char * message)
{
    Serial.print("Master: ");
    Serial.println(message);
    esp.writeData(message);
    delay(10);
    Serial.print("Slave: ");
    Serial.println(esp.readData());
    Serial.println();
}


uint8_t data [9] {1,2,3,4,5,6,7,8,9};
size_t len = 9;
void setup()
{
    Serial.begin(115200);
    SPI.begin();
    SPI.beginTransaction(SPISettings(1000000,MSBFIRST, SPI_MODE1));
    esp.begin();           
    delay(1000);
    //send("Hello Slave!");
}
void loop()
{
    ///delay(1000);
   // send("Are you alive?");
    uint8_t i=0;
      
        SPI.transfer(0x02);
        SPI.transfer(0x00);
        while(len-- && i < 32) {
            SPI.transfer(data[i++]);
        }
        while(i++ < 32) {
            SPI.transfer(0);
        }
   
}
