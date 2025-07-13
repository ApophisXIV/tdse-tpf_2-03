/**
 * @file utils.h
 *
 * @authors
 * Guido Rodriguez (guerodriguez@fi.uba.ar)
 *
 * @brief Header file for utils functions and definitions
 * @version 0.1
 * @date 13-07-2025
 *
 * @copyright Copyright (c) 2025. All rights reserved.
 *
 * Licensed under the MIT License, see LICENSE for details.
 * SPDX-License-Identifier: MIT
 */

#ifndef UTILS_H
#define UTILS_H

/* -------------------------------- Includes -------------------------------- */
#include "main.h"

/* -------------------------------- CPP Guard ------------------------------- */
#ifdef __cplusplus
extern "C" {
#endif    // __cplusplus

/* ------------------------------ Public macros ----------------------------- */

/* ---------------------------- Public constants ---------------------------- */

/* ------------------------------- Pulic enums ------------------------------ */

/* ---------------------------- Public datatypes ---------------------------- */
/**
 * @brief  Auxiliary structure to represent a GPIO pin
 */
typedef struct {
    GPIO_TypeDef *port;
    uint16_t pin;
} gpio_pin_t;

/* -------------------- External public data declarations ------------------- */

/* ----------------------- Public function prototypes ----------------------- */

/* ------------------- External public function prototypes ------------------ */

/* ------------------------------ CPP Guard end ----------------------------- */
#ifdef __cplusplus
}
#endif    // __cplusplus

#endif    // UTILS_H
