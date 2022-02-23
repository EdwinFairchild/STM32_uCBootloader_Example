/**
 * @brief bootlaoder starts @ 0x8000000
 * and is given about 130k of space
 * 
 * user app will begin a@ 0x8020000
 * CRC: https://users.ece.cmu.edu/~koopman/crc/
 */

#ifndef _BOOTLOADER_H_
#define _BOOTLOADER_H_

#include "BL_frames.h"
#include "main.h"
#include <stdint.h>
#include <stdbool.h>
//TODO: these are just for printing bootloader does not need these
//bootloader should be passed a printing function for debug messages
#include "usart.h"
#include "gpio.h"
#include "stdarg.h"
#include "stdio.h"
#include "string.h"
#include "usart.h"
//-----------------------------------------------------------------


//prototypes
void bootloader_main(void);
void bootloader_USART2_callback(uint8_t data);
#endif
