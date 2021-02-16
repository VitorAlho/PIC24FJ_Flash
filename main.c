/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  PIC24FJ256DA210
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.61
        MPLAB 	          :  MPLAB X v5.45
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#include <stdint.h>
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/memory/flash.h"
//#include "mcc_generated_files/memory/flash_demo.h"

/*
                         Main application
 */

typedef struct{
    uint16_t tag[1000];
    uint16_t lastRegister;
}GreenList;

GreenList __attribute__((far)) greenList ,  __attribute__((far)) greenListTest;

void greenList_clearList(GreenList *_greenList){
    _greenList->lastRegister = 0;
}

void greenList_addTag(uint16_t _tag, GreenList *_greenList){
    (*_greenList).tag[(*_greenList).lastRegister++] = _tag;
}

static __prog__ uint8_t memoriaFlash_Page1[FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS] __attribute__((space(prog),aligned(FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS)));

static __prog__ uint8_t memoriaFlash_Page2[FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS] __attribute__((space(prog),aligned(FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS)));


static void WordWriteExample()
{

    uint32_t flash_storage_address_page1;
    uint32_t flash_storage_address_page2;
    bool result;

    int i=0;
    
    for(i=0;i<1000;i++){
        greenList_addTag(0x0001+i,&greenList);
    }
    
    // Get flash page aligned address of flash reserved above for this test.
    flash_storage_address_page1 = FLASH_GetErasePageAddress((uint32_t)&memoriaFlash_Page1[0]);
    flash_storage_address_page2 = FLASH_GetErasePageAddress((uint32_t)&memoriaFlash_Page2[0]);

    // Program Valid Key for NVM Commands
    FLASH_Unlock(FLASH_UNLOCK_KEY);

    // Erase the page of flash at this address
    result = FLASH_ErasePage(flash_storage_address_page1);
    result = FLASH_ErasePage(flash_storage_address_page2);
    
    if (result == false)
    {
       //FlashError();
        while(1);
    }      
        
    for( i = 0; i < greenList.lastRegister; i++ ){    
        if( i == 0 ){
            result  = FLASH_WriteWord16( flash_storage_address_page1, greenList.tag[i] );
        }
        else{
            if( i < 512 ){
                result &= FLASH_WriteWord16( flash_storage_address_page1 + i * 2U, greenList.tag[i] ); 
            }
            else{
                if( i == 512 ){
                    result  = FLASH_WriteWord16( flash_storage_address_page2, greenList.tag[i] );
                }
                else{
                    result &= FLASH_WriteWord16( flash_storage_address_page2 + (i - 512) * 2U, greenList.tag[i] );
                }
            }
        }
    }    
    
    if (result == false)
    {
        //FlashError();
        while(1);
    }

    // Clear Key for NVM Commands so accidental call to flash routines will not corrupt flash
    FLASH_Lock();
    
    // read the data to verify the data
    for( i = 0; i < greenList.lastRegister; i++ ){
        if( i < 512 ){
            greenList_addTag( FLASH_ReadWord16(flash_storage_address_page1 + i * 2U), &greenListTest );
        }
        else{
            greenList_addTag( FLASH_ReadWord16(flash_storage_address_page2 + (i-512) * 2U), &greenListTest );
        }        
    }    

    // Stop if the read data does not match the write data;
    for( i = 0; i < greenList.lastRegister; i++ ){
        if ( greenList.tag[i] != greenListTest.tag[i] ){
              //MiscompareError();  
            while(1);
        }
    }      
}


int main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    while (1)
    {
        WordWriteExample();
        //FlashDemo();
        // Add your application code
    }

    return 1;
}
/**
 End of File
*/

