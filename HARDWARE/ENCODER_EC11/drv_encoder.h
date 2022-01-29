

#ifndef _DRC_RNCODER_H
#define _DRC_RNCODER_H

#include "drv_encoder.h"
#include "sys.h"

void TIM5_init(void);
uint16_t TIM5_read(void);
uint8_t enc_pressed (void);

#endif