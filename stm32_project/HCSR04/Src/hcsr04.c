/*
 * hcsr04.c
 *
 *  Created on: Jan 23, 2026
 *      Author: ivkov
 */

#include "hcsr04.h"
#include "main.h"   

static TIM_HandleTypeDef *s_htim = NULL;
static uint32_t s_channel = 0;

static volatile uint32_t s_t_rise = 0;
static volatile uint32_t s_t_fall = 0;
static volatile uint32_t s_pulse_us = 0;
static volatile uint8_t  s_ready = 0;
static volatile uint8_t  s_waiting_fall = 0;
static uint32_t s_start_ms = 0;
static volatile uint8_t s_timed_out = 0;


static uint8_t s_dwt_inited = 0;

static void dwt_init_once(void)
{
    if (s_dwt_inited) return;

    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

    s_dwt_inited = 1;
}

static void delay_us(uint32_t us)
{
    uint32_t start = DWT->CYCCNT;
    uint32_t cycles = us * (SystemCoreClock / 1000000U);

    while ((DWT->CYCCNT - start) < cycles) {;}
}

static void set_polarity_rising(void)
{
    __HAL_TIM_SET_CAPTUREPOLARITY(s_htim, s_channel, TIM_INPUTCHANNELPOLARITY_RISING);
}

static void set_polarity_falling(void)
{
    __HAL_TIM_SET_CAPTUREPOLARITY(s_htim, s_channel, TIM_INPUTCHANNELPOLARITY_FALLING);
}

static void compute_pulse_us(void)
{
    uint32_t arr = __HAL_TIM_GET_AUTORELOAD(s_htim);

    if (s_t_fall >= s_t_rise) s_pulse_us = s_t_fall - s_t_rise;
    else s_pulse_us = (arr + 1U - s_t_rise) + s_t_fall;

    s_ready = 1;
}


void HCSR04_Init(TIM_HandleTypeDef *htim, uint32_t channel)
{
    dwt_init_once();

    s_htim = htim;
    s_channel = channel;

    s_t_rise = 0;
    s_t_fall = 0;
    s_pulse_us = 0;
    s_ready = 0;
    s_waiting_fall = 0;

    set_polarity_rising();
}

void HCSR04_Trigger(void)
{
    s_ready = 0;
    s_waiting_fall = 0;
    s_pulse_us = 0;
    s_timed_out = 0;

    set_polarity_rising();

    s_start_ms = HAL_GetTick();


    HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_RESET);
    delay_us(2);

    HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_SET);
    delay_us(10);

    HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_RESET);
}

uint8_t HCSR04_IsReady(void)
{
    return s_ready;
}

uint32_t HCSR04_GetPulseUs(void)
{
    return s_pulse_us;
}

float HCSR04_GetDistanceCm(void)
{
    return (s_pulse_us * 0.0343f) * 0.5f;
}

void HCSR04_OnCaptureIRQ(TIM_HandleTypeDef *htim)
{
    if (htim != s_htim) return;
    if (s_timed_out) return;

    if (!s_waiting_fall)
    {
        s_t_rise = HAL_TIM_ReadCapturedValue(htim, s_channel);
        set_polarity_falling();
        s_waiting_fall = 1;
    }
    else
    {
        s_t_fall = HAL_TIM_ReadCapturedValue(htim, s_channel);
        set_polarity_rising();
        s_waiting_fall = 0;

        compute_pulse_us();
    }
}

uint8_t HCSR04_HasTimedOut(uint32_t timeout_ms)
{
    if (s_ready) return 0;

    if (!s_timed_out && (HAL_GetTick() - s_start_ms) >= timeout_ms)
    {
        s_timed_out = 1;
        s_pulse_us = 0;
        s_waiting_fall = 0;
        set_polarity_rising();
    }

    return s_timed_out;
}
