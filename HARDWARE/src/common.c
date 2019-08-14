//可供所有模块调用的函数
#include "common.h"

uint16_t window_average_filter(struct Window_Filter_Struct *filter_data, uint16_t new_data)
{	
	filter_data->acc = filter_data->acc+new_data-filter_data->data[filter_data->counter];
	filter_data->data[filter_data->counter++] = new_data;
	filter_data->counter &=0x07;
	filter_data->result = filter_data->acc>>3;
	return (filter_data->acc>>3);
}
