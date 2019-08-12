#ifndef __FLOW_H
#define __FLOW_H

#include <stdbool.h>
#include "sys.h"
#include "car_system.h"

extern struct Flow init_flow;

void init_flow_map(void);
void flow_switch(void);
void flow_process(void);

#endif
