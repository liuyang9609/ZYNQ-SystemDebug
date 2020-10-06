#include"xgpiops.h"

#ifndef EMIO_INITIAL_H_
#define EMIO_INITIAL_H_

int Miz702_EMIO_init(void);

#define SCL_PIN_0 54
#define SDA_PIN_0 55

#define SCL_PIN_1 56
#define SDA_PIN_1 57

#define DIRECTION_INPUT 5
#define DIRECTION_OUTPUT 1

void CLOCK_HIGH(void);

void CLOCK_LOW(void);

void DATA_HIGH(void);

void DATA_LOW(void);

#endif