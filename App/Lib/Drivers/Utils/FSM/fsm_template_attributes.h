/**
 * @file fsm_template_attributes.h
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

#ifndef FSM_ATTRIBUTES_H
#define FSM_ATTRIBUTES_H

/* -------------------------------- Includes -------------------------------- */
#include "main.h"
#include "utils.h"

#include <stdbool.h>
#include <stdint.h>

/* -------------------------------- CPP Guard ------------------------------- */
#ifdef __cplusplus
extern "C" {
#endif    // __cplusplus

/* ------------------------------ Public macros ----------------------------- */

/* ---------------------------- ¨Public constants --------------------------- */
#define FSM_MAX_INSTANCES 4

/* ------------------------------ Public enums ------------------------------ */
typedef enum {
    ST_STOPED,
    ST_ERROR,
    ST_A,
    ST_B,
    ST_C,
} fsm_states_t;

typedef enum {
    EV_1,
    EV_2,
    EV_3,
} fsm_event_id_t;

/* ---------------------------- Public datatypes ---------------------------- */
typedef struct {
    uint8_t var_1;
    bool flag;
} fsm_cfg_t;

typedef uint8_t fsm_id_t;
/* -------------------- External public data declarations ------------------- */

/* ----------------------- Public function prototypes ----------------------- */

/* ------------------- External public function prototypes ------------------ */

/* ------------------------------ CPP Guard end ----------------------------- */
#ifdef __cplusplus
}
#endif    // __cplusplus

#endif    // FSM_ATTRIBUTES_H