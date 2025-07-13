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
 */

#ifndef A498_H
#define A498_H

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

/* -------------------- External public data declarations ------------------- */

/* ----------------------- Public function prototypes ----------------------- */
int A498_init(void);
void A498_set_direction(A498_direction_t direction);
/* ------------------- External public function prototypes ------------------ */

/* ------------------------------ CPP Guard end ----------------------------- */
#ifdef __cplusplus
}
#endif    // __cplusplus

#endif    // A498_H
