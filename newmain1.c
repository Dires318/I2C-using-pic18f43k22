#include "newfile.h"
unsigned char p;
void config(){
ANSELCbits.ANSC3=0; // Digital I / O
ANSELCbits.ANSC4=0 ; // Digital I / O
TRISCbits.TRISC3=1; // SCL pin is input
TRISCbits.TRISC4=1; // SDA pin is input
SSP1ADD=0x25; // clock frequency of SLK = Fosc/ ( SSPAD
SSP1CON1bits.SSPM =0b1000; // I2C Master mode, clock
SSP1CON1bits.SSPEN =1; // Enables the serial port and
INTCONbits.PEIE=1; // Enables all active peripheral i
}
void Send_I2C_StartBit(void)
{
PIR1bits.SSP1IF= 0; // clear SSP interrupt bit
SSP1CON2bits.SEN=1; // send start bit
while(!PIR1bits.SSP1IF); // Wait for the SSPIF bit to
PIR1bits.SSP1IF= 0 ;
}
void Send_I2C_StopBit( void)
{
PIR1bits.SSP1IF= 0; // clear SSP interrupt bit
SSP1CON2bits.PEN =1 ; // Initiate the Stop condition
while(!PIR1bits.SSP1IF);// Wait for the SSPIF bit to
PIR1bits.SSP1IF=0;
}
void Send ( unsigned char x)
{
PIR1bits.SSP1IF= 0; // clear SSP interrupt bit
SSP1BUF=x; // Transmission begins as soon as SS
while(!PIR1bits.SSP1IF); // Wait for interrupt flag to
PIR1bits.SSP1IF=0;
}
void Send_I2C_Repeated_Start ( void)
{
PIR1bits.SSP1IF= 0; // clear SSP interrupt bit
SSP1CON2bits.RSEN=1 ;
while(!PIR1bits.SSP1IF); // Wait for the SSPIF bit to
PIR1bits.SSP1IF=0;
}
unsigned int Read_I2C_Data( void)
{
PIR1bits.SSP1IF= 0; // clear SSP interrupt bit
SSP1CON2bits.RCEN=1; // set the receive enable bit to i
while(!PIR1bits.SSP1IF); // Wait for interrupt flag to
PIR1bits.SSP1IF= 0; // clear SSP interrupt bit
return (SSP1BUF); // Data from eeprom is now in the SSPB
}
void wait()
{
    while((SSP1STAT&0x04)||(SSP1CON2&0x1F));
}
void configure(){
    ANSELCbits.ANSC3=0; // Digital I / O
    ANSELCbits.ANSC4=0 ; // Digital I / O
    TRISCbits.TRISC3=1; // SCL pin is input
    TRISCbits.TRISC4=1; // SDA pin is input
    SSP1CON1bits.SSPM=0b0110;// set the device as slave 
    SSP1CON1bits.SSPEN =1;//enable serial port
    SSP1ADD=0x10;
}
   void interapt(){
   if((SSP1CON1bits.SSPOV)||(SSP2CON1bits.WCOL)){
        p=SSP2BUF;
        SSP1CON1bits.SSPOV;
        SSP1CON1bits.WCOL=0;
        SSP1CON1bits.CKP=1;
   }
}
void address(){
    if(SSP1STATbits.BF){
    p=SSP1BUF;
    while(SSP1STATbits.BF);
     }
}
unsigned char receive(){
    if(SSP1STATbits.BF){
    p=SSP1BUF;
    while(SSP1STATbits.BF);
    }
    return (p);
}
void release(){
    SSP1CON1bits.CKP=1;
}
void wait_clearInterapt(){
    while(!PIR1bits.SSPIF);
    PIR1bits.SSPIF=0;
}