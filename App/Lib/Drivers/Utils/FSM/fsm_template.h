/**
 * @file fsm_template.h
 *
 * @authors
 * Guido Rodriguez (guerodriguez@fi.uba.ar)
 *
 * @brief FSM header file
 * @version 0.1
 * @date 13-07-2025
 *
 * @copyright Copyright (c) 2025. All rights reserved.
 *
 * Licensed under the MIT License, see LICENSE for details.
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef FSM_H
#define FSM_H

/* -------------------------------- Includes -------------------------------- */
#include "fsm_template_attributes.h"

/* -------------------------------- CPP Guard ------------------------------- */
#ifdef __cplusplus
extern "C" {
#endif    // __cplusplus

/* ------------------------------ Public macros ----------------------------- */

/* ---------------------------- ¨Public constants --------------------------- */

/* ------------------------------ Public enums ------------------------------ */

/* ---------------------------- Public datatypes ---------------------------- */
/**
 * @brief  FSM structure definition
 * @note   Opaque structure to hide implementation details
 * @retval None
 */
typedef struct fsm fsm_t;

/* -------------------- External public data declarations ------------------- */

/* ----------------------- Public function prototypes ----------------------- */
/**
 * @brief  Register a new FSM instance
 * @pre    The id must be unique and not already registered
 * @post   The FSM instance is registered and initialized with the given configuration
 * @param  id: Unique identifier for the FSM instance
 * @param  cfg: Pointer to the configuration structure
 * @param  initial_state: Initial state of the FSM
 * @retval Pointer to the registered FSM instance, or NULL on failure
 */
fsm_t *fsm_register(fsm_id_t id, fsm_cfg_t *cfg, fsm_states_t initial_state);

/**
 * @brief  Unregister an FSM instance
 * @pre    The FSM instance must be registered
 * @post   The FSM instance is unregistered and its state is reset to stopped
 * @param  hfsm: Pointer to the FSM instance to unregister
 * @retval true if unregistration was successful, false otherwise
 */
bool fsm_unregister(fsm_t *hfsm);

/**
 * @brief  Update the tick count of the FSM instance
 * @pre    The FSM instance must be registered
 * @post   The tick count is incremented by one
 * @param  hfsm: Pointer to the FSM instance to update
 * @retval true if the tick was updated successfully, false otherwise
 */
bool fsm_tick_update(fsm_t *hfsm);

/**
 * @brief  Get the current state of the FSM instance
 * @pre    The FSM instance must be registered
 * @post   None
 * @param  hfsm: Pointer to the FSM instance
 * @retval Current state of the FSM instance
 */
fsm_states_t fsm_get_current_state(fsm_t *hfsm);

/**
 * @brief  Get the identifier of the FSM instance
 * @pre    The FSM instance must be registered
 * @post   None
 * @param  hfsm: Pointer to the FSM instance
 * @retval Identifier of the FSM instance
 */
fsm_id_t fsm_get_id(fsm_t *hfsm);

/**
 * @brief  Get a variable from the FSM instance
 * @pre    The FSM instance must be registered
 * @post   None
 * @param  hfsm: Pointer to the FSM instance
 * @retval Value of var_1 from the FSM instance configuration
 */
uint16_t fsm_get_var_1(fsm_t *hfsm);


/* ------------------------------- FSM Events ------------------------------- */

/**
 * @brief  Trigger event A on the FSM instance
 * @pre    The FSM instance must be registered
 * @post   The FSM instance processes event A
 * @param  hfsm: Pointer to the FSM instance
 * @retval true if the event was processed successfully, false otherwise
 */
bool fsm_event_a(fsm_t *hfsm);

/**
 * @brief  Trigger event B on the FSM instance
 * @pre    The FSM instance must be registered
 * @post   The FSM instance processes event B
 * @param  hfsm: Pointer to the FSM instance
 * @retval true if the event was processed successfully, false otherwise
 */
bool fsm_event_b(fsm_t *hfsm);

/**
 * @brief  Trigger event C on the FSM instance
 * @pre    The FSM instance must be registered
 * @post   The FSM instance processes event C
 * @param  hfsm: Pointer to the FSM instance
 * @retval true if the event was processed successfully, false otherwise
 */
bool fsm_event_c(fsm_t *hfsm);

/* ------------------- External public function prototypes ------------------ */

/* ------------------------------ CPP Guard end ----------------------------- */
#ifdef __cplusplus
}
#endif    // __cplusplus

#endif    // FSM_H