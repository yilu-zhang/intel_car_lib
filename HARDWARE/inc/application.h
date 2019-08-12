#ifndef __APPLICATION_H
#define __APPLICATION_H

#include "wheel.h"
#include "infrared_remote.h"
#include "ultrasonic.h"
#include "mpu6050.h"

void motion_init(void);
void motion_control(void);
void communication_task(void);
void update_sensor_data(void);

#endif



