/**
 * @file fsm_template.c
 *
 * @authors
 * Guido Rodriguez (guerodriguez@fi.uba.ar)
 *
 * @brief Finite State Machine (FSM) implementation
 * @version 0.1
 * @date 13-07-2025
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
struct fsm {
    // Instance management
    fsm_id_t id;
    bool is_registered;
    // Configuration
    fsm_cfg_t config;
    // State machine variables
    fsm_states_t actual_state;
    uint32_t tick;
};

typedef void (*fsm_event_handler_t)(fsm_t *, fsm_event_id_t event);

/* ------------------- Private static function prototypes ------------------- */
/**
 * @brief Dispatch an event to the FSM instance
 * @pre    The FSM instance must be registered
 * @post   The FSM instance processes the event
 * @param  hfsm: Pointer to the FSM instance
 * @param  event: Event to dispatch
 * @retval true if the event was processed successfully, false otherwise
 */
static bool fsm_dispatch_event(fsm_t *hfsm, fsm_event_id_t event);
static fsm_t *fsm_get_instance(void);

// FSM API Prototypes
static void fsm_action_state_stoped(fsm_t *hfsm, fsm_event_id_t event);
static void fsm_action_state_error(fsm_t *hfsm, fsm_event_id_t event);
static void fsm_action_state_a(fsm_t *hfsm, fsm_event_id_t event);
static void fsm_action_state_b(fsm_t *hfsm, fsm_event_id_t event);
static void fsm_action_state_c(fsm_t *hfsm, fsm_event_id_t event);

/* ------------------------ Private static variables ------------------------ */
static const fsm_event_handler_t states_behavior[] = {
    [ST_STOPED] = fsm_action_state_stoped,
    [ST_ERROR]  = fsm_action_state_error,
    [ST_A]      = fsm_action_state_a,
    [ST_B]      = fsm_action_state_b,
    [ST_C]      = fsm_action_state_c,
};

// FSM Instances
static fsm_t fsm_instances[FSM_MAX_INSTANCES] = {0};

/* ------------------------ Functions implementation ------------------------ */
static fsm_t *fsm_get_instance(void) {
    for (uint8_t i = 0; i < FSM_MAX_INSTANCES; i++) {
        if (fsm_instances[i].is_registered == false) {
            fsm_instances[i].is_registered = true;
            return &fsm_instances[i];
        }
    }
    return 0;
}

fsm_t *fsm_register(fsm_id_t id, fsm_cfg_t *cfg, fsm_states_t initial_state) {
    if (!cfg) return 0;

    fsm_t *hfsm = fsm_get_instance();
    if (!hfsm) return 0;

    hfsm->id           = id;
    hfsm->actual_state = initial_state;
    hfsm->config       = *cfg;
    hfsm->tick         = 0;
    return hfsm;
}

bool fsm_unregister(fsm_t *hfsm) {
    if (!hfsm) return false;
    hfsm->is_registered = false;
    hfsm->actual_state  = ST_STOPED;
    return true;
}

bool fsm_tick_update(fsm_t *hfsm) {
    if (!hfsm) return false;
    hfsm->tick++;
    return true;
}

fsm_states_t fsm_get_current_state(fsm_t *hfsm) {
    if (!hfsm) return ST_ERROR;
    return hfsm->actual_state;
}

uint16_t fsm_get_var_1(fsm_t *hfsm) {
    if (!hfsm) return 0;
    return hfsm->config.var_1;
}

fsm_id_t fsm_get_id(fsm_t *hfsm) {
    if (!hfsm) return 0;
    return hfsm->id;
}

static bool fsm_dispatch_event(fsm_t *hfsm, fsm_event_id_t event) {
    if (!hfsm || event < EV_1 || event > EV_3) return false;

    if (states_behavior[hfsm->actual_state]) {
        states_behavior[hfsm->actual_state](hfsm, event);
        return true;
    }
    return false;
}

/* --------------------------------- FSM API -------------------------------- */
static void fsm_action_state_stoped(fsm_t *hfsm, fsm_event_id_t event) {
    // NOTE  La idea de este estado es llevar la FSM a un punto seguro
    //       (podria usarse el mismo que state_error si corresponde)
}

static void fsm_action_state_error(fsm_t *hfsm, fsm_event_id_t event) {
    // NOTE La idea de este estado es llevar la FSM a un punto seguro
}

bool fsm_event_a(fsm_t *hfsm) {
    return fsm_dispatch_event(hfsm, EV_1);
}
static void fsm_action_state_a(fsm_t *hfsm, fsm_event_id_t event) {
    if (event == EV_1) {
        hfsm->actual_state = ST_B;
    }
}

bool fsm_event_b(fsm_t *hfsm) {
    return fsm_dispatch_event(hfsm, EV_2);
}
static void fsm_action_state_b(fsm_t *hfsm, fsm_event_id_t event) {
    if (event == EV_2) {
        hfsm->actual_state = ST_C;
    } else if (event == EV_3) {
        hfsm->actual_state = ST_A;
    }
}

bool fsm_event_c(fsm_t *hfsm) {
    return fsm_dispatch_event(hfsm, EV_3);
}
static void fsm_action_state_c(fsm_t *hfsm, fsm_event_id_t event) {
    if (event == EV_3) {
        hfsm->actual_state = ST_A;
    }
}