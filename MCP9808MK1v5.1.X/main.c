/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.4
        Device            :  PIC18F46K20
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/examples/i2c_master_example.h"

/*
                         Main application
 */
void main(void){
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    //Include this header file
    //#include "mcc_generated_files/examples/i2c_master_example.h"

    #define MCP9808_ADDR 0x18 // nicht 0x30

    #define CONFIG_REG_ADDR 0x01
    #define TEMP_REG_ADDR 0x05
    uint16_t tempData;
    uint16_t tempDataAnz;
    I2C_Write2ByteRegister(MCP9808_ADDR,CONFIG_REG_ADDR,0x0000);
    tempData = I2C_Read2ByteRegister(MCP9808_ADDR,TEMP_REG_ADDR);
    
    while (1){                                                          // Endlosscheife
        I2C_Write2ByteRegister(MCP9808_ADDR,CONFIG_REG_ADDR,0x0000);    // wählt das Temperatur-Register im Pointer-Register aus
        tempData = I2C_Read2ByteRegister(MCP9808_ADDR,TEMP_REG_ADDR);   // "tempData" gleich I2C read (Temperatur-Register)
        tempDataAnz = (tempData & 0x0fff) >> 4;                         // "tempDataAnz" gleich "tempData" maskiert mit 0x0fff um 4 nach rechts
        if((tempData & 0x1000) == 0x1000){                              // wenn "tempData" maskiert mit 0x1000 gleich 0x1000 ist
            tempDataAnz = 256 - tempDataAnz;                            // "tempDataAnz" - 256
            printf("-");                                                // schreibt "-" an UART
        }                                                               // 
        printf("%d°C\r\n",tempDataAnz);                                 // schreibt den Inhalt von "tempDataAnz" an UART
        __delay_ms(500);                                                // warte 500ms
    }                                                                   // 
}                                                                       // 
/**
 End of File
*/