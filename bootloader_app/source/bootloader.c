#include "bootloader.h"

// TODO:
// bootloader should have a config file with this value or be given thiat value etc
#define USER_APP_LOCATION (0x8020000 + 4)

typedef enum
{
	bl_idle_state = 0,
	bl_update_state,
} BL_State_t;
BL_State_t bootloaderState = bl_idle_state;

// buffer frame where we will store recevied bytes directly from UART
uint8_t bytes_buff[sizeof(frame_format_t)] = {0};
// frame we will assemble from received bytes
frame_format_t receivedFrame;
uint8_t bytes_received_count = 0;
// TODO: should this be sent by the cmoputer app?
// let the user chose where the firmware will decide?
// however the binary feel needs to have the propper
// vector table offset...so maybe not
uint32_t start_address = 0x8020000;
uint32_t blockNum = 0;
bootloader_state bootlaoder_current_state = STATE_IDLE;

// TODO:
bool parse = false;
// TODO:
// bootloader should  have no knowledge of this, atleast not explicitly
extern UART_HandleTypeDef huart2;
// private prototypes
static void print(char *msg, ...);
static void jump_to_user_app(void);
static void write_payload(void);
static void erase_sector(void);
static void parse_frame(void);
// state function protoypes
frame_format_t parsing_state_func(void);
frame_format_t idle_state_func(void);
void bootloader_main(void)
{
	// TODO: fix :enable RX interrupt
	USART2->CR1 |= USART_CR1_RXNEIE;

	// initialize state functions
	bootloader_state_functions[STATE_IDLE] = idle_state_func;

	erase_sector();

	while (1)
	{
		(*bootloader_state_functions[bootlaoder_current_state])();
		
		// HAL_GPIO_TogglePin(GPIOA, user_led_Pin);
		// HAL_Delay(500);
	}
}
frame_format_t parsing_state_func(void)
{
}
frame_format_t idle_state_func(void)
{
	parse_frame();
}
static void parse_frame(void)
{
	if (parse)
	{
		//assemble a frame from bytes_buff 
		memcpy(&receivedFrame, bytes_buff, sizeof(frame_format_t));
		
		//the type of frame we get will dictate what the next state should be
		
		if (receivedFrame.start_of_frame == BL_START_OF_FRAME && receivedFrame.end_of_frame == BL_END_OF_FRAME && receivedFrame.frame_id == BL_PAYLOAD)
		{
			write_payload();
		}
		else if (receivedFrame.start_of_frame == BL_START_OF_FRAME && receivedFrame.end_of_frame == BL_END_OF_FRAME && receivedFrame.frame_id == BL_UPDATE_DONE)
		{
			jump_to_user_app();
		}
		parse = false;
	}
}
static void write_payload(void)
{

	HAL_FLASH_Unlock();
	for (int i = 0; i < 16; i += 4)
	{
		uint32_t *val = (uint32_t *)&receivedFrame.payload[i];
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, start_address, *val);
		start_address += 4;
	}
	HAL_FLASH_Unlock();
	print("o");

	//	HAL_FLASH_Lock();
}

static void jump_to_user_app(void)
{
	void (*user_app_reset_handler)(void) = (void *)(*((uint32_t *)(USER_APP_LOCATION)));
	user_app_reset_handler();
}

static void print(char *msg, ...)
{
	char buff[250];
	va_list args;
	va_start(args, msg);
	vsprintf(buff, msg, args);

	for (int i = 0; i < strlen(buff); i++)
	{
		USART2->DR = buff[i];
		while (!(USART2->SR & USART_SR_TXE))
			;
	}

	while (!(USART2->SR & USART_SR_TC))
		;
}
// TODO: lots to do here keep playing with it....
void bootloader_USART2_callback(uint8_t data)
{
	// filll buffer until we have enough bytes to assemble a frame
	if (bytes_received_count <= sizeof(frame_format_t))
	{
		bytes_buff[bytes_received_count++] = data;
		if (bytes_received_count == sizeof(frame_format_t))
		{

			bytes_received_count = 0;
			parse = true;
		}
	}
	// USART2->DR = data; //echo the data
	//  HAL_GPIO_TogglePin(GPIOA, user_led_Pin);
}
void set_bl_state(BL_State_t state)
{
	bootloaderState = state;
}

// TODO:  abstract sector erasing based user app memory locationa and size
void erase_sector(void)
{

	FLASH_EraseInitTypeDef erase;
	erase.NbSectors = 1;
	erase.Sector = FLASH_SECTOR_5;
	erase.VoltageRange = FLASH_VOLTAGE_RANGE_3;
	uint32_t err = 0;

	HAL_FLASH_Unlock();
	HAL_FLASHEx_Erase(&erase, &err);
	HAL_FLASH_Lock();
}
