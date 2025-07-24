/**
 * @file A498.h
 *
 * @authors
 * Guido Rodriguez (guerodriguez@fi.uba.ar)
 *
 * @brief A498 stepper motor driver header file
 * @version 0.1
 * @date 13-07-2025
 *
 * @copyright Copyright (c) 2025. All rights reserved.
 *
 * Licensed under the MIT License, see LICENSE for details.
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef A498_H
#define A498_H

/* -------------------------------- Includes -------------------------------- */
#include "A498_attributes.h"

/* -------------------------------- CPP Guard ------------------------------- */
#ifdef __cplusplus
extern "C" {
#endif    // __cplusplus

/* ------------------------------ Public macros ----------------------------- */

/* ---------------------------- ¨Public constants --------------------------- */

/* ------------------------------ Public enums ------------------------------ */

/* ---------------------------- Public datatypes ---------------------------- */
/**
 * @brief  A498 structure definition
 * @note   Opaque structure to hide implementation details
 * @retval None
 */
typedef struct A498 A498_t;

/* -------------------- External public data declarations ------------------- */

/* ----------------------- Public function prototypes ----------------------- */
/**
 * @brief  Register a new A498 instance
 * @pre    The id must be unique and not already registered
 * @post   The A498 instance is registered and initialized with the given configuration
 * @param  id: Unique identifier for the A498 instance
 * @param  cfg: Pointer to the configuration structure
 * @param  initial_state: Initial state of the A498
 * @retval Pointer to the registered A498 instance, or NULL on failure
 */
A498_t *A498_register(A498_id_t id, A498_cfg_t *cfg, A498_states_t initial_state);

/**
 * @brief  Unregister an A498 instance
 * @pre    The A498 instance must be registered
 * @post   The A498 instance is unregistered and its state is reset to stopped
 * @param  hA498: Pointer to the A498 instance to unregister
 * @retval true if unregistration was successful, false otherwise
 */
bool A498_unregister(A498_t *hA498);

/**
 * @brief  Update the internal A498 fsm instance
 * @pre    The A498 instance must be registered
 * @post   The tick count is incremented by one
 * @param  hA498: Pointer to the A498 instance to update
 * @retval true if the instance was updated successfully, false otherwise
 */
bool A498_update(A498_t *hA498);

/**
 * @brief  Get the current state of the A498 instance
 * @pre    The A498 instance must be registered
 * @post   None
 * @param  hA498: Pointer to the A498 instance
 * @retval Current state of the A498 instance
 */
A498_states_t A498_get_current_state(A498_t *hA498);

/**
 * @brief  Get the identifier of the A498 instance
 * @pre    The A498 instance must be registered
 * @post   None
 * @param  hA498: Pointer to the A498 instance
 * @retval Identifier of the A498 instance
 */
A498_id_t A498_get_id(A498_t *hA498);

/* ------------------------------- A498 Events ------------------------------- */
// bool A498_config(A498_t *hA498); //TODO: Revisar si permito configuracion on-the-fly
bool A498_sleep(A498_t *hA498);
bool A498_wake_up(A498_t *hA498);
bool A498_reset(A498_t *hA498);
bool A498_enable(A498_t *hA498);
bool A498_disable(A498_t *hA498);
bool A498_make_clockwise_step(A498_t *hA498);
bool A498_make_counterclockwise_step(A498_t *hA498);

/* ------------------- External public function prototypes ------------------ */

/* ------------------------------ CPP Guard end ----------------------------- */
#ifdef __cplusplus
}
#endif    // __cplusplus

#endif    // A498_H