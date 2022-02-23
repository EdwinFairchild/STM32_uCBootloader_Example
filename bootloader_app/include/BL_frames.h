#ifndef _BL_FRAMES_H_
#define _BL_FRAMES_H_
/**
 * @brief Frame Format
 *          -------------------------------------------
 *          |-SOF-|-Frame_ID-|-Len-|-Data-|-CRC-|-EOF-|
 *  Bytes:  ---4-------4--------2-----n------4-----4--
 */
#include <stdint.h>
//The PC side sends EDDY and FAIR in proper order but little endian nature of ARM M
//makes it store in address lowest to high so the F is in lowest bye of the hex and R is 
//at the highest byte

#define BL_START_OF_FRAME  0x45444459 //EDDY : little endian
#define BL_END_OF_FRAME    0x46414952 //FAIR : little endian

#define BL_STATUS_CHECK 0x4b4b4b4b
#define BL_START_UPDATE 0xBA5EBA11
#define BL_PAYLOAD      0xDEADBEEF
#define BL_UPDATE_DONE  0xDEADDADE
typedef struct __attribute__((packed))
{
    uint32_t start_of_frame;
    uint32_t frame_id;
    uint16_t payload_len;
    uint8_t payload[16];
    uint32_t crc32; 
    uint32_t  end_of_frame;

}frame_format_t;


#define BL_ACK  0x00
#define BL_NACK 0x01
typedef enum
{
    BL_status_ok = 0,
    BL_status_err

}bl_status;




#endif
