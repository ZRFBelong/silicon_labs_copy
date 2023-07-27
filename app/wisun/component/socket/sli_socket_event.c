/***************************************************************************//**
 * @file
 * @brief
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "cmsis_os2.h"
#include "sl_cmsis_os2_common.h"
#include "sl_wisun_event_mgr.h"
#include "sli_socket_hnd.h"
#include "socket.h"
#include "sl_wisun_trace_util.h"

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

/* Socket data event handler */
void sl_wisun_socket_data_event_hnd(sl_wisun_evt_t *evt)
{
  sli_socket_hnd_t *hnd = NULL;
  uint32_t size = 0;
  int32_t r = 0;
  wisun_addr_t remote_addr = { 0 };

  hnd = sli_socket_hnd_get((int32_t) evt->evt.socket_data.socket_id); // get socket handler
  if (hnd == NULL) {
    return;
  }

  remote_addr.sin6_family = AF_WISUN;
  memcpy(&remote_addr.sin6_addr.s6_addr, &evt->evt.socket_data.remote_address, sizeof(in6_addr_t));
  remote_addr.sin6_port = evt->evt.socket_data.remote_port;

  // set remote address and remote port, gluing to the socket handler
  (void) sli_socket_hnd_write_remote_addr(hnd, &remote_addr, sizeof(wisun_addr_t), 0UL);
  size = evt->evt.socket_data.data_length;
  r = sli_socket_hnd_fifo_write(hnd, evt->evt.socket_data.data, &size);
  if (r == -1) {
    sli_socket_hnd_fifo_overflow_handler(hnd->socket_id,
                                         evt->evt.socket_data.data,
                                         evt->evt.socket_data.data_length,
                                         evt->evt.socket_data.data + size);
  }
  __CHECK_FOR_STATUS(evt->evt.error.status);
}

/* Socket data available event handler */
void sl_wisun_socket_data_available_event_hnd(sl_wisun_evt_t *evt)
{
  __CHECK_FOR_STATUS(evt->evt.error.status);
}

/* Socket connected event handler */
void sl_wisun_socket_connected_event_hnd(sl_wisun_evt_t *evt)
{
  __CHECK_FOR_STATUS(evt->evt.error.status);
}

/* Socket connection available event handler*/
void sl_wisun_socket_connection_available_event_hnd(sl_wisun_evt_t *evt)
{
  sli_socket_hnd_t *hnd = NULL;
  hnd = sli_socket_hnd_get((int32_t) evt->evt.socket_connection_available.socket_id);

  if (hnd == NULL) {
    return;
  }

  sli_socket_hnd_set_state(hnd, SOCKET_STATE_CONNECTION_AVAILABLE, true);
  __CHECK_FOR_STATUS(evt->evt.error.status);
}

/* Socket close event handler */
void sl_wisun_socket_closing_event_hnd(sl_wisun_evt_t *evt)
{
  sli_socket_hnd_remove(evt->evt.socket_closing.socket_id);
  __CHECK_FOR_STATUS(evt->evt.error.status);
}

/* Socket data sent event handler */
void sl_wisun_socket_data_sent_event_hnd(sl_wisun_evt_t *evt)
{
  __CHECK_FOR_STATUS(evt->evt.error.status);
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------
