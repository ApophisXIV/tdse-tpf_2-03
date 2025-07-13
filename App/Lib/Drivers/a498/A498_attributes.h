/**
 * @file A498_attributes.h
 *
 * @authors
 * Guido Rodriguez (guerodriguez@fi.uba.ar)
 *
 * @brief
 * @version 0.1
 * @date DD-MM-YYYY
 *
 * @copyright Copyright (c) 2025. All rights reserved.
 *
 * Licensed under the MIT License, see LICENSE for details.
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef A498_ATTRIBUTES_H
#define A498_ATTRIBUTES_H

/* -------------------------------- Includes -------------------------------- */
#include "main.h"
#include "utils.h"

/* -------------------------------- CPP Guard ------------------------------- */
#ifdef __cplusplus
extern "C" {
#endif    // __cplusplus

/* ------------------------------ Public macros ----------------------------- */

/* ---------------------------- ¨Public constants --------------------------- */

/* ------------------------------ Public enums ------------------------------ */
typedef enum {
    EV_A498_SLEEP,
    EV_A498_WAKE_UP,
    EV_A498_RESET,
    EV_A498_ENABLE,
    EV_A498_DISABLE,
    EV_A498_MAKE_CLOCKWISE_STEP,
    EV_A498_MAKE_COUNTERCLOCKWISE_STEP,
    EV_A498_MAKE_CLOCKWISE_TURN,
    EV_A498_MAKE_COUNTERCLOCKWISE_TURN,
    EV_A498_SET_STEP_MODE,
    EV_A498_SET_STEP_DELAY,
} A498_events_t;

typedef enum {
    ST_A498_IDLE,
    ST_A498_SLEEP,
    ST_A498_ENABLED,
    ST_A498_DISABLED,
    ST_A498_TURNING,
} A498_states_t;

typedef enum {
    A498_DIRECTION_CLOCKWISE,
    A498_DIRECTION_COUNTERCLOCKWISE
} A498_direction_t;

typedef enum {
    A498_STEP_MODE_FULL,
    A498_STEP_MODE_HALF,
    A498_STEP_MODE_QUARTER,
    A498_STEP_MODE_EIGHTH,
    A498_STEP_MODE_SIXTEENTH
} A498_step_mode_t;

/* ---------------------------- Public datatypes ---------------------------- */
typedef struct {
    // GPIO pins
    gpio_pin_t step_pin;
    gpio_pin_t direction_pin;
    gpio_pin_t enable_pin;
    gpio_pin_t reset_pin;
    gpio_pin_t sleep_pin;
    gpio_pin_t step_config_a_pin;
    gpio_pin_t step_config_b_pin;
    gpio_pin_t step_config_c_pin;

    // Configuration parameters
    A498_step_mode_t step_mode;
    uint16_t step_delay_us;
    uint16_t steps_per_revolution;
} A498_cfg_t;

typedef struct {
    uint32_t tick;
    A498_states_t state;
    A498_events_t event;
} A498_dta_t;

/* -------------------- External public data declarations ------------------- */

/* ----------------------- Public function prototypes ----------------------- */

/* ------------------- External public function prototypes ------------------ */

/* ------------------------------ CPP Guard end ----------------------------- */
#ifdef __cplusplus
}
#endif    // __cplusplus

#endif    // A498_ATTRIBUTES_H