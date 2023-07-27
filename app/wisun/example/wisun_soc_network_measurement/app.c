/***************************************************************************//**
 * @file
 * @brief Application code
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/
// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------
#include <stdio.h>
#include <assert.h>
#include "sl_component_catalog.h"
#include "app.h"
#include "sl_wisun_network_measurement.h"
#include "sl_iperf.h"
#include "sl_iperf_util.h"
#include "sl_wisun_coap_rhnd.h"

#if defined(SL_CATALOG_GUI_PRESENT)
#include "sl_wisun_network_measurement_gui.h"
#include "sl_display.h"
#include "sl_gui.h"
#endif
// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------
/*App task function*/
void app_task(void *args)
{
  (void) args;

  // connect to the wisun network
  app_wisun_connect_and_wait();

#if defined(SL_CATALOG_GUI_PRESENT)
  sl_display_renderer(sl_wisun_nwm_main_form, NULL, 0);
#endif

  while (1) {
    // User code here
    msleep(1);
  }
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------
