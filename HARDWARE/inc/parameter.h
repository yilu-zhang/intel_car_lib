#ifndef __PARAMETER_H
#define __PARAMETER_H

/*******************************auto_flow***********************************/
#define AUTO_FLOW_DELAY_TIME 1200
#define AUTO_FLOW_ADVANCE_OBSTACLE_DISTANCE 50
#define AUTO_FLOW_TURN_OBSTACLE_DISTANCE 100   //在转弯时设置较大的值，避免反复探测


/*******************************motor***********************************/
//用四节干电池供电，且在低电量时，单轮转，最低速500，四轮转最低速600
#define DC_MOTOR_STOP_SPEED 0
#define DC_MOTOR_HIGH_SPEED 1200

//设置转弯时四个轮子的速度，小半径转弯边速度低，半径转弯边速度高
//在家里地板比较滑，转弯时常绕一个轮子转，故使用一边轮后腿的方式转弯，后退防止靠近前方障碍物
#define DC_MOTOR_TURN_UP_LOW_SPEED 0  
#define DC_MOTOR_TURN_DOWN_LOW_SPEED 0
#define DC_MOTOR_TURN_UP_HIGH_SPEED 1900
#define DC_MOTOR_TURN_DOWN_HIGH_SPEED 1900

/*******************************infrared remote***********************************/
//红外遥控识别码(ID),每款遥控器的该值基本都不一样,但也有一样的.
//我们选用的遥控器识别码为0
#define REMOTE_ID 0  

#endif
