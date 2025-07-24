/**
 * @file fw_template.h
 *
 * @authors
 * Persona 1 (persona_1@example.com)
 * Persona 2 (persona_2@example.com)
 * Persona 3 (persona_3@example.com)
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

#ifndef FW_TEMPLATE_H
#define FW_TEMPLATE_H

/* -------------------------------- Includes -------------------------------- */

/* -------------------------------- CPP Guard ------------------------------- */
#ifdef __cplusplus
extern "C" {
#endif    // __cplusplus

/* ------------------------------ Public macros ----------------------------- */

/* ---------------------------- ¨Public constants --------------------------- */

/* ------------------------------ Public enums ------------------------------ */
typedef enum {
    EV_TEMPLATE_EVENT_1,
    EV_TEMPLATE_EVENT_2,
} template_events_t;

typedef enum {
    ST_TEMPLATE_STATE_1,
    ST_TEMPLATE_STATE_2,
} template_states_t;

/* ---------------------------- Public datatypes ---------------------------- */
typedef void (*template_event_t)(void);

typedef struct {
    template_states_t state;    // Current state of the FSM
    template_event_t event;     // Current event triggering the FSM transition
} template_fsm_node_t;

/* -------------------- External public data declarations ------------------- */

/* ----------------------- Public function prototypes ----------------------- */

/* ------------------- External public function prototypes ------------------ */

/* ------------------------------ CPP Guard end ----------------------------- */
#ifdef __cplusplus
}
#endif    // __cplusplus

#endif    // FW_TEMPLATE_H