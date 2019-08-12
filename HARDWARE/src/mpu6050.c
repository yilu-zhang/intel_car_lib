#include "mpu6050.h"
#include "flash.h"

//��ʼ��MPU6050
//����ֵ:0,�ɹ�
//����,�������
u8 mpu6050_Init(void)
{ 
	u8 res;
	IIC_Init();//��ʼ��IIC����
	MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X80);	//��λMPU6050
    delay_ms(100);
	MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X00);	//����MPU6050 
	MPU_Set_Gyro_Fsr(1);					//�����Ǵ�����,��500dps
	MPU_Set_Accel_Fsr(0);					//���ٶȴ�����,��2g
	MPU_Set_Rate(50);						//���ò�����50Hz
	MPU_Write_Byte(MPU_INT_EN_REG,0X00);	//�ر������ж�
	MPU_Write_Byte(MPU_USER_CTRL_REG,0X00);	//I2C��ģʽ�ر�
	MPU_Write_Byte(MPU_FIFO_EN_REG,0X00);	//�ر�FIFO
	MPU_Write_Byte(MPU_INTBP_CFG_REG,0X80);	//INT���ŵ͵�ƽ��Ч
	res=MPU_Read_Byte(MPU_DEVICE_ID_REG);
	if(res==MPU_ADDR)//����ID��ȷ
	{
		MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X01);	//����CLKSEL,PLL X��Ϊ�ο�
		MPU_Write_Byte(MPU_PWR_MGMT2_REG,0X00);	//���ٶ��������Ƕ�����
		MPU_Set_Rate(50);						//���ò�����Ϊ50Hz
 	}else return 1;
	return 0;
}

float invSqrt(float x)                     //������ƽ��������
{
    float xhalf = 0.5f*x;
    int32_t i = *(int32_t *)&x; // get bits for floating VALUE
    i = 0x5f375a86- (i>>1); // gives initial guess y0
    x = *(float*)&i; // convert bits BACK to float
    x = x*(1.5f-xhalf*x*x); // Newton step, repeating increases accuracy
    return x;
} 

/*******************************************************************************
* Function Name  : IMUupdate
* Description    : accel gyro mag���ں��㷨��Դ��S.O.H. Madgwick.
* Input          : None
* Output         : None
* Return         : None

// q0 q1 q2 q3��Ҫ��ʼ�����ܴ��뵽����ĳ����У�����ֱ��ʹ��1 0 0 0��������ļ��㣬��������Ϊ��
// 1.����У׼accle gyro mag��
// 2.����init_quaternion������1��accle��xyz�����ݣ������ù�ʽ�������ʼ��ŷ���ǣ�
//   ����ACCEL_1G=9.81����λ����m/s2����init_Yaw�����ô����Ƽ��������
// 3.�����Լ��Ĳ������ڣ�������halfT��halfT=��������/2����������Ϊִ��1��AHRSupdate���õ�ʱ�䣻
// 4.��2�м������ŷ����ת��Ϊ��ʼ������Ԫ��q0 q1 q2 q3���ںϼ��ٶȼƣ������ǣ�������º��ŷ����pitch��roll��Ȼ��ʹ��pitch roll�ʹ����Ƶ����ݽ��л����˲��ںϵõ�Yaw������ʹ�ã�����ŷ��������㣻
// 5.��ֱ��ʹ����Ԫ����
// 6.�ظ�4�����ɸ�����̬;

//�ܵ���˵�������������ǣ����ٶȼ�������������Pitch��Roll��������������������Yaw;
//���³����У�gx, gy, gz��λΪ����/s��ax, ay, azΪ���ٶȼ������ԭʼ16��������, mx, my, mzΪ�����������ԭʼ16�������ݣ�
//ǰ������mpu9150�ļ��ٶȼƺ������ǵ�x��Ϊǰ������;
//���³�����õĲο�����Ϊ��mpu9150�ļ��ٶȼƺ���������ָ��xyz����Ϊ������

//������Ϊ����500��/s��ǰ���£������ǵ���������65.5LSB/��/s�����԰������������ʮ���������ݳ���65.5���ǽ��ٶȣ���λ�ǡ�/s��
//Ȼ���ٳ���57.3�ͱ�ɻ�����;(1����=180/pi=57.3��)

//ŷ���ǵ�λΪ����radian������57.3�Ժ�ת��Ϊ�Ƕ�
*******************************************************************************/
void IMUupdate(float gx, float gy, float gz, float ax, float ay, float az,\
             	float init_mx, float init_my, float init_mz) 
{
	float norm;
	float vx, vy, vz;
	float ex, ey, ez;
	struct Mpu6050 *mpu = &car.component.mpu6050;
	/*��һ������ֵ�����ٶȼƺʹ����Ƶĵ�λ��ʲô������ν����Ϊ�����ڴ˱����˹�һ������*/        
	//normalise the measurements
	norm = invSqrt(ax*ax + ay*ay + az*az);       
	ax = ax * norm;
	ay = ay * norm;
	az = az * norm;

	vx = 2*(mpu->quaternion.q1*mpu->quaternion.q3 - mpu->quaternion.q0*mpu->quaternion.q2);
	vy = 2*(mpu->quaternion.q0*mpu->quaternion.q1 + mpu->quaternion.q2*mpu->quaternion.q3);
	vz = mpu->quaternion.q0*mpu->quaternion.q0 - mpu->quaternion.q1*mpu->quaternion.q1\
		- mpu->quaternion.q2*mpu->quaternion.q2 + mpu->quaternion.q3*mpu->quaternion.q3;
  
	mpu->attitude.ax = ax;
	mpu->attitude.ay = ay;
	mpu->attitude.az = az;

	mpu->attitude.vx = vx;
	mpu->attitude.vy = vy;
	mpu->attitude.vz = vz;
	
	//���ڰѼ��ٶȵĲ���ʸ���Ͳο�ʸ����������Ѵų��Ĳ���ʸ���Ͳο�ʸ��Ҳ����������������������ݡ�
	// error is sum of cross product between reference direction of fields and direction measured by sensors
	ex = (ay*vz - az*vy);
	ey = (az*vx - ax*vz);
	ez = (ax*vy - ay*vx);
   
	// integral error scaled integral gain
	mpu->integral_error.exInt = mpu->integral_error.exInt + ex*Ki;
	mpu->integral_error.eyInt = mpu->integral_error.eyInt + ey*Ki;
	mpu->integral_error.ezInt = mpu->integral_error.ezInt + ez*Ki;
	
	// adjusted gyroscope measurements
	gx = gx + Kp*ex + mpu->integral_error.exInt;
	gy = gy + Kp*ey + mpu->integral_error.eyInt;
	gz = gz + Kp*ez + mpu->integral_error.ezInt;
	

	// integrate quaternion rate and normalise����Ԫ�������㷨��һ������-������
	mpu->quaternion.q0 = mpu->quaternion.q0 + (-mpu->quaternion.q1*gx - mpu->quaternion.q2*gy - mpu->quaternion.q3*gz)*halfT;
	mpu->quaternion.q1 = mpu->quaternion.q1 + (mpu->quaternion.q0*gx + mpu->quaternion.q2*gz - mpu->quaternion.q3*gy)*halfT;
	mpu->quaternion.q2 = mpu->quaternion.q2 + (mpu->quaternion.q0*gy - mpu->quaternion.q1*gz + mpu->quaternion.q3*gx)*halfT;
	mpu->quaternion.q3 = mpu->quaternion.q3 + (mpu->quaternion.q0*gz + mpu->quaternion.q1*gy - mpu->quaternion.q2*gx)*halfT;  
	
	// normalise quaternion
	norm = invSqrt(mpu->quaternion.q0*mpu->quaternion.q0 + mpu->quaternion.q1*mpu->quaternion.q1 \
			+ mpu->quaternion.q2*mpu->quaternion.q2 + mpu->quaternion.q3*mpu->quaternion.q3);
	mpu->quaternion.q0 = mpu->quaternion.q0 * norm;       //w
	mpu->quaternion.q1 = mpu->quaternion.q1 * norm;       //x
	mpu->quaternion.q2 = mpu->quaternion.q2 * norm;       //y
	mpu->quaternion.q3 = mpu->quaternion.q3 * norm;       //z
        
    //sensor.attitude.roll = sensor.attitude.float_roll = -90+atan2(vx,vz) * RAD; //�����ǣ���y��ת��	 
    //sensor.attitude.pitch = sensor.attitude.float_pitch =90-atan2(vx,vy)*RAD;
    //sensor.attitude.float_yaw = atan2(2*q1*q2 + 2*q0*q3,-2*q2*q2 - 2*q3*q3 + 1) * RAD;  //ƫ���ǣ���z��ת��
	//�Ӻ���ǰ���������������˳ʱ��Ϊ������ʱ��Ϊ����ƽ��0��ʵ��pitch����yaw��float��yaw��10����ǰ��������������ƽ��0��ʵ��yawû��Ӧ������ת��������û��Ӧ������pitch85
	mpu->attitude.roll = mpu->attitude.float_roll = -asin(vz) * RAD; //�����ǣ���y��ת��	 
    mpu->attitude.pitch = mpu->attitude.float_pitch =asin(vy)*RAD;
    mpu->attitude.float_yaw = asin(vx) * RAD;  //ƫ���ǣ���z��ת��
    mpu->attitude.yaw  = 10.0f * mpu->attitude.float_yaw;
	mpu->attitude.gyro_yaw = mpu->DMP_data.GYROz>>1;
	mpu->attitude.gyro_roll=mpu->DMP_data.GYROy;
	
}

void MPU6050_Data_Process(void)
{
    static uint16_t j=0;  
    static int16_t last_GYROz=0;
	struct Mpu6050 *mpu = &car.component.mpu6050;
	
	mpu->DMP_data.ACCx=-((mpu->data_buff[2]<<8)+mpu->data_buff[3]);    //��Ӧmpu6050��-accy
	mpu->DMP_data.ACCy =((mpu->data_buff[4]<<8)+mpu->data_buff[5]);    //��Ӧmpu6050��accz
	mpu->DMP_data.ACCz =-((mpu->data_buff[0]<<8)+mpu->data_buff[1]);   //��Ӧmpu6050��-accx
	mpu->DMP_data.GYROx = -((mpu->data_buff[10]<<8)+mpu->data_buff[11]);//��Ӧmpu6050��-gyroy	   
	mpu->DMP_data.GYROy = ((mpu->data_buff[12]<<8)+mpu->data_buff[13]); //��Ӧmpu6050��gyroz	
	mpu->DMP_data.GYROz = -((mpu->data_buff[8]<<8)+mpu->data_buff[9]);  //��Ӧmpu6050��-gyrox	
	//��λת���ɣ�����/s��0.000266=1/(Gyro_500_Scale_Factor * 57.3) 
	mpu->DMP_data.gx=(mpu->DMP_data.GYROx-mpu->gyro_offset[MPU6050_GYROX_OFFSET]) * Gyro_500_Rad_Factor;	   
	mpu->DMP_data.gy=(mpu->DMP_data.GYROy-mpu->gyro_offset[MPU6050_GYROY_OFFSET]) * Gyro_500_Rad_Factor;	   
	mpu->DMP_data.gz=(mpu->DMP_data.GYROz-mpu->gyro_offset[MPU6050_GYROZ_OFFSET]) * Gyro_500_Rad_Factor;
	
	mpu->DMP_data.ax=(mpu->DMP_data.ACCx); 	
	mpu->DMP_data.ay=(mpu->DMP_data.ACCy); 	   
	mpu->DMP_data.az=(mpu->DMP_data.ACCz); 
	
    if(mpu->get_offset_flag)
    {        
		IMUupdate(mpu->DMP_data.gx, mpu->DMP_data.gy, mpu->DMP_data.gz,\
		         mpu->DMP_data.ax,  mpu->DMP_data.ay,  mpu->DMP_data.az,  1, 1 ,  1) ;
       
    }
    else
    {  
		//���ڻ�����ֹ������±���ƫ��
        if((mpu->DMP_data.GYROz>last_GYROz-150)&&(mpu->DMP_data.GYROz<last_GYROz+150)\
			&&(mpu->DMP_data.GYROz<300)&&(mpu->DMP_data.GYROz>-300)) 			
		{
			j++;
		}
        else 
        {   
            j=0;        
            mpu->gyro_offset[MPU6050_GYROX_OFFSET]=0; 
            mpu->gyro_offset[MPU6050_GYROY_OFFSET]=0;
            mpu->gyro_offset[MPU6050_GYROZ_OFFSET]=0;
        }   //once MPU6050_GYROz is not similar to last,  reset.  
        if((j>200)&&(j<=600)) 
        {    
            mpu->gyro_offset[MPU6050_GYROX_OFFSET] += (float)mpu->DMP_data.GYROx;	
            mpu->gyro_offset[MPU6050_GYROY_OFFSET] += (float)mpu->DMP_data.GYROy;
            mpu->gyro_offset[MPU6050_GYROZ_OFFSET] += (float)mpu->DMP_data.GYROz;
        }					  
        last_GYROz=mpu->DMP_data.GYROz;
        if(j>600)
        {

            mpu->get_offset_flag=true; //if last for 4s,Get GYROzOffset successfully.  
            
            mpu->gyro_offset[MPU6050_GYROX_OFFSET]=mpu->gyro_offset[MPU6050_GYROX_OFFSET]/400.0f;
            mpu->gyro_offset[MPU6050_GYROY_OFFSET]=mpu->gyro_offset[MPU6050_GYROY_OFFSET]/400.0f;
            mpu->gyro_offset[MPU6050_GYROZ_OFFSET]=mpu->gyro_offset[MPU6050_GYROZ_OFFSET]/400.0f;

			flash_data.float_data[FLASH_ADDR_MPU6050_GYROX_OFFSET] = mpu->gyro_offset[MPU6050_GYROX_OFFSET];
			flash_data.float_data[FLASH_ADDR_MPU6050_GYROY_OFFSET] = mpu->gyro_offset[MPU6050_GYROY_OFFSET];
			flash_data.float_data[FLASH_ADDR_MPU6050_GYROZ_OFFSET] = mpu->gyro_offset[MPU6050_GYROZ_OFFSET];
			store_config_data();
					
//            MPU6050_GYROx_Offset_int=(int16_t)MPU6050_GYROx_Offset;
//            MPU6050_GYROy_Offset_int=(int16_t)MPU6050_GYROy_Offset;
//            MPU6050_GYROz_Offset_int=(int16_t)MPU6050_GYROz_Offset;
			
            j=0;
        }
    }        
				
}

void mpu6050_update(void)
{
	struct Mpu6050 *mpu = &car.component.mpu6050;
	//uint32_t start_time = uwTick;
	
	MPU_Read_Len(MPU_ADDR,MPU_ACCEL_XOUTH_REG,14,mpu->data_buff);	//��ȡ�����Ǻͼ��ٶȼ�����
	//sensor.attitude.error_counter =0;
	MPU6050_Data_Process();	
}

void mpu6050_task(void)
{
	mpu6050_update();	
}

//����MPU6050�����Ǵ����������̷�Χ
//fsr:0,��250dps;1,��500dps;2,��1000dps;3,��2000dps
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
u8 MPU_Set_Gyro_Fsr(u8 fsr)
{
	return MPU_Write_Byte(MPU_GYRO_CFG_REG,fsr<<3);//���������������̷�Χ  
}
//����MPU6050���ٶȴ����������̷�Χ
//fsr:0,��2g;1,��4g;2,��8g;3,��16g
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
u8 MPU_Set_Accel_Fsr(u8 fsr)
{
	return MPU_Write_Byte(MPU_ACCEL_CFG_REG,fsr<<3);//���ü��ٶȴ����������̷�Χ  
}
//����MPU6050�����ֵ�ͨ�˲���
//lpf:���ֵ�ͨ�˲�Ƶ��(Hz)
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
u8 MPU_Set_LPF(u16 lpf)
{
	u8 data=0;
	if(lpf>=188)data=1;
	else if(lpf>=98)data=2;
	else if(lpf>=42)data=3;
	else if(lpf>=20)data=4;
	else if(lpf>=10)data=5;
	else data=6; 
	return MPU_Write_Byte(MPU_CFG_REG,data);//�������ֵ�ͨ�˲���  
}
//����MPU6050�Ĳ�����(�ٶ�Fs=1KHz)
//rate:4~1000(Hz)
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
u8 MPU_Set_Rate(u16 rate)
{
	u8 data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	data=MPU_Write_Byte(MPU_SAMPLE_RATE_REG,data);	//�������ֵ�ͨ�˲���
 	return MPU_Set_LPF(rate/2);	//�Զ�����LPFΪ�����ʵ�һ��
}

//�õ��¶�ֵ
//����ֵ:�¶�ֵ(������100��)
short MPU_Get_Temperature(void)
{
    u8 buf[2]; 
    short raw;
	float temp;
	MPU_Read_Len(MPU_ADDR,MPU_TEMP_OUTH_REG,2,buf); 
    raw=((u16)buf[0]<<8)|buf[1];  
    temp=36.53+((double)raw)/340;  
    return temp*100;;
}
//�õ�������ֵ(ԭʼֵ)
//gx,gy,gz:������x,y,z���ԭʼ����(������)
//����ֵ:0,�ɹ�
//    ����,�������
u8 MPU_Get_Gyroscope(short *gx,short *gy,short *gz)
{
    u8 buf[6],res;  
	res=MPU_Read_Len(MPU_ADDR,MPU_GYRO_XOUTH_REG,6,buf);
	if(res==0)
	{
		*gx=((u16)buf[0]<<8)|buf[1];  
		*gy=((u16)buf[2]<<8)|buf[3];  
		*gz=((u16)buf[4]<<8)|buf[5];
	} 	
    return res;;
}
//�õ����ٶ�ֵ(ԭʼֵ)
//gx,gy,gz:������x,y,z���ԭʼ����(������)
//����ֵ:0,�ɹ�
//    ����,�������
u8 MPU_Get_Accelerometer(short *ax,short *ay,short *az)
{
    u8 buf[6],res;  
	res=MPU_Read_Len(MPU_ADDR,MPU_ACCEL_XOUTH_REG,6,buf);
	if(res==0)
	{
		*ax=((u16)buf[0]<<8)|buf[1];  
		*ay=((u16)buf[2]<<8)|buf[3];  
		*az=((u16)buf[4]<<8)|buf[5];
	} 	
    return res;;
}
//IIC����д
//addr:������ַ 
//reg:�Ĵ�����ַ
//len:д�볤��
//buf:������
//����ֵ:0,����
//    ����,�������
u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{
	u8 i; 
    IIC_Start(); 
	IIC_Send_Byte((addr<<1)|0);//����������ַ+д����	
	if(IIC_Wait_Ack())	//�ȴ�Ӧ��
	{
		IIC_Stop();		 
		return 1;		
	}
    IIC_Send_Byte(reg);	//д�Ĵ�����ַ
    IIC_Wait_Ack();		//�ȴ�Ӧ��
	for(i=0;i<len;i++)
	{
		IIC_Send_Byte(buf[i]);	//��������
		if(IIC_Wait_Ack())		//�ȴ�ACK
		{
			IIC_Stop();	 
			return 1;		 
		}		
	}    
    IIC_Stop();	 
	return 0;	
} 
//IIC������
//addr:������ַ
//reg:Ҫ��ȡ�ļĴ�����ַ
//len:Ҫ��ȡ�ĳ���
//buf:��ȡ�������ݴ洢��
//����ֵ:0,����
//    ����,�������
u8 MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{ 
 	IIC_Start(); 
	IIC_Send_Byte((addr<<1)|0);//����������ַ+д����	
	if(IIC_Wait_Ack())	//�ȴ�Ӧ��
	{
		IIC_Stop();		 
		return 1;		
	}
    IIC_Send_Byte(reg);	//д�Ĵ�����ַ
    IIC_Wait_Ack();		//�ȴ�Ӧ��
    IIC_Start();
	IIC_Send_Byte((addr<<1)|1);//����������ַ+������	
    IIC_Wait_Ack();		//�ȴ�Ӧ�� 
	while(len)
	{
		if(len==1)*buf=IIC_Read_Byte(0);//������,����nACK 
		else *buf=IIC_Read_Byte(1);		//������,����ACK  
		len--;
		buf++; 
	}    
    IIC_Stop();	//����һ��ֹͣ���� 
	return 0;	
}
//IICдһ���ֽ� 
//reg:�Ĵ�����ַ
//data:����
//����ֵ:0,����
//    ����,�������
u8 MPU_Write_Byte(u8 reg,u8 data) 				 
{ 
    IIC_Start(); 
	IIC_Send_Byte((MPU_ADDR<<1)|0);//����������ַ+д����	
	if(IIC_Wait_Ack())	//�ȴ�Ӧ��
	{
		IIC_Stop();		 
		return 1;		
	}
    IIC_Send_Byte(reg);	//д�Ĵ�����ַ
    IIC_Wait_Ack();		//�ȴ�Ӧ�� 
	IIC_Send_Byte(data);//��������
	if(IIC_Wait_Ack())	//�ȴ�ACK
	{
		IIC_Stop();	 
		return 1;		 
	}		 
    IIC_Stop();	 
	return 0;
}
//IIC��һ���ֽ� 
//reg:�Ĵ�����ַ 
//����ֵ:����������
u8 MPU_Read_Byte(u8 reg)
{
	u8 res;
    IIC_Start(); 
	IIC_Send_Byte((MPU_ADDR<<1)|0);//����������ַ+д����	
	IIC_Wait_Ack();		//�ȴ�Ӧ�� 
    IIC_Send_Byte(reg);	//д�Ĵ�����ַ
    IIC_Wait_Ack();		//�ȴ�Ӧ��
    IIC_Start();
	IIC_Send_Byte((MPU_ADDR<<1)|1);//����������ַ+������	
    IIC_Wait_Ack();		//�ȴ�Ӧ�� 
	res=IIC_Read_Byte(0);//��ȡ����,����nACK 
    IIC_Stop();			//����һ��ֹͣ���� 
	return res;		
}




