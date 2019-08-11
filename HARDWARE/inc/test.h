#ifndef __COMMON_H
#define __COMMON_H

#include "wheel.h"
#include "infrared_remote.h"
#include "sfr.h"
#include "mpu6050.h"
#include "flash.h"
#include "delay.h"
#include "sfr.h"
#include "ultrasonic.h"


void test(void);
void infrared_remote_test(void);
void mpu6050_test(void);
void flash_test(void);
void systick_test(void);
void ultrasonic_test(void);
void steering_engine_test(void);

#endif
