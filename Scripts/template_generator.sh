#!/bin/bash

# ---------------------- Config ----------------------
AUTHOR="Tu Nombre (tu.email@example.com)"
LICENSE="MIT License"
VERSION="0.1"
DATE=$(date +%Y-%m-%d)
BASE_PATH="App/Lib"
# ----------------------------------------------------

# -------------------- Args check --------------------
if [ -z "$1" ] || [ -z "$2" ]; then
    echo "Uso: $0 <nombre_modulo> <--api | --driver>"
    exit 1
fi

MODULE_NAME=$(echo "$1" | tr '[:upper:]' '[:lower:]')
TYPE_FLAG="$2"

if [ "$TYPE_FLAG" == "--api" ]; then
    TARGET_DIR="${BASE_PATH}/APIs/${MODULE_NAME}"
elif [ "$TYPE_FLAG" == "--driver" ]; then
    TARGET_DIR="${BASE_PATH}/Drivers/${MODULE_NAME}"
else
    echo "Error: Segundo parámetro debe ser --api o --driver"
    exit 1
fi

mkdir -p "$TARGET_DIR"

HEADER_FILE="${MODULE_NAME}.h"
SOURCE_FILE="${MODULE_NAME}.c"
MACRO_GUARD=$(echo "${MODULE_NAME}_H" | tr '[:lower:]' '[:upper:]')

# -------------------- .h file --------------------
cat > "${TARGET_DIR}/${HEADER_FILE}" <<EOF
/**
 * @file ${HEADER_FILE}
 *
 * @authors
 * ${AUTHOR}
 *
 * @brief
 * @version ${VERSION}
 * @date ${DATE}
 *
 * @copyright Copyright (c) 2025. All rights reserved.
 *
 * Licensed under the ${LICENSE}, see LICENSE for details.
 * SPDX-License-Identifier: MIT
 */

#ifndef ${MACRO_GUARD}
#define ${MACRO_GUARD}

/* -------------------------------- Includes -------------------------------- */

/* -------------------------------- CPP Guard ------------------------------- */
#ifdef __cplusplus
extern "C" {
#endif    // __cplusplus

/* ------------------------------ Public macros ----------------------------- */

/* ---------------------------- Public constants ---------------------------- */

/* ---------------------------- Public datatypes ---------------------------- */

/* -------------------- External public data declarations ------------------- */

/* ----------------------- Public function prototypes ----------------------- */

/* ------------------- External public function prototypes ------------------ */

/* ------------------------------ CPP Guard end ----------------------------- */
#ifdef __cplusplus
}
#endif    // __cplusplus

#endif    // ${MACRO_GUARD}
EOF

# -------------------- .c file --------------------
cat > "${TARGET_DIR}/${SOURCE_FILE}" <<EOF
/**
 * @file ${SOURCE_FILE}
 *
 * @authors
 * ${AUTHOR}
 *
 * @brief
 * @version ${VERSION}
 * @date ${DATE}
 *
 * @copyright Copyright (c) 2025. All rights reserved.
 *
 * Licensed under the ${LICENSE}, see LICENSE for details.
 * SPDX-License-Identifier: MIT
 */

/* -------------------------------- Includes -------------------------------- */
#include "${HEADER_FILE}"

/* ----------------------------- Private macros ----------------------------- */

/* ---------------------------- Private constants --------------------------- */

/* ---------------------------- Private datatypes --------------------------- */

/* ------------------- Private static function prototypes ------------------- */

/* ------------------------ Private static variables ------------------------ */

/* ------------------------ Functions implementation ------------------------ */
EOF

# -------------------- Final message --------------------
echo "✅ Módulo creado en: ${TARGET_DIR}/"
