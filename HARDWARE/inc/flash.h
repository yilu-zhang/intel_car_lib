#ifndef __FLASH_H
#define __FLASH_H

//#include "sys.h"
#include "mpu6050.h"

#define FLASH_ADDR_START 0x080E0000
#define FLASH_NULL_WORD_DATA 0xFFFFFFFF		//falsh±»²Á³ýºóÎª0xFFFFFFFF	

enum FLASH_ADDR
{
	FLASH_ADDR_SYSTEM_INFO =0,
	FLASH_ADDR_MPU6050_GYROX_OFFSET,
	FLASH_ADDR_MPU6050_GYROY_OFFSET,
	FLASH_ADDR_MPU6050_GYROZ_OFFSET,
	FLASH_ADDR_END,
};

#define  FLASH_DATA_SIZE (FLASH_ADDR_END *2)
#define  FLASH_WORD_DATA_SIZE (FLASH_ADDR_END)

union FLASH_DATA
{
	uint8_t byte_data[FLASH_WORD_DATA_SIZE<<2];
	uint32_t word_data[FLASH_WORD_DATA_SIZE]; 
	//int32_t int_word_data[FLASH_WORD_DATA_SIZE];
	float float_data[FLASH_WORD_DATA_SIZE];
};

extern union FLASH_DATA flash_data;

void load_flash_data(void);
void store_config_data(void);

#endif

