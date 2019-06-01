/*
 * platform_config.h
 *
 * Copyright 2018 Dimitris Tassopoulos
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 */

#ifndef __PLATFORM_CONFIG_H
#define __PLATFORM_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include "stm32f10x.h"
#include "misc.h"

/**
 * Trace levels for this project.
 * Have in mind that these are bit flags!
 */
enum en_trace_level {
	TRACE_LEVEL_DEFAULT = 	(1 << 0),
	TRACE_LEVEL_SPI = 		(1 << 1),
	TRACE_LEVEL_I2C = 		(1 << 2),
	TRACE_LEVEL_UART = 		(1 << 3),
	TRACE_LEVEL_PWM = 		(1 << 4),
	TRACE_LEVEL_ADC = 		(1 << 5),
};

#define DEBUG_TRACE

#ifdef DEBUG_TRACE
#define TRACE(X) TRACEL(TRACE_LEVEL_DEFAULT, X)
#define TRACEL(TRACE_LEVEL, X) do { if (glb.trace_levels & TRACE_LEVEL) printf X;} while(0)
#else
#define TRACE(X)
#define TRACEL(X,Y)
#endif


#define USE_DEBUG_PIN
#define DEBUG_PIN	GPIO_Pin_14
#define DEBUG_PORT 	GPIOC

/* on reset all of these will be set to 0 */
struct tp_glb {
	uint16_t	tmr_1ms;
	uint8_t		mode;
	uint32_t trace_levels;
};

extern volatile struct tp_glb glb;

static inline void set_trace_level(uint32_t level, uint8_t enable)
{
	if (enable) {
		glb.trace_levels |= level;
	}
	else {
		glb.trace_levels &= ~level;
	}
}

#ifdef __cplusplus
}
#endif

#endif /* __PLATFORM_CONFIG_H */
