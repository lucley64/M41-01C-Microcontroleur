/**
 * \file
 *
 * \brief Parallel Input/Output (PIO) Controller driver for SAM.
 *
 * Copyright (c) 2011-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef PERIPHS_H_INCLUDED
#define PERIPHS_H_INCLUDED

//#include "compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

/* GPIO Support */
#define PIO_TYPE_Pos                  27
/* PIO Type Mask */
#define PIO_TYPE_Msk                  (0xFu << PIO_TYPE_Pos)
/* The pin is not a function pin. */
#define PIO_TYPE_NOT_A_PIN            (0x0u << PIO_TYPE_Pos)
/* The pin is controlled by the peripheral A. */
#define PIO_TYPE_PIO_PERIPH_A         (0x1u << PIO_TYPE_Pos)
/* The pin is controlled by the peripheral B. */
#define PIO_TYPE_PIO_PERIPH_B         (0x2u << PIO_TYPE_Pos)
/* The pin is controlled by the peripheral C. */
#define PIO_TYPE_PIO_PERIPH_C         (0x3u << PIO_TYPE_Pos)
/* The pin is controlled by the peripheral D. */
#define PIO_TYPE_PIO_PERIPH_D         (0x4u << PIO_TYPE_Pos)
/* The pin is an input. */
#define PIO_TYPE_PIO_INPUT            (0x5u << PIO_TYPE_Pos)
/* The pin is an output and has a default level of 0. */
#define PIO_TYPE_PIO_OUTPUT_0         (0x6u << PIO_TYPE_Pos)
/* The pin is an output and has a default level of 1. */
#define PIO_TYPE_PIO_OUTPUT_1         (0x7u << PIO_TYPE_Pos)

typedef enum _pio_type {
	PIO_NOT_A_PIN   = PIO_TYPE_NOT_A_PIN,
	PIO_PERIPH_A    = PIO_TYPE_PIO_PERIPH_A,
	PIO_PERIPH_B    = PIO_TYPE_PIO_PERIPH_B,
	PIO_INPUT       = PIO_TYPE_PIO_INPUT,
	PIO_OUTPUT_0    = PIO_TYPE_PIO_OUTPUT_0,
	PIO_OUTPUT_1    = PIO_TYPE_PIO_OUTPUT_1
} pio_type_t;

/*  Default pin configuration (no attribute). */
#define PIO_DEFAULT             (0u << 0)
/*  The internal pin pull-up is active. */
#define PIO_PULLUP              (1u << 0)
/*  The internal glitch filter is active. */
#define PIO_DEGLITCH            (1u << 1)
/*  The pin is open-drain. */
#define PIO_OPENDRAIN           (1u << 2)

/*  The internal debouncing filter is active. */
#define PIO_DEBOUNCE            (1u << 3)

/*  Enable additional interrupt modes. */
#define PIO_IT_AIME             (1u << 4)

/*  Interrupt High Level/Rising Edge detection is active. */
#define PIO_IT_RE_OR_HL         (1u << 5)
/*  Interrupt Edge detection is active. */
#define PIO_IT_EDGE             (1u << 6)

/*  Low level interrupt is active */
#define PIO_IT_LOW_LEVEL        (0               | 0 | PIO_IT_AIME)
/*  High level interrupt is active */
#define PIO_IT_HIGH_LEVEL       (PIO_IT_RE_OR_HL | 0 | PIO_IT_AIME)
/*  Falling edge interrupt is active */
#define PIO_IT_FALL_EDGE        (0               | PIO_IT_EDGE | PIO_IT_AIME)
/*  Rising edge interrupt is active */
#define PIO_IT_RISE_EDGE        (PIO_IT_RE_OR_HL | PIO_IT_EDGE | PIO_IT_AIME)


// Timers
#define   TC_CMR_TCCLKS_TIMER_CLOCK1 (0x0u << 0) /**< \brief (TC_CMR) Clock selected: TCLK1 */
#define   TC_CMR_TCCLKS_TIMER_CLOCK2 (0x1u << 0) /**< \brief (TC_CMR) Clock selected: TCLK2 */
#define   TC_CMR_TCCLKS_TIMER_CLOCK3 (0x2u << 0) /**< \brief (TC_CMR) Clock selected: TCLK3 */
#define   TC_CMR_TCCLKS_TIMER_CLOCK4 (0x3u << 0) /**< \brief (TC_CMR) Clock selected: TCLK4 */
#define   TC_CMR_TCCLKS_TIMER_CLOCK5 (0x4u << 0) /**< \brief (TC_CMR) Clock selected: TCLK5 */

#define TC_SR_COVFS (0x1u << 0) /**< \brief (TC_SR) Counter Overflow Status */
#define TC_SR_LOVRS (0x1u << 1) /**< \brief (TC_SR) Load Overrun Status */
#define TC_SR_CPAS (0x1u << 2) /**< \brief (TC_SR) RA Compare Status */
#define TC_SR_CPBS (0x1u << 3) /**< \brief (TC_SR) RB Compare Status */
#define TC_SR_CPCS (0x1u << 4) /**< \brief (TC_SR) RC Compare Status */
#define TC_SR_LDRAS (0x1u << 5) /**< \brief (TC_SR) RA Loading Status */
#define TC_SR_LDRBS (0x1u << 6) /**< \brief (TC_SR) RB Loading Status */
#define TC_SR_ETRGS (0x1u << 7) /**< \brief (TC_SR) External Trigger Status */
#define TC_SR_CLKSTA (0x1u << 16) /**< \brief (TC_SR) Clock Enabling Status */
#define TC_SR_MTIOA (0x1u << 17) /**< \brief (TC_SR) TIOA Mirror */
#define TC_SR_MTIOB (0x1u << 18) /**< \brief (TC_SR) TIOB Mirror */

// CA/N

#define   ADC_MR_LOWRES_BITS_12 (0x0u << 4) /**< \brief (ADC_MR) 12-bit resolution */
#define   ADC_MR_LOWRES_BITS_10 (0x1u << 4) /**< \brief (ADC_MR) 10-bit resolution */

#define   ADC_MR_STARTUP_SUT0 (0x0u << 16) /**< \brief (ADC_MR) 0 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT8 (0x1u << 16) /**< \brief (ADC_MR) 8 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT16 (0x2u << 16) /**< \brief (ADC_MR) 16 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT24 (0x3u << 16) /**< \brief (ADC_MR) 24 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT64 (0x4u << 16) /**< \brief (ADC_MR) 64 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT80 (0x5u << 16) /**< \brief (ADC_MR) 80 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT96 (0x6u << 16) /**< \brief (ADC_MR) 96 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT112 (0x7u << 16) /**< \brief (ADC_MR) 112 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT512 (0x8u << 16) /**< \brief (ADC_MR) 512 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT576 (0x9u << 16) /**< \brief (ADC_MR) 576 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT640 (0xAu << 16) /**< \brief (ADC_MR) 640 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT704 (0xBu << 16) /**< \brief (ADC_MR) 704 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT768 (0xCu << 16) /**< \brief (ADC_MR) 768 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT832 (0xDu << 16) /**< \brief (ADC_MR) 832 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT896 (0xEu << 16) /**< \brief (ADC_MR) 896 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT960 (0xFu << 16) /**< \brief (ADC_MR) 960 periods of ADCClock */

enum adc_startup_time {
	ADC_STARTUP_TIME_0 = ADC_MR_STARTUP_SUT0,
	ADC_STARTUP_TIME_1 = ADC_MR_STARTUP_SUT8,
	ADC_STARTUP_TIME_2 = ADC_MR_STARTUP_SUT16,
	ADC_STARTUP_TIME_3 = ADC_MR_STARTUP_SUT24,
	ADC_STARTUP_TIME_4 = ADC_MR_STARTUP_SUT64,
	ADC_STARTUP_TIME_5 = ADC_MR_STARTUP_SUT80,
	ADC_STARTUP_TIME_6 = ADC_MR_STARTUP_SUT96,
	ADC_STARTUP_TIME_7 = ADC_MR_STARTUP_SUT112,
	ADC_STARTUP_TIME_8 = ADC_MR_STARTUP_SUT512,
	ADC_STARTUP_TIME_9 = ADC_MR_STARTUP_SUT576,
	ADC_STARTUP_TIME_10 = ADC_MR_STARTUP_SUT640,
	ADC_STARTUP_TIME_11 = ADC_MR_STARTUP_SUT704,
	ADC_STARTUP_TIME_12 = ADC_MR_STARTUP_SUT768,
	ADC_STARTUP_TIME_13 = ADC_MR_STARTUP_SUT832,
	ADC_STARTUP_TIME_14 = ADC_MR_STARTUP_SUT896,
	ADC_STARTUP_TIME_15 = ADC_MR_STARTUP_SUT960
};

#define   ADC_MR_SETTLING_AST3 (0x0u << 20) /**< \brief (ADC_MR) 3 periods of ADCClock */
#define   ADC_MR_SETTLING_AST5 (0x1u << 20) /**< \brief (ADC_MR) 5 periods of ADCClock */
#define   ADC_MR_SETTLING_AST9 (0x2u << 20) /**< \brief (ADC_MR) 9 periods of ADCClock */
#define   ADC_MR_SETTLING_AST17 (0x3u << 20) /**< \brief (ADC_MR) 17 periods of ADCClock */

enum adc_settling_time_t {
	ADC_SETTLING_TIME_0 = ADC_MR_SETTLING_AST3,
	ADC_SETTLING_TIME_1 = ADC_MR_SETTLING_AST5,
	ADC_SETTLING_TIME_2 = ADC_MR_SETTLING_AST9,
	ADC_SETTLING_TIME_3 = ADC_MR_SETTLING_AST17
};

#define ADC_MR_TRGEN (0x1u << 0) /**< \brief (ADC_MR) Trigger Enable */
#define   ADC_MR_TRGEN_DIS (0x0u << 0) /**< \brief (ADC_MR) Hardware triggers are disabled. Starting a conversion is only possible by software. */
#define   ADC_MR_TRGEN_EN (0x1u << 0) /**< \brief (ADC_MR) Hardware trigger selected by TRGSEL field is enabled. */
#define   ADC_MR_TRGSEL_ADC_TRIG0 (0x0u << 1) /**< \brief (ADC_MR) External : ADCTRG */
#define   ADC_MR_TRGSEL_ADC_TRIG1 (0x1u << 1) /**< \brief (ADC_MR) TIOA Output of the Timer Counter Channel 0 */
#define   ADC_MR_TRGSEL_ADC_TRIG2 (0x2u << 1) /**< \brief (ADC_MR) TIOA Output of the Timer Counter Channel 1 */
#define   ADC_MR_TRGSEL_ADC_TRIG3 (0x3u << 1) /**< \brief (ADC_MR) TIOA Output of the Timer Counter Channel 2 */
#define   ADC_MR_TRGSEL_ADC_TRIG4 (0x4u << 1) /**< \brief (ADC_MR) PWM Event Line 0 */
#define   ADC_MR_TRGSEL_ADC_TRIG5 (0x5u << 1) /**< \brief (ADC_MR) PWM Event Line 0 */

enum adc_trigger_t {
	/* Starting a conversion is only possible by software. */
	ADC_TRIG_SW = ADC_MR_TRGEN_DIS,
	/* External trigger */
	ADC_TRIG_EXT = ADC_MR_TRGSEL_ADC_TRIG0 | ADC_MR_TRGEN,
	/* TIO Output of the Timer Counter Channel 0 */
	ADC_TRIG_TIO_CH_0 = ADC_MR_TRGSEL_ADC_TRIG1 | ADC_MR_TRGEN,
	/* TIO Output of the Timer Counter Channel 1 */
	ADC_TRIG_TIO_CH_1 = ADC_MR_TRGSEL_ADC_TRIG2 | ADC_MR_TRGEN,
	/* TIO Output of the Timer Counter Channel 2 */
	ADC_TRIG_TIO_CH_2 = ADC_MR_TRGSEL_ADC_TRIG3 | ADC_MR_TRGEN,
	/* PWM Event Line 0 */
	ADC_TRIG_PWM_EVENT_LINE_0 = ADC_MR_TRGSEL_ADC_TRIG4 | ADC_MR_TRGEN,
	/* PWM Event Line 1 */
	ADC_TRIG_PWM_EVENT_LINE_1 = ADC_MR_TRGSEL_ADC_TRIG5 | ADC_MR_TRGEN
};

enum adc_channel_num_t {
	ADC_CHANNEL_0  = 0,
	ADC_CHANNEL_1  = 1,
	ADC_CHANNEL_2  = 2,
	ADC_CHANNEL_3  = 3,
	ADC_CHANNEL_4  = 4,
	ADC_CHANNEL_5  = 5,
	ADC_CHANNEL_6  = 6,
	ADC_CHANNEL_7  = 7,
	ADC_CHANNEL_8  = 8,
	ADC_CHANNEL_9  = 9,
	ADC_CHANNEL_10 = 10,
	ADC_CHANNEL_11 = 11,
	ADC_CHANNEL_12 = 12,
	ADC_CHANNEL_13 = 13,
	ADC_CHANNEL_14 = 14,
	ADC_TEMPERATURE_SENSOR = 15,
};

/* -------- ADC_ISR : (ADC Offset: 0x30) Interrupt Status Register -------- */
#define ADC_ISR_EOC0 (0x1u << 0) /**< \brief (ADC_ISR) End of Conversion 0 */
#define ADC_ISR_EOC1 (0x1u << 1) /**< \brief (ADC_ISR) End of Conversion 1 */
#define ADC_ISR_EOC2 (0x1u << 2) /**< \brief (ADC_ISR) End of Conversion 2 */
#define ADC_ISR_EOC3 (0x1u << 3) /**< \brief (ADC_ISR) End of Conversion 3 */
#define ADC_ISR_EOC4 (0x1u << 4) /**< \brief (ADC_ISR) End of Conversion 4 */
#define ADC_ISR_EOC5 (0x1u << 5) /**< \brief (ADC_ISR) End of Conversion 5 */
#define ADC_ISR_EOC6 (0x1u << 6) /**< \brief (ADC_ISR) End of Conversion 6 */
#define ADC_ISR_EOC7 (0x1u << 7) /**< \brief (ADC_ISR) End of Conversion 7 */
#define ADC_ISR_EOC8 (0x1u << 8) /**< \brief (ADC_ISR) End of Conversion 8 */
#define ADC_ISR_EOC9 (0x1u << 9) /**< \brief (ADC_ISR) End of Conversion 9 */
#define ADC_ISR_EOC10 (0x1u << 10) /**< \brief (ADC_ISR) End of Conversion 10 */
#define ADC_ISR_EOC11 (0x1u << 11) /**< \brief (ADC_ISR) End of Conversion 11 */
#define ADC_ISR_EOC12 (0x1u << 12) /**< \brief (ADC_ISR) End of Conversion 12 */
#define ADC_ISR_EOC13 (0x1u << 13) /**< \brief (ADC_ISR) End of Conversion 13 */
#define ADC_ISR_EOC14 (0x1u << 14) /**< \brief (ADC_ISR) End of Conversion 14 */
#define ADC_ISR_EOC15 (0x1u << 15) /**< \brief (ADC_ISR) End of Conversion 15 */
#define ADC_ISR_DRDY (0x1u << 24) /**< \brief (ADC_ISR) Data Ready */
#define ADC_ISR_GOVRE (0x1u << 25) /**< \brief (ADC_ISR) General Overrun Error */
#define ADC_ISR_COMPE (0x1u << 26) /**< \brief (ADC_ISR) Comparison Error */
#define ADC_ISR_ENDRX (0x1u << 27) /**< \brief (ADC_ISR) End of RX Buffer */
#define ADC_ISR_RXBUFF (0x1u << 28) /**< \brief (ADC_ISR) RX Buffer Full */


#define PWM_CLOCK_DIV_MAX  255
#define PWM_CLOCK_PRE_MAX  11
#define PWM_INVALID_ARGUMENT  0xFFFF

typedef enum {
	PWM_ALIGN_LEFT = (0 << 8),   /* The period is left aligned. */
	PWM_ALIGN_CENTER = (1 << 8)  /* The period is center aligned. */
} pwm_align_t;

typedef enum {
	PWM_LOW = LOW,     /* Low level */
	PWM_HIGH = HIGH,  /* High level */
} pwm_level_t;

typedef struct {
	/** Boolean of using override output as PWMH */
	bool b_override_pwmh;
	/** Boolean of using override output as PWML */
	bool b_override_pwml;
	/** Level of override output for PWMH */
	pwm_level_t override_level_pwmh;
	/** Level of override output for PWML */
	pwm_level_t override_level_pwml;
} pwm_output_t;

typedef enum {
	PWM_FAULT_PWMFI0 = (1 << 0),
	PWM_FAULT_PWMFI1 = (1 << 1),
	PWM_FAULT_PWMFI2 = (1 << 2),
	PWM_FAULT_MAINOSC = (1 << 3),
	PWM_FAULT_ADC = (1 << 4),
	PWM_FAULT_TIMER_0 = (1 << 5),
} pwm_fault_id_t;

typedef enum {
	PWM_EVENT_PERIOD_END = (0 << 10),      /* The channel counter event occurs at the end of the PWM period. */
	PWM_EVENT_PERIOD_HALF_END = (1 << 10)  /* The channel counter event occurs at the half of the PWM period. */
} pwm_counter_event_t;

typedef enum _pwm_ch_t {
	PWM_CHANNEL_0 = 0,
	PWM_CHANNEL_1 = 1,
	PWM_CHANNEL_2 = 2,
	PWM_CHANNEL_3 = 3,
	PWM_CHANNEL_4 = 4,
	PWM_CHANNEL_5 = 5,
	PWM_CHANNEL_6 = 6,
	PWM_CHANNEL_7 = 7
} pwm_ch_t;

typedef struct {
	bool initialise;
	/** Channel number */
	uint32_t channel;
	/** Channel prescaler */
	uint32_t ul_prescaler;
	/** Channel alignment */
	pwm_align_t alignment;
	/** Channel initial polarity */
	pwm_level_t polarity;
	/** Duty Cycle Value */
	uint32_t ul_duty;
	/** Period Cycle Value */
	uint32_t ul_period;
	/** Channel counter event */
	pwm_counter_event_t counter_event;
	/** Boolean of channel dead-time generator */
	bool b_deadtime_generator;
	/** Boolean of channel dead-time PWMH output inverted */
	bool b_pwmh_output_inverted;
	/** Boolean of channel dead-time PWML output inverted */
	bool b_pwml_output_inverted;
	/** Dead-time Value for PWMH Output */
	uint16_t us_deadtime_pwmh;
	/** Dead-time Value for PWML Output */
	uint16_t us_deadtime_pwml;
	/** Channel output */
	pwm_output_t output_selection;
	/** Boolean of Synchronous Channel */
	bool b_sync_ch;
	/** Fault ID of the channel */
	pwm_fault_id_t fault_id;
	/** Channel PWMH output level in fault protection */
	pwm_level_t ul_fault_output_pwmh;
	/** Channel PWML output level in fault protection */
	pwm_level_t ul_fault_output_pwml;
} pwm_channel_t;

#ifdef __cplusplus
}
#endif

#endif /* PERIPHS_H_INCLUDED */
