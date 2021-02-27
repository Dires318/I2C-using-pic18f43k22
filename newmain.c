#include "newfile.h"
void main(void){
    ANSELB=0;
    TRISB=0;
    ANSELAbits.ANSA0=0;
    TRISAbits.RA0=1;
    ANSELAbits.ANSA1=0;
    TRISAbits.RA1=1;
	if(PORTAbits.AN0){
        PORTB=0;
        config();
        while(1){
        wait();
        Send_I2C_StartBit(); // Start
        wait();
        Send(0x10);
        wait();
        Send(0x07);
        wait();// Wait for ACKEN
        Send_I2C_StopBit(); // Stop
        if(!PORTAbits.AN0)
            break;
        }
    }
    if(PORTAbits.AN1){
       configure();
        while(1){
        wait_clearInterapt();
        interapt();
        address();
        wait_clearInterapt();
        PORTB=receive();
        release();
        if(!PORTAbits.AN0)
            break;
        }
    }
}
