// DSPIC33CK64MC105 Configuration Bit Settings

// 'C' source line config statements

// FSEC
#pragma config BWRP = OFF               // Boot Segment Write-Protect bit (Boot Segment may be written)
#pragma config BSS = DISABLED           // Boot Segment Code-Protect Level bits (No Protection (other than BWRP))
#pragma config BSEN = OFF               // Boot Segment Control bit (No Boot Segment)
#pragma config GWRP = OFF               // General Segment Write-Protect bit (General Segment may be written)
#pragma config GSS = DISABLED           // General Segment Code-Protect Level bits (No Protection (other than GWRP))
#pragma config CWRP = OFF               // Configuration Segment Write-Protect bit (Configuration Segment may be written)
#pragma config CSS = DISABLED           // Configuration Segment Code-Protect Level bits (No Protection (other than CWRP))
#pragma config AIVTDIS = OFF            // Alternate Interrupt Vector Table bit (Disabled AIVT)

// FBSLIM
#pragma config BSLIM = 0x1FFF           // Boot Segment Flash Page Address Limit bits (Enter Hexadecimal value)

// FOSCSEL
#pragma config FNOSC = FRCDIVN          // Oscillator Source Selection (Internal Fast RC (FRC) Oscillator with postscaler)
#pragma config IESO = ON                // Two-speed Oscillator Start-up Enable bit (Start up device with FRC, then switch to user-selected oscillator source)

// FOSC
#pragma config POSCMD = NONE            // Primary Oscillator Mode Select bits (Primary Oscillator disabled)
#pragma config OSCIOFNC = OFF           // OSC2 Pin Function bit (OSC2 is clock output)
#pragma config FCKSM = CSDCMD           // Clock Switching Mode bits (Both Clock switching and Fail-safe Clock Monitor are disabled)
#pragma config PLLKEN = ON              // PLL Lock Enable (PLL clock output will be disabled if LOCK is lost)
#pragma config XTCFG = G3               // XT Config (24-32 MHz crystals)
#pragma config XTBST = ENABLE           // XT Boost (Boost the kick-start)

// FWDT
#pragma config RWDTPS = PS2147483648    // Run Mode Watchdog Timer Post Scaler select bits (1:2147483648)
#pragma config RCLKSEL = LPRC           // Watchdog Timer Clock Select bits (Always use LPRC)
#pragma config WINDIS = ON              // Watchdog Timer Window Enable bit (Watchdog Timer operates in Non-Window mode)
#pragma config WDTWIN = WIN25           // Watchdog Timer Window Select bits (WDT Window is 25% of WDT period)
#pragma config SWDTPS = PS2147483648    // Sleep Mode Watchdog Timer Post Scaler select bits (1:2147483648)
#pragma config FWDTEN = ON              // Watchdog Timer Enable bit (WDT enabled in hardware)

// FPOR
#pragma config BISTDIS = DISABLED       // Memory BIST Feature Disable (mBIST on reset feature disabled)

// FICD
#pragma config ICS = PGD1               // ICD Communication Channel Select bits (Communicate on PGC1 and PGD1)
#pragma config JTAGEN = OFF             // JTAG Enable bit (JTAG is disabled)

// FDMTIVTL
#pragma config DMTIVTL = 0xFFFF         // Dead Man Timer Interval low word (Enter Hexadecimal value)

// FDMTIVTH
#pragma config DMTIVTH = 0xFFFF         // Dead Man Timer Interval high word (Enter Hexadecimal value)

// FDMTCNTL
#pragma config DMTCNTL = 0xFFFF         // Lower 16 bits of 32 bit DMT instruction count time-out value (0-0xFFFF) (Enter Hexadecimal value)

// FDMTCNTH
#pragma config DMTCNTH = 0xFFFF         // Upper 16 bits of 32 bit DMT instruction count time-out value (0-0xFFFF) (Enter Hexadecimal value)

// FDMT
#pragma config DMTDIS = OFF             // Dead Man Timer Disable bit (Dead Man Timer is Disabled and can be enabled by software)

// FDEVOPT
#pragma config ALTI2C1 = OFF            // Alternate I2C1 Pin bit (I2C1 mapped to SDA1/SCL1 pins)
#pragma config SMB3EN = SMBUS3          // SM Bus Enable (SMBus 3.0 input levels)
#pragma config SPI2PIN = PPS            // SPI2 Pin Select bit (SPI2 uses I/O remap (PPS) pins)

// FALTREG
#pragma config CTXT1 = OFF              // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 1 bits (Not Assigned)
#pragma config CTXT2 = OFF              // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 2 bits (Not Assigned)
#pragma config CTXT3 = OFF              // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 3 bits (Not Assigned)
#pragma config CTXT4 = OFF              // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 4 bits (Not Assigned)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#define FCY 1000000UL
#include <libpic30.h>


void UartInit(void)
{
    U1MODE = 0;
    U1MODEH = 0;    
    U1STA = 0;
    U1STAH = 0;
    U1BRG = 25;  // 9600 @ Fosc 200MHz

    U1STAHbits.URXISEL = 6;
    U1MODEHbits.BCLKSEL = 0;
    U1MODEbits.UTXEN = 1;
    U1MODEbits.URXEN = 1;
    U1MODEbits.UARTEN = 1;
    
    //DEBUGGER USB RX/TX TEST - FOR OOB DEMO EFFORT
    RPOR13bits.RP58R = 1;
    RPINR18bits.U1RXR = 59;
    
//    RPOR2bits.RP36R = 1;
//    RPINR18bits.U1RXR = 47;
}

void UartSendByte(char data)
{
    while (U1STAbits.TRMT == 0)
    {
    } // wait for room in TX buffer

    U1TXREG = data;
} 

void UartSendString(char *pData)
{
    unsigned int x = 0;

    while(pData[x] != 0)
    {
        UartSendByte(pData[x]);
        x = x + 1;
    }
}


int main(void)
{
    char data2[] = "dsPIC33CK64MC105 Curiosity Nano Demo. Please press on-board button to initiate demo.\n\r";
    char data[] = "\n Button pressed! Enjoy the blink. \n\r";
    char data1[] = "\n Button not pressed... please press to observe blink. \n\r";

    _ANSELD13 = 0; //make RD13 a digital input
    _CNPUD13 = 1; //turn on internal pull up for RD13 
    _TRISD13 = 1; //RD13 an input 
    _TRISD10 = 0; // make trisd10 an output

    UartInit();

    while(PORTDbits.RD13 != 0)
    {
        UartSendString(data2);
        __delay_ms(1000);
        _LATD10 = 1;
    }

    while(1)
    {
        if(PORTDbits.RD13 == 0)
        {
            LATDbits.LATD10 = 0;
            UartSendString(data);
            __delay_ms(1000);
        }
        else
        {
            LATDbits.LATD10 = 1;
            UartSendString(data1);
            __delay_ms(1000);
        }
    }
} 
    
    
    





