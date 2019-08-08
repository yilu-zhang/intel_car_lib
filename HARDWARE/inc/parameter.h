#ifndef __PARAMETER_H
#define __PARAMETER_H

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

#endif
