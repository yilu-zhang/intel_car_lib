#ifndef __COMMON_H
#define __COMMON_H

#include "sys.h"
#include "ultrasonic.h"

uint16_t window_average_filter(struct Window_Filter_Struct *filter_data, uint16_t new_data);

#endif

