#ifndef _MAX_HPP
#define _MAX_HPP

#include <stdio.h>
#include <math.h>

#define MAX_THREADS 64
#define SUBDATANUM 2000000
#define DATANUM (SUBDATANUM * MAX_THREADS) /*这个数值是总数据量*/

extern float rawFloatData[DATANUM];

float Max(const float data[], const int len);
float MaxSpeedUp(const float data[], const int len);

void InitData(const float data[], const size_t len);

#endif