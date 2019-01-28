#ifndef __PARAMETER_H
#define __PARAMETER_H

/*******************************motor***********************************/
//用四节干电池供电，且在低电量时，单轮转，最低速500，四轮转最低速600
#define DC_MOTOR_STOP_SPEED 0
#define DC_MOTOR_HIGH_SPEED 1000

//设置转弯时四个轮子的速度，小半径转弯边速度低，半径转弯边速度高
#define DC_MOTOR_TURN_UP_LOW_SPEED 0  
#define DC_MOTOR_TURN_DOWN_LOW_SPEED 0
#define DC_MOTOR_TURN_UP_HIGH_SPEED 900
#define DC_MOTOR_TURN_DOWN_HIGH_SPEED 900

#endif
