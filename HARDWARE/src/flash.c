# include "flash.h"

union FLASH_DATA flash_data;

void store_config_data( void)
{
	uint8_t i;
	FLASH_Status status = FLASH_COMPLETE;

	FLASH_Unlock();  //����
	FLASH_DataCacheCmd(DISABLE);//FLASH�����ڼ�,�����ֹ���ݻ���
	
	status=FLASH_EraseSector(FLASH_Sector_11,VoltageRange_3);//VCC=2.7~3.6V֮��!!
	if(status!=FLASH_COMPLETE)return;	//����������

   	if(status==FLASH_COMPLETE)
	{
		for(i=0; i< FLASH_WORD_DATA_SIZE; ++i)
		{
			
			if(FLASH_ProgramWord(FLASH_ADDR_START+(i<<2),flash_data.word_data[i])!=FLASH_COMPLETE)//д������
			{ 
				break;	//д���쳣
			}
		}
	}
	
	FLASH_DataCacheCmd(ENABLE);	//FLASH��������,�������ݻ���
	FLASH_Lock();//����
}

void load_flash_data(void)
{
	uint8_t i;
	struct Mpu6050 *mpu = &car.component.mpu6050;
	
	for(i=0; i< FLASH_WORD_DATA_SIZE; ++i)
	{
			flash_data.word_data[i] = *(((uint32_t *)FLASH_ADDR_START) + i);
	}
	
	if((flash_data.word_data[FLASH_ADDR_MPU6050_GYROX_OFFSET] == FLASH_NULL_WORD_DATA)\
		|| (flash_data.word_data[FLASH_ADDR_MPU6050_GYROY_OFFSET] == FLASH_NULL_WORD_DATA)\
	    || (flash_data.word_data[FLASH_ADDR_MPU6050_GYROZ_OFFSET] == FLASH_NULL_WORD_DATA)
		|| (flash_data.word_data[FLASH_ADDR_MPU6050_GYROX_OFFSET] == 0)\
		|| (flash_data.word_data[FLASH_ADDR_MPU6050_GYROY_OFFSET] == 0)\
		|| (flash_data.word_data[FLASH_ADDR_MPU6050_GYROZ_OFFSET] == 0))  
	{
		mpu->get_offset_flag = false;
	}
	else
	{
		mpu->gyro_offset[MPU6050_GYROX_OFFSET] = flash_data.float_data[FLASH_ADDR_MPU6050_GYROX_OFFSET];
		mpu->gyro_offset[MPU6050_GYROY_OFFSET] = flash_data.float_data[FLASH_ADDR_MPU6050_GYROY_OFFSET];
		mpu->gyro_offset[MPU6050_GYROZ_OFFSET] = flash_data.float_data[FLASH_ADDR_MPU6050_GYROZ_OFFSET];
		
		mpu->get_offset_flag = true;
		//mpu6050.get_offset_flag = false;
	}
}

