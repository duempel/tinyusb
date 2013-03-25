/*
 * hid_host.c
 *
 *  Created on: Dec 20, 2012
 *      Author: hathach
 */

/*
 * Software License Agreement (BSD License)
 * Copyright (c) 2013, hathach (tinyusb.org)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the tiny usb stack.
 */

#include "tusb_option.h"

#if (MODE_HOST_SUPPORTED && defined HOST_CLASS_HID)

#define _TINY_USB_SOURCE_FILE_

//--------------------------------------------------------------------+
// INCLUDE
//--------------------------------------------------------------------+
#include "common/common.h"
#include "hid_host.h"

//--------------------------------------------------------------------+
// MACRO CONSTANT TYPEDEF
//--------------------------------------------------------------------+

//--------------------------------------------------------------------+
// INTERNAL OBJECT & FUNCTION DECLARATION
//--------------------------------------------------------------------+

//--------------------------------------------------------------------+
// CLASS-USBD API (don't require to verify parameters)
//--------------------------------------------------------------------+
void hidh_init(void)
{
#if TUSB_CFG_HOST_HID_KEYBOARD
  hidh_keyboard_init();
#endif

#if TUSB_CFG_HOST_HID_MOUSE
  hidh_mouse_init();
#endif

#if TUSB_CFG_HOST_HID_GENERIC
  hidh_generic_init();
#endif
}

tusb_error_t hidh_open_subtask(uint8_t dev_addr, uint8_t const *descriptor, uint16_t *p_length)
{
  tusb_descriptor_interface_t* p_interface = (tusb_descriptor_interface_t*) descriptor;
  if (p_interface->bInterfaceSubClass == HID_SUBCLASS_BOOT)
  {
    switch(p_interface->bInterfaceProtocol)
    {
      #if TUSB_CFG_HOST_HID_KEYBOARD
      case HID_PROTOCOL_KEYBOARD:
        return hidh_keyboard_open_subtask(dev_addr, descriptor, p_length);
      break;
      #endif

      #if TUSB_CFG_HOST_HID_MOUSE
      case HID_PROTOCOL_MOUSE:
        return hidh_keyboard_open_subtask(dev_addr, descriptor, p_length);
      break;
      #endif

      default: // unknown protocol --> skip this interface
        *p_length = p_interface->bLength;
        return TUSB_ERROR_NONE;
    }
  }else
  {
    // open generic
    *p_length = p_interface->bLength;
    return TUSB_ERROR_NONE;
  }
}

void hidh_isr(pipe_handle_t pipe_hdl, tusb_bus_event_t event)
{

}

void hidh_close(uint8_t dev_addr)
{

}

#endif
