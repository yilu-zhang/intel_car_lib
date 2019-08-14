#ifndef __PARAMETER_H
#define __PARAMETER_H

/*******************************auto_flow***********************************/
#define AUTO_FLOW_DELAY_TIME 1200
#define AUTO_FLOW_ADVANCE_OBSTACLE_DISTANCE 50
#define AUTO_FLOW_TURN_OBSTACLE_DISTANCE 100   //��ת��ʱ���ýϴ��ֵ�����ⷴ��̽��


/*******************************motor***********************************/
//���Ľڸɵ�ع��磬���ڵ͵���ʱ������ת�������500������ת�����600
#define DC_MOTOR_STOP_SPEED 0
#define DC_MOTOR_HIGH_SPEED 1200

//����ת��ʱ�ĸ����ӵ��ٶȣ�С�뾶ת����ٶȵͣ��뾶ת����ٶȸ�
//�ڼ���ذ�Ƚϻ���ת��ʱ����һ������ת����ʹ��һ���ֺ��ȵķ�ʽת�䣬���˷�ֹ����ǰ���ϰ���
#define DC_MOTOR_TURN_UP_LOW_SPEED 0  
#define DC_MOTOR_TURN_DOWN_LOW_SPEED 0
#define DC_MOTOR_TURN_UP_HIGH_SPEED 1900
#define DC_MOTOR_TURN_DOWN_HIGH_SPEED 1900

/*******************************infrared remote***********************************/
//����ң��ʶ����(ID),ÿ��ң�����ĸ�ֵ��������һ��,��Ҳ��һ����.
//����ѡ�õ�ң����ʶ����Ϊ0
#define REMOTE_ID 0  

#endif
