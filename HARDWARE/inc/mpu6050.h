#ifndef __MPU6050_H
#define __MPU6050_H
#include "mpu6050_iic.h" 
#include <stdbool.h>  //bool����
#include "sys.h"
#include "delay.h"
#include <math.h>
//#include "usart.h"   

//#define MPU_ACCEL_OFFS_REG		0X06	//accel_offs�Ĵ���,�ɶ�ȡ�汾��,�Ĵ����ֲ�δ�ᵽ
//#define MPU_PROD_ID_REG			0X0C	//prod id�Ĵ���,�ڼĴ����ֲ�δ�ᵽ
#define MPU_SELF_TESTX_REG		0X0D	//�Լ�Ĵ���X
#define MPU_SELF_TESTY_REG		0X0E	//�Լ�Ĵ���Y
#define MPU_SELF_TESTZ_REG		0X0F	//�Լ�Ĵ���Z
#define MPU_SELF_TESTA_REG		0X10	//�Լ�Ĵ���A
#define MPU_SAMPLE_RATE_REG		0X19	//����Ƶ�ʷ�Ƶ��
#define MPU_CFG_REG				0X1A	//���üĴ���
#define MPU_GYRO_CFG_REG		0X1B	//���������üĴ���
#define MPU_ACCEL_CFG_REG		0X1C	//���ٶȼ����üĴ���
#define MPU_MOTION_DET_REG		0X1F	//�˶���ֵⷧ���üĴ���
#define MPU_FIFO_EN_REG			0X23	//FIFOʹ�ܼĴ���
#define MPU_I2CMST_CTRL_REG		0X24	//IIC�������ƼĴ���
#define MPU_I2CSLV0_ADDR_REG	0X25	//IIC�ӻ�0������ַ�Ĵ���
#define MPU_I2CSLV0_REG			0X26	//IIC�ӻ�0���ݵ�ַ�Ĵ���
#define MPU_I2CSLV0_CTRL_REG	0X27	//IIC�ӻ�0���ƼĴ���
#define MPU_I2CSLV1_ADDR_REG	0X28	//IIC�ӻ�1������ַ�Ĵ���
#define MPU_I2CSLV1_REG			0X29	//IIC�ӻ�1���ݵ�ַ�Ĵ���
#define MPU_I2CSLV1_CTRL_REG	0X2A	//IIC�ӻ�1���ƼĴ���
#define MPU_I2CSLV2_ADDR_REG	0X2B	//IIC�ӻ�2������ַ�Ĵ���
#define MPU_I2CSLV2_REG			0X2C	//IIC�ӻ�2���ݵ�ַ�Ĵ���
#define MPU_I2CSLV2_CTRL_REG	0X2D	//IIC�ӻ�2���ƼĴ���
#define MPU_I2CSLV3_ADDR_REG	0X2E	//IIC�ӻ�3������ַ�Ĵ���
#define MPU_I2CSLV3_REG			0X2F	//IIC�ӻ�3���ݵ�ַ�Ĵ���
#define MPU_I2CSLV3_CTRL_REG	0X30	//IIC�ӻ�3���ƼĴ���
#define MPU_I2CSLV4_ADDR_REG	0X31	//IIC�ӻ�4������ַ�Ĵ���
#define MPU_I2CSLV4_REG			0X32	//IIC�ӻ�4���ݵ�ַ�Ĵ���
#define MPU_I2CSLV4_DO_REG		0X33	//IIC�ӻ�4д���ݼĴ���
#define MPU_I2CSLV4_CTRL_REG	0X34	//IIC�ӻ�4���ƼĴ���
#define MPU_I2CSLV4_DI_REG		0X35	//IIC�ӻ�4�����ݼĴ���

#define MPU_I2CMST_STA_REG		0X36	//IIC����״̬�Ĵ���
#define MPU_INTBP_CFG_REG		0X37	//�ж�/��·���üĴ���
#define MPU_INT_EN_REG			0X38	//�ж�ʹ�ܼĴ���
#define MPU_INT_STA_REG			0X3A	//�ж�״̬�Ĵ���

#define MPU_ACCEL_XOUTH_REG		0X3B	//���ٶ�ֵ,X���8λ�Ĵ���
#define MPU_ACCEL_XOUTL_REG		0X3C	//���ٶ�ֵ,X���8λ�Ĵ���
#define MPU_ACCEL_YOUTH_REG		0X3D	//���ٶ�ֵ,Y���8λ�Ĵ���
#define MPU_ACCEL_YOUTL_REG		0X3E	//���ٶ�ֵ,Y���8λ�Ĵ���
#define MPU_ACCEL_ZOUTH_REG		0X3F	//���ٶ�ֵ,Z���8λ�Ĵ���
#define MPU_ACCEL_ZOUTL_REG		0X40	//���ٶ�ֵ,Z���8λ�Ĵ���

#define MPU_TEMP_OUTH_REG		0X41	//�¶�ֵ�߰�λ�Ĵ���
#define MPU_TEMP_OUTL_REG		0X42	//�¶�ֵ��8λ�Ĵ���

#define MPU_GYRO_XOUTH_REG		0X43	//������ֵ,X���8λ�Ĵ���
#define MPU_GYRO_XOUTL_REG		0X44	//������ֵ,X���8λ�Ĵ���
#define MPU_GYRO_YOUTH_REG		0X45	//������ֵ,Y���8λ�Ĵ���
#define MPU_GYRO_YOUTL_REG		0X46	//������ֵ,Y���8λ�Ĵ���
#define MPU_GYRO_ZOUTH_REG		0X47	//������ֵ,Z���8λ�Ĵ���
#define MPU_GYRO_ZOUTL_REG		0X48	//������ֵ,Z���8λ�Ĵ���

#define MPU_I2CSLV0_DO_REG		0X63	//IIC�ӻ�0���ݼĴ���
#define MPU_I2CSLV1_DO_REG		0X64	//IIC�ӻ�1���ݼĴ���
#define MPU_I2CSLV2_DO_REG		0X65	//IIC�ӻ�2���ݼĴ���
#define MPU_I2CSLV3_DO_REG		0X66	//IIC�ӻ�3���ݼĴ���

#define MPU_I2CMST_DELAY_REG	0X67	//IIC������ʱ����Ĵ���
#define MPU_SIGPATH_RST_REG		0X68	//�ź�ͨ����λ�Ĵ���
#define MPU_MDETECT_CTRL_REG	0X69	//�˶������ƼĴ���
#define MPU_USER_CTRL_REG		0X6A	//�û����ƼĴ���
#define MPU_PWR_MGMT1_REG		0X6B	//��Դ����Ĵ���1
#define MPU_PWR_MGMT2_REG		0X6C	//��Դ����Ĵ���2 
#define MPU_FIFO_CNTH_REG		0X72	//FIFO�����Ĵ����߰�λ
#define MPU_FIFO_CNTL_REG		0X73	//FIFO�����Ĵ����Ͱ�λ
#define MPU_FIFO_RW_REG			0X74	//FIFO��д�Ĵ���
#define MPU_DEVICE_ID_REG		0X75	//����ID�Ĵ���
 
//���AD0��(9��)�ӵ�,IIC��ַΪ0X68(���������λ).
//�����V3.3,��IIC��ַΪ0X69(���������λ).
#define MPU_ADDR				0X68
#define RAD 57.29578f;   //180.0/3.1415926
#define halfT 0.002f  //halfT=��������/2����������Ϊmain����whileѭ������ʱ��
#define Ki 0.005f
#define Kp 2.0f 
#define Accel_2_Scale_Factor    16384.0f      //2^16/4
#define Gyro_500_Rad_Factor     0.00026646f   //1000/2^16/57.3���ٶȾ���  ��λ������/s

enum MPU6050_GYRO_OFFSET
{
	MPU6050_GYROX_OFFSET,
	MPU6050_GYROY_OFFSET,
	MPU6050_GYROZ_OFFSET,
	MPU6050_GYRO_OFFSET_END,
};

struct DMP_Data
{
int16_t GYROx;	//������ X�� ���ٶ� ADCֵ

int16_t GYROy;  //������ Y�� ���ٶ� ADCֵ

int16_t GYROz;	//������ Z�� ���ٶ� ADCֵ

int16_t ACCx;   //���ٶȼ� X�� ADCֵ

int16_t ACCy;   //���ٶȼ� Y�� ADCֵ

int16_t ACCz;	//���ٶȼ� Z�� ADCֵ

int16_t HMCx;   //�������� X��

int16_t HMCy;   //�������� Y��

int16_t HMCz;   //��������Z��
	
float gx;
float gy;
float gz;
float ax;
float ay;
float az;

//���������� DMP_Routing ���¡�
int16_t  dmp_pitch;     //DMP������ĸ�����	��λ����
int16_t  dmp_roll;      //DMP��ת��	 ��λ����
int16_t  dmp_yaw;		//DMP ����ǣ�����û�д����Ʋ��룬����ǻ�Ʈ  ��λ����
};

struct Quaternion
{
	float q0,q1,q2,q3;
};

struct Integral_Error
{
	float exInt,eyInt,ezInt;
};

struct Attitude
{
	uint16_t error_counter;
	int16_t pitch;
	int16_t roll;
	int16_t yaw;
	float float_pitch;
	float float_roll;
	float float_yaw;
	
	float ax;
	float ay;
	float az;
	
	float vx;
	float vy;
	float vz;

	int16_t gyro_pitch;
	int16_t gyro_yaw;
	int16_t gyro_roll;
//	struct Window_Filter_signed filter_yaw;
//	struct Window_Filter_signed filter_pitch;
//	struct Window_Filter_signed filter_roll;
};

struct 	Mpu6050
{
	u8 data_buff[14]; //���ٶȡ��¶ȡ�������ֵ
	bool get_offset_flag;
	float gyro_offset[MPU6050_GYRO_OFFSET_END];
	struct DMP_Data DMP_data;
	struct Quaternion quaternion;
	struct Integral_Error integral_error;
	struct Attitude attitude;
};


////��Ϊ�������GND,����תΪ��д��ַ��,Ϊ0XD1��0XD0(�����GND,��Ϊ0XD3��0XD2)  
//#define MPU_READ    0XD1
//#define MPU_WRITE   0XD0

u8 mpu6050_Init(void); 								//��ʼ��MPU6050
u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf);//IIC����д
u8 MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf); //IIC������ 
u8 MPU_Write_Byte(u8 reg,u8 data);				//IICдһ���ֽ�
u8 MPU_Read_Byte(u8 reg);						//IIC��һ���ֽ�

u8 MPU_Set_Gyro_Fsr(u8 fsr);
u8 MPU_Set_Accel_Fsr(u8 fsr);
u8 MPU_Set_LPF(u16 lpf);
u8 MPU_Set_Rate(u16 rate);
u8 MPU_Set_Fifo(u8 sens);


short MPU_Get_Temperature(void);
u8 MPU_Get_Gyroscope(short *gx,short *gy,short *gz);
u8 MPU_Get_Accelerometer(short *ax,short *ay,short *az);

void mpu6050_task(void);

#endif
