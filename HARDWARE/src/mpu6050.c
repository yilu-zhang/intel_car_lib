#include "mpu6050.h"
#include "flash.h"

//初始化MPU6050
//返回值:0,成功
//其他,错误代码
u8 mpu6050_Init(void)
{ 
	u8 res;
	IIC_Init();//初始化IIC总线
	MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X80);	//复位MPU6050
    delay_ms(100);
	MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X00);	//唤醒MPU6050 
	MPU_Set_Gyro_Fsr(1);					//陀螺仪传感器,±500dps
	MPU_Set_Accel_Fsr(0);					//加速度传感器,±2g
	MPU_Set_Rate(50);						//设置采样率50Hz
	MPU_Write_Byte(MPU_INT_EN_REG,0X00);	//关闭所有中断
	MPU_Write_Byte(MPU_USER_CTRL_REG,0X00);	//I2C主模式关闭
	MPU_Write_Byte(MPU_FIFO_EN_REG,0X00);	//关闭FIFO
	MPU_Write_Byte(MPU_INTBP_CFG_REG,0X80);	//INT引脚低电平有效
	res=MPU_Read_Byte(MPU_DEVICE_ID_REG);
	if(res==MPU_ADDR)//器件ID正确
	{
		MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X01);	//设置CLKSEL,PLL X轴为参考
		MPU_Write_Byte(MPU_PWR_MGMT2_REG,0X00);	//加速度与陀螺仪都工作
		MPU_Set_Rate(50);						//设置采样率为50Hz
 	}else return 1;
	return 0;
}

float invSqrt(float x)                     //快速求平方根倒数
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
* Description    : accel gyro mag的融合算法，源自S.O.H. Madgwick.
* Input          : None
* Output         : None
* Return         : None

// q0 q1 q2 q3需要初始化才能带入到下面的程序中，不能直接使用1 0 0 0进行下面的计算，整个步骤为：
// 1.首先校准accle gyro mag；
// 2.调用init_quaternion，根据1中accle的xyz轴数据，并利用公式计算出初始化欧拉角，
//   其中ACCEL_1G=9.81，单位都是m/s2，而init_Yaw可以用磁力计计算出来；
// 3.根据自己的采样周期，来调整halfT，halfT=采样周期/2，采样周期为执行1次AHRSupdate所用的时间；
// 4.将2中计算出的欧拉角转化为初始化的四元数q0 q1 q2 q3，融合加速度计，陀螺仪，算出更新后的欧拉角pitch和roll，然后使用pitch roll和磁力计的数据进行互补滤波融合得到Yaw，即可使用，但是欧拉角有奇点；
// 5.或直接使用四元数；
// 6.重复4，即可更新姿态;

//总的来说，核心是陀螺仪，加速度计用来修正补偿Pitch和Roll，磁力计用来修正补偿Yaw;
//以下程序中，gx, gy, gz单位为弧度/s，ax, ay, az为加速度计输出的原始16进制数据, mx, my, mz为磁力计输出的原始16进制数据；
//前进方向：mpu9150的加速度计和陀螺仪的x轴为前进方向;
//以下程序采用的参考方向为：mpu9150的加速度计和陀螺仪所指的xyz方向为正方向；

//在量程为正负500度/s的前提下，陀螺仪的灵敏度是65.5LSB/度/s，所以把陀螺仪输出的十六进制数据除以65.5就是角速度，单位是°/s，
//然后再除以57.3就变成弧度制;(1弧度=180/pi=57.3度)

//欧拉角单位为弧度radian，乘以57.3以后转换为角度
*******************************************************************************/
void IMUupdate(float gx, float gy, float gz, float ax, float ay, float az,\
             	float init_mx, float init_my, float init_mz) 
{
	float norm;
	float vx, vy, vz;
	float ex, ey, ez;
	struct Mpu6050 *mpu = &car.component.mpu6050;
	/*归一化测量值，加速度计和磁力计的单位是什么都无所谓，因为它们在此被作了归一化处理*/        
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
	
	//现在把加速度的测量矢量和参考矢量做叉积，把磁场的测量矢量和参考矢量也做叉积。都拿来来修正陀螺。
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
	

	// integrate quaternion rate and normalise，四元数更新算法，一阶龙格-库塔法
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
        
    //sensor.attitude.roll = sensor.attitude.float_roll = -90+atan2(vx,vz) * RAD; //俯仰角，绕y轴转动	 
    //sensor.attitude.pitch = sensor.attitude.float_pitch =90-atan2(vx,vy)*RAD;
    //sensor.attitude.float_yaw = atan2(2*q1*q2 + 2*q0*q3,-2*q2*q2 - 2*q3*q3 + 1) * RAD;  //偏航角，绕z轴转动
	//从后往前看，横滚角正常，顺时针为负，逆时针为正，平放0；实际pitch对着yaw，float是yaw的10倍，前倾正，后仰负，平放0；实际yaw没反应，左右转三个方向都没反应；测试pitch85
	mpu->attitude.roll = mpu->attitude.float_roll = -asin(vz) * RAD; //俯仰角，绕y轴转动	 
    mpu->attitude.pitch = mpu->attitude.float_pitch =asin(vy)*RAD;
    mpu->attitude.float_yaw = asin(vx) * RAD;  //偏航角，绕z轴转动
    mpu->attitude.yaw  = 10.0f * mpu->attitude.float_yaw;
	mpu->attitude.gyro_yaw = mpu->DMP_data.GYROz>>1;
	mpu->attitude.gyro_roll=mpu->DMP_data.GYROy;
	
}

void MPU6050_Data_Process(void)
{
    static uint16_t j=0;  
    static int16_t last_GYROz=0;
	struct Mpu6050 *mpu = &car.component.mpu6050;
	
	mpu->DMP_data.ACCx=-((mpu->data_buff[2]<<8)+mpu->data_buff[3]);    //对应mpu6050的-accy
	mpu->DMP_data.ACCy =((mpu->data_buff[4]<<8)+mpu->data_buff[5]);    //对应mpu6050的accz
	mpu->DMP_data.ACCz =-((mpu->data_buff[0]<<8)+mpu->data_buff[1]);   //对应mpu6050的-accx
	mpu->DMP_data.GYROx = -((mpu->data_buff[10]<<8)+mpu->data_buff[11]);//对应mpu6050的-gyroy	   
	mpu->DMP_data.GYROy = ((mpu->data_buff[12]<<8)+mpu->data_buff[13]); //对应mpu6050的gyroz	
	mpu->DMP_data.GYROz = -((mpu->data_buff[8]<<8)+mpu->data_buff[9]);  //对应mpu6050的-gyrox	
	//单位转化成：弧度/s，0.000266=1/(Gyro_500_Scale_Factor * 57.3) 
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
		//需在机器静止的情况下保存偏置
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
	
	MPU_Read_Len(MPU_ADDR,MPU_ACCEL_XOUTH_REG,14,mpu->data_buff);	//读取陀螺仪和加速度计数据
	//sensor.attitude.error_counter =0;
	MPU6050_Data_Process();	
}

void mpu6050_task(void)
{
	mpu6050_update();	
}

//设置MPU6050陀螺仪传感器满量程范围
//fsr:0,±250dps;1,±500dps;2,±1000dps;3,±2000dps
//返回值:0,设置成功
//    其他,设置失败 
u8 MPU_Set_Gyro_Fsr(u8 fsr)
{
	return MPU_Write_Byte(MPU_GYRO_CFG_REG,fsr<<3);//设置陀螺仪满量程范围  
}
//设置MPU6050加速度传感器满量程范围
//fsr:0,±2g;1,±4g;2,±8g;3,±16g
//返回值:0,设置成功
//    其他,设置失败 
u8 MPU_Set_Accel_Fsr(u8 fsr)
{
	return MPU_Write_Byte(MPU_ACCEL_CFG_REG,fsr<<3);//设置加速度传感器满量程范围  
}
//设置MPU6050的数字低通滤波器
//lpf:数字低通滤波频率(Hz)
//返回值:0,设置成功
//    其他,设置失败 
u8 MPU_Set_LPF(u16 lpf)
{
	u8 data=0;
	if(lpf>=188)data=1;
	else if(lpf>=98)data=2;
	else if(lpf>=42)data=3;
	else if(lpf>=20)data=4;
	else if(lpf>=10)data=5;
	else data=6; 
	return MPU_Write_Byte(MPU_CFG_REG,data);//设置数字低通滤波器  
}
//设置MPU6050的采样率(假定Fs=1KHz)
//rate:4~1000(Hz)
//返回值:0,设置成功
//    其他,设置失败 
u8 MPU_Set_Rate(u16 rate)
{
	u8 data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	data=MPU_Write_Byte(MPU_SAMPLE_RATE_REG,data);	//设置数字低通滤波器
 	return MPU_Set_LPF(rate/2);	//自动设置LPF为采样率的一半
}

//得到温度值
//返回值:温度值(扩大了100倍)
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
//得到陀螺仪值(原始值)
//gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
//返回值:0,成功
//    其他,错误代码
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
//得到加速度值(原始值)
//gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
//返回值:0,成功
//    其他,错误代码
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
//IIC连续写
//addr:器件地址 
//reg:寄存器地址
//len:写入长度
//buf:数据区
//返回值:0,正常
//    其他,错误代码
u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{
	u8 i; 
    IIC_Start(); 
	IIC_Send_Byte((addr<<1)|0);//发送器件地址+写命令	
	if(IIC_Wait_Ack())	//等待应答
	{
		IIC_Stop();		 
		return 1;		
	}
    IIC_Send_Byte(reg);	//写寄存器地址
    IIC_Wait_Ack();		//等待应答
	for(i=0;i<len;i++)
	{
		IIC_Send_Byte(buf[i]);	//发送数据
		if(IIC_Wait_Ack())		//等待ACK
		{
			IIC_Stop();	 
			return 1;		 
		}		
	}    
    IIC_Stop();	 
	return 0;	
} 
//IIC连续读
//addr:器件地址
//reg:要读取的寄存器地址
//len:要读取的长度
//buf:读取到的数据存储区
//返回值:0,正常
//    其他,错误代码
u8 MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{ 
 	IIC_Start(); 
	IIC_Send_Byte((addr<<1)|0);//发送器件地址+写命令	
	if(IIC_Wait_Ack())	//等待应答
	{
		IIC_Stop();		 
		return 1;		
	}
    IIC_Send_Byte(reg);	//写寄存器地址
    IIC_Wait_Ack();		//等待应答
    IIC_Start();
	IIC_Send_Byte((addr<<1)|1);//发送器件地址+读命令	
    IIC_Wait_Ack();		//等待应答 
	while(len)
	{
		if(len==1)*buf=IIC_Read_Byte(0);//读数据,发送nACK 
		else *buf=IIC_Read_Byte(1);		//读数据,发送ACK  
		len--;
		buf++; 
	}    
    IIC_Stop();	//产生一个停止条件 
	return 0;	
}
//IIC写一个字节 
//reg:寄存器地址
//data:数据
//返回值:0,正常
//    其他,错误代码
u8 MPU_Write_Byte(u8 reg,u8 data) 				 
{ 
    IIC_Start(); 
	IIC_Send_Byte((MPU_ADDR<<1)|0);//发送器件地址+写命令	
	if(IIC_Wait_Ack())	//等待应答
	{
		IIC_Stop();		 
		return 1;		
	}
    IIC_Send_Byte(reg);	//写寄存器地址
    IIC_Wait_Ack();		//等待应答 
	IIC_Send_Byte(data);//发送数据
	if(IIC_Wait_Ack())	//等待ACK
	{
		IIC_Stop();	 
		return 1;		 
	}		 
    IIC_Stop();	 
	return 0;
}
//IIC读一个字节 
//reg:寄存器地址 
//返回值:读到的数据
u8 MPU_Read_Byte(u8 reg)
{
	u8 res;
    IIC_Start(); 
	IIC_Send_Byte((MPU_ADDR<<1)|0);//发送器件地址+写命令	
	IIC_Wait_Ack();		//等待应答 
    IIC_Send_Byte(reg);	//写寄存器地址
    IIC_Wait_Ack();		//等待应答
    IIC_Start();
	IIC_Send_Byte((MPU_ADDR<<1)|1);//发送器件地址+读命令	
    IIC_Wait_Ack();		//等待应答 
	res=IIC_Read_Byte(0);//读取数据,发送nACK 
    IIC_Stop();			//产生一个停止条件 
	return res;		
}




