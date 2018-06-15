#include "MicroBit.h"
MicroBit uBit;

#include "HTU21D.h"
HTU21D HTU;

int main(void){
    uBit.init();
    
    //HTU.softReset();
    
    //HTU.setResolution(RH12_TEMP14);
    //HTU.setResolution(RH08_TEMP12);
    //HTU.setResolution(RH10_TEMP13);
    //HTU.setResolution(RH11_TEMP11);
    while(1){
        //printf("User Register: 0x%X\n", HTU.read_user_register());
        
        float temp  = HTU.readTemp();
        float humid = HTU.readHumid();
        printf("%.1f C, %.1f %%\n", temp, humid);
        
        wait(1.0);
    }
    
    release_fiber();
    return 0;
}
