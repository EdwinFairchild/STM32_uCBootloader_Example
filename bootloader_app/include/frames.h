#ifndef _FRAMES_H_
#define _FRAMES_H_

/**
 * @brief Frame Format
 *          -------------------------------------------
 *          |-SOF-|-Frame_ID-|-Len-|-Data-|-CRC-|-EOF-|
 *  Bytes:  ---4-------4--------2-----n------4-----4--
 * 
 * STM32F4 n = 16 
 */

//delimeters
#define BL_ELEMENT_START_OF_FRAME  0x45444459 //EDDY 
#define BL_ELEMENT_END_OF_FRAME    0x46414952 //FAIR 

//frame IDS
#define BL_FRAME_ID_HEADER       0xFEEDEDDE //sends info about firmware: size , version 
#define BL_FRAME_ID_STATUS_CHECK 0x4b4b4b4b
#define BL_FRAME_ID_START_UPDATE 0xBA5EBA11
#define BL_FRAME_ID_PAYLOAD      0xDEADBEEF
#define BL_FRAME_ID_UPDATE_DONE  0xDEADDADE
#define BL_FRAME_ID_ACK_FRAME    0x45634AED
#define BL_FRAME_ID_NACK_FRAME   0x43636AEA
#define PAYLOAD_LEN 16

//frame formated struct
typedef struct __attribute__((packed))
{
    uint32_t start_of_frame;
    uint32_t frame_id;
    uint16_t payload_len;
    uint8_t payload[PAYLOAD_LEN];
    uint32_t crc32; 
    uint32_t  end_of_frame;

}frame_format_t;

//TODO: struct to configure bootloader

//header frame 
typedef struct __attribute__((packed))
{
    uint32_t start_of_frame;
    uint32_t frame_id;
    uint32_t magicNumber;
    uint32_t image_checksum;
    uint32_t firmware_version; 
    uint32_t imageSize;
    uint32_t jumpValue;
    uint32_t crc32; 
    uint32_t end_of_frame;

}header_frame_format_t;

//states
typedef enum bootloader_state
{
    BL_STATE_IDLE = 0,
    BL_STATE_START_UPDATE,
    BL_STATE_UPDATING,
}bootloader_state ; 

typedef enum
{
    BL_status_ok = 0,
    BL_status_err
}bl_status;

frame_format_t (*bootloader_state_functions[3])(void);


#endif