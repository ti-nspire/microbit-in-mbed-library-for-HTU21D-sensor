#define HTDU21D_ADDRESS           0x40<<1
#define TRIGGER_TEMP_MEASURE_HOLD 0xE3
#define TRIGGER_HUMD_MEASURE_HOLD 0xE5
#define SHIFTED_DIVISOR           0x988000UL
#define WRITE_USER_REG            0xE6
#define READ_USER_REG             0xE7
#define SOFT_RESET                0xFE

#define RH12_TEMP14 0b00000000
#define RH08_TEMP12 0b00000001
#define RH10_TEMP13 0b10000000
#define RH11_TEMP11 0b10000001

class HTU21D{
    public:
        HTU21D();
        float readTemp(void);
        float readHumid(void);
        char  read_user_register(void);
        void  setResolution(char resolution);
        void  softReset(void);
    private:
        unsigned short check_crc(char msb, char lsb, char crc);
};
