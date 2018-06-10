#include "HTU21D.h"

#include "MicroBit.h"
MicroBitI2C i2c(I2C_SDA0, I2C_SCL0);

unsigned short HTU21D::check_crc(char msb, char lsb, char crc){
    unsigned int divisor   = SHIFTED_DIVISOR;
    unsigned int remainder = msb<<16 | lsb<<8 | crc;

    for(int i=23; i>7; i--){
        if(remainder & 1<<i){
            remainder ^= divisor;
        }
        divisor >>= 1;        
    }
    return (remainder == 0) ? 0 : 999;
}

float HTU21D::readTemp(){
    char buf[3] = {TRIGGER_TEMP_MEASURE_HOLD};
    i2c.write(HTDU21D_ADDRESS, buf, 1); 
    i2c.read (HTDU21D_ADDRESS, buf, 3);

    unsigned short raw       = (buf[0]<<8 | buf[1]) & 0xfffc;
    unsigned short crcResult = check_crc(buf[0], buf[1], buf[2]);

    return (crcResult == 0) ?
           -46.85F + 175.72F * (float)raw / 65536.0F :
           crcResult;
}

float HTU21D::readHumid(){
    char buf[3] = {TRIGGER_HUMD_MEASURE_HOLD};
    i2c.write(HTDU21D_ADDRESS, buf, 1); 
    i2c.read (HTDU21D_ADDRESS, buf, 3);

    unsigned short raw       = (buf[0]<<8 | buf[1]) & 0xfffc;
    unsigned short crcResult = check_crc(buf[0], buf[1], buf[2]);

    return (crcResult == 0) ?
           -6.0F + 125.0F * (float)raw / 65536.0F :
           crcResult;
}

char HTU21D::read_user_register(void){
    char buf[] = {READ_USER_REG};
    i2c.write(HTDU21D_ADDRESS, buf, 1); 
    i2c.read (HTDU21D_ADDRESS, buf, 1);

    return buf[0];
}

void HTU21D::setResolution(char resolution){
    char userRegister = read_user_register();

    userRegister &= 0b01111110;
    resolution   &= 0b10000001;
    userRegister |= resolution;

    char buf[] = {WRITE_USER_REG, userRegister};
    i2c.write(HTDU21D_ADDRESS, buf, 2);
}

void HTU21D::softReset(void){
    char buf[] = {SOFT_RESET};
    i2c.write(HTDU21D_ADDRESS, buf, 1);
}
