/**
 * @file A498.c
 *
 * @authors
 * Guido Rodriguez (guerodriguez@fi.uba.ar)
 *
 * @brief  A498 stepper motor driver implementation
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
#include "A498.h"

/* ----------------------------- Private macros ----------------------------- */
#define CONSUME_EVENT(HANDLE_PTR, EXPECTED_EVENT)                                                               \
    for (bool avaliable_to_run = ((HANDLE_PTR)->is_event_pending && ((HANDLE_PTR)->event == (EXPECTED_EVENT))); \
         avaliable_to_run;                                                                                      \
         avaliable_to_run = false)                                                                              \
        if (((HANDLE_PTR)->is_event_pending = false), true)

/* ---------------------------- Private constants --------------------------- */
#define A498_RESET_DELAY_MS         10
#define A498_TIMEOUT_NO_ACTIVITY_MS 5000

/* ---------------------------- Private datatypes --------------------------- */
struct A498 {
    // Instance management
    A498_id_t id;
    bool is_registered;
    // Configuration
    A498_cfg_t config;
    // State machine variables
    A498_states_t actual_state;
    A498_event_id_t event;
    bool is_event_pending;
    // State machine timing
    uint32_t tick;
    uint32_t last_tick;
};

typedef void (*A498_event_handler_t)(A498_t *);

/* ------------------- Private static function prototypes ------------------- */
/**
 * @brief  Dispatch an event to the A498 instance
 * @pre    The A498 instance must be registered
 * @pre    The state handlers must consume the event setting the event flag acordingly
 * @post   The event is dispatched and the state machine is updated
 * @param  *hA498: Pointer to the A498 instance
 * @param  event: Event to dispatch
 * @retval true if the event was dispatched successfully, false otherwise
 */
static bool A498_dispatch_event(A498_t *hA498, A498_event_id_t event);
static A498_t *A498_get_instance(void);

// A498 API Prototypes
static void A498_action_state_error(A498_t *hA498);
static void A498_action_state_idle(A498_t *hA498);
static void A498_action_state_reset(A498_t *hA498);
static void A498_action_state_sleep(A498_t *hA498);
static void A498_action_state_enabled(A498_t *hA498);
static void A498_action_state_disabled(A498_t *hA498);
static void A498_action_state_stepping_clockwise(A498_t *hA498);
static void A498_action_state_stepping_counterclockwise(A498_t *hA498);

/* ------------------------ Private static variables ------------------------ */
static const A498_event_handler_t states_behavior[] = {
    [ST_STOPED]                         = A498_action_state_error,
    [ST_ERROR]                          = A498_action_state_error,
    [ST_A498_IDLE]                      = A498_action_state_idle,
    [ST_A498_RESET]                     = A498_action_state_reset,
    [ST_A498_SLEEP]                     = A498_action_state_sleep,
    [ST_A498_ENABLED]                   = A498_action_state_enabled,
    [ST_A498_DISABLED]                  = A498_action_state_disabled,
    [ST_A498_STEPPING_CLOCKWISE]        = A498_action_state_stepping_clockwise,
    [ST_A498_STEPPING_COUNTERCLOCKWISE] = A498_action_state_stepping_counterclockwise,
};

// A498 Instances
static A498_t A498_instances[A498_MAX_INSTANCES] = {0};

/* ------------------------ Functions implementation ------------------------ */
static A498_t *A498_get_instance(void) {
    for (uint8_t i = 0; i < A498_MAX_INSTANCES; i++) {
        if (A498_instances[i].is_registered == false) {
            A498_instances[i].is_registered = true;
            return &A498_instances[i];
        }
    }
    return 0;
}

A498_t *A498_register(A498_id_t id, A498_cfg_t *cfg, A498_states_t initial_state) {
    if (!cfg) return 0;

    A498_t *hA498 = A498_get_instance();
    if (!hA498) return 0;

    hA498->id               = id;
    hA498->actual_state     = initial_state;
    hA498->config           = *cfg;
    hA498->tick             = 0;
    hA498->last_tick        = 0;
    hA498->is_event_pending = false;
    return hA498;
}

bool A498_unregister(A498_t *hA498) {
    if (!hA498) return false;
    hA498->is_registered = false;
    hA498->actual_state  = ST_STOPED;
    return true;
}

bool A498_update(A498_t *hA498) {
    if (!hA498) return false;
    hA498->tick++;
    states_behavior[hA498->actual_state](hA498);
    return true;
}

A498_states_t A498_get_current_state(A498_t *hA498) {
    if (!hA498) return ST_ERROR;
    return hA498->actual_state;
}

A498_id_t A498_get_id(A498_t *hA498) {
    if (!hA498) return 0;
    return hA498->id;
}

static bool A498_dispatch_event(A498_t *hA498, A498_event_id_t event) {
    if (!hA498 || event < EV_A498_SLEEP || event > EV_A498_MAKE_COUNTERCLOCKWISE_STEP) return false;

    hA498->event = event;

    if (states_behavior[hA498->actual_state]) {
        hA498->is_event_pending = true;
        states_behavior[hA498->actual_state](hA498);    // NOTE: The state will be the responsible to consume the event
        return true;
    }
    return false;
}

/* --------------------------------- A498 API -------------------------------- */
static void A498_action_state_error(A498_t *hA498) {
}

bool A498_wake_up(A498_t *hA498) {
    return A498_dispatch_event(hA498, EV_A498_WAKE_UP);
}
static void A498_action_state_idle(A498_t *hA498) {
    CONSUME_EVENT(hA498, EV_A498_RESET) {
        hA498->actual_state = ST_A498_ENABLED;
    }
    CONSUME_EVENT(hA498, EV_A498_SLEEP) {
        hA498->actual_state = ST_A498_SLEEP;
    }
    CONSUME_EVENT(hA498, EV_A498_ENABLE) {
        hA498->actual_state = ST_A498_ENABLED;
        HAL_GPIO_WritePin(hA498->config.enable_gpio.port, hA498->config.enable_gpio.pin, HIGH);
    }
    CONSUME_EVENT(hA498, EV_A498_DISABLE) {
        hA498->actual_state = ST_A498_DISABLED;
        HAL_GPIO_WritePin(hA498->config.enable_gpio.port, hA498->config.enable_gpio.pin, LOW);
    }
    CONSUME_EVENT(hA498, EV_A498_MAKE_CLOCKWISE_STEP) {
        hA498->actual_state = ST_A498_STEPPING_CLOCKWISE;
        HAL_GPIO_WritePin(hA498->config.direction_gpio.port, hA498->config.direction_gpio.pin, HIGH);
    }
    CONSUME_EVENT(hA498, EV_A498_MAKE_COUNTERCLOCKWISE_STEP) {
        hA498->actual_state = ST_A498_STEPPING_COUNTERCLOCKWISE;
        HAL_GPIO_WritePin(hA498->config.direction_gpio.port, hA498->config.direction_gpio.pin, LOW);
    }
    if (hA498->tick - hA498->last_tick > A498_TIMEOUT_NO_ACTIVITY_MS) {
        hA498->actual_state = ST_A498_SLEEP;
        HAL_GPIO_WritePin(hA498->config.sleep_gpio.port, hA498->config.sleep_gpio.pin, LOW);
    }
}

bool A498_reset(A498_t *hA498) {
    return A498_dispatch_event(hA498, EV_A498_RESET);
}
static void A498_action_state_reset(A498_t *hA498) {

    


    if (hA498->tick - hA498->last_tick < A498_RESET_DELAY_MS) return;
    hA498->actual_state = ST_A498_IDLE;
}

bool A498_sleep(A498_t *hA498) {
    return A498_dispatch_event(hA498, EV_A498_SLEEP);
}
static void A498_action_state_sleep(A498_t *hA498) {
    if (IS_EVENT_PENDING(hA498, EV_A498_MAKE_CLOCKWISE_STEP)) {
        hA498->actual_state = ST_A498_STEPPING_CLOCKWISE;
    } else if (IS_EVENT_PENDING(hA498, EV_A498_MAKE_COUNTERCLOCKWISE_STEP)) {
        hA498->actual_state = ST_A498_STEPPING_COUNTERCLOCKWISE;
    } else if (!hA498->is_event_pending) {
        HAL_GPIO_WritePin(hA498->config.sleep_gpio.port, hA498->config.sleep_gpio.pin, LOW);
    }
}

bool A498_enable(A498_t *hA498) {
    return A498_dispatch_event(hA498, EV_A498_ENABLE);
}
static void A498_action_state_enabled(A498_t *hA498) {
}

bool A498_disable(A498_t *hA498) {
    return A498_dispatch_event(hA498, EV_A498_DISABLE);
}
static void A498_action_state_disabled(A498_t *hA498) {
}

bool A498_make_clockwise_step(A498_t *hA498) {
    return A498_dispatch_event(hA498, EV_A498_MAKE_CLOCKWISE_STEP);
}
static void A498_action_state_stepping_clockwise(A498_t *hA498) {
    HAL_GPIO_WritePin(hA498->config.direction_gpio.port, hA498->config.direction_gpio.pin, HIGH);
}

bool A498_make_counterclockwise_step(A498_t *hA498) {
    return A498_dispatch_event(hA498, EV_A498_MAKE_COUNTERCLOCKWISE_STEP);
}
static void A498_action_state_stepping_counterclockwise(A498_t *hA498) {
}
