/**
 * @file fsm_template.c
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

/* -------------------------------- Includes -------------------------------- */
#include "fsm_template.h"

/* ----------------------------- Private macros ----------------------------- */

/* ---------------------------- Private constants --------------------------- */

/* ---------------------------- Private datatypes --------------------------- */

/* ------------------- Private static function prototypes ------------------- */
static void fsm_template_event_1(void);
static void fsm_template_event_2(void);

/* ------------------------ Private static variables ------------------------ */

// Transition table for the FSM
static const template_fsm_node_t fsm_transition_table[] = {
    [ST_TEMPLATE_STATE_1] = {EV_TEMPLATE_EVENT_1, fsm_template_event_1},
    [ST_TEMPLATE_STATE_2] = {EV_TEMPLATE_EVENT_2, fsm_template_event_2},
};

/* ------------------------ Functions implementation ------------------------ */

void fsm_template_init(template_fsm_t *fsm) {
    fsm->state = ST_TEMPLATE_STATE_1;    // Initial state
    fsm->event = EV_TEMPLATE_EVENT_1;    // Initial event
    fsm->flag  = false;                  // No pending event
}

void fsm_template_update(template_fsm_t *fsm) {
    // Check if there is a pending event
    if (fsm->flag) {
        // Execute the action associated with the current event
        fsm_transition_table[fsm->state].event();

        // Reset the flag after processing the event
        fsm->flag = false;
    }
}
void fsm_template_event_1(void) {
    // Action for event 1
    // Transition to the next state
    fsm->state = ST_TEMPLATE_STATE_2;
}
void fsm_template_event_2(void) {
    // Action for event 2
    // Transition to the next state
    fsm->state = ST_TEMPLATE_STATE_1;
}
