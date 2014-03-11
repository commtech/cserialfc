/*
    Copyright (C) 2013 Commtech, Inc.

    This file is part of cserialfc.

    cserialfc is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    cserialfc is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with cserialfc.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <stdio.h>
#include <fcntl.h> /* open, O_RDWR */

#ifndef _WIN32
#include <unistd.h> /* write, close */
#include <poll.h>
#endif

#include "serialfc.h"
#include "errno.h"

#define UNUSED(x) (void)(x)

#define MAX_NAME_LENGTH 25

int translate_error(int e)
{
#ifdef _WIN32
    switch (e) {
        case ERROR_NOT_SUPPORTED:
            return SERIALFC_NOT_SUPPORTED;
        case ERROR_INVALID_PARAMETER:
            return SERIALFC_INVALID_PARAMETER;
    default:
        return e;
    }
#else
    switch (e) {
        case EPROTONOSUPPORT:
            return SERIALFC_NOT_SUPPORTED;
        case EINVAL:
            return SERIALFC_INVALID_PARAMETER;
    default:
        return e;
    }
#endif
}

int ioctl_action(serialfc_handle h, int ioctl_name)
{
    int result;

#ifdef _WIN32
    DWORD temp;

    result = DeviceIoControl(h, (DWORD)ioctl_name,
                             NULL, 0,
                             NULL, 0,
                             &temp, (LPOVERLAPPED)NULL);

    return (result == TRUE) ? 0 : translate_error(GetLastError());
#else
    result = ioctl(h, ioctl_name);

    return (result != -1) ? 0 : translate_error(errno);
#endif
}

int ioctl_get_boolean(serialfc_handle h, int ioctl_name, unsigned *status)
{
    int result;

#ifdef _WIN32
    DWORD temp;

    result = DeviceIoControl(h, (DWORD)ioctl_name,
                             NULL, 0,
                             status, sizeof(*status),
                             &temp, (LPOVERLAPPED)NULL);

    return (result == TRUE) ? 0 : translate_error(GetLastError());
#else
    result = ioctl(h, ioctl_name, status);

    return (result != -1) ? 0 : translate_error(errno);
#endif
}

int ioctl_set_integer(serialfc_handle h, int ioctl_name, int value)
{
    int result;

#ifdef _WIN32
    DWORD temp;

    result = DeviceIoControl(h, (DWORD)ioctl_name,
                             &value, sizeof(value),
                             NULL, 0,
                             &temp, (LPOVERLAPPED)NULL);

    return (result == TRUE) ? 0 : translate_error(GetLastError());
#else
    result = ioctl(h, ioctl_name, value);

    return (result != -1) ? 0 : translate_error(errno);
#endif
}

int ioctl_get_integer(serialfc_handle h, int ioctl_name, int *value)
{
    int result;

#ifdef _WIN32
    DWORD temp;

    result = DeviceIoControl(h, (DWORD)ioctl_name,
                             NULL, 0,
                             value, sizeof(*value),
                             &temp, (LPOVERLAPPED)NULL);

    return (result == TRUE) ? 0 : translate_error(GetLastError());
#else
    result = ioctl(h, ioctl_name, value);

    return (result != -1) ? 0 : translate_error(errno);
#endif
}

int ioctl_set_pointer(serialfc_handle h, int ioctl_name, const void *value,
                      int size)
{
    int result;

    #ifdef _WIN32
        DWORD temp;

        result = DeviceIoControl(h, (DWORD)ioctl_name,
                                 (void *)value, size,
                                 NULL, 0,
                                 &temp, (LPOVERLAPPED)NULL);

        return (result == TRUE) ? 0 : translate_error(GetLastError());
    #else
        UNUSED(size);

        result = ioctl(h, ioctl_name, value);

        return (result != -1) ? 0 : translate_error(errno);
    #endif
}

int ioctl_get_pointer(serialfc_handle h, int ioctl_name, void *value,
                      int size)
{
    int result;

#ifdef _WIN32
    DWORD temp;

    result = DeviceIoControl(h, (DWORD)ioctl_name,
                             NULL, 0,
                             value, size,
                             &temp, (LPOVERLAPPED)NULL);

    return (result == TRUE) ? 0 : translate_error(GetLastError());
#else
    UNUSED(size);

    result = ioctl(h, ioctl_name, value);

    return (result != -1) ? 0 : translate_error(errno);
#endif
}

int ioctl_getset_pointer(serialfc_handle h, int ioctl_name, void *value,
                         int size)
{
    int result;

#ifdef _WIN32
    DWORD temp;

    result = DeviceIoControl(h, (DWORD)ioctl_name,
                             value, size,
                             value, size,
                             &temp, (LPOVERLAPPED)NULL);

    return (result == TRUE) ? 0 : translate_error(GetLastError());
#else
    UNUSED(size);

    result = ioctl(h, ioctl_name, value);

    return (result != -1) ? 0 : translate_error(errno);
#endif
}

int serialfc_connect(unsigned port_num, serialfc_handle *h)
{
    char name[MAX_NAME_LENGTH];

#ifdef _WIN32
    sprintf_s(name, MAX_NAME_LENGTH, "\\\\.\\COM%u", port_num);

    *h = CreateFile(name,
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
            NULL
    );

    return (*h != INVALID_HANDLE_VALUE) ? 0 : translate_error(GetLastError());
#else
    sprintf(name, "/dev/serialfc%u", port_num);

    *h = open(name, O_RDWR);

    return (*h != -1) ? 0 : translate_error(errno);
#endif
}

int serialfc_enable_rs485(serialfc_handle h)
{
    return ioctl_action(h, IOCTL_FASTCOM_ENABLE_RS485);
}

int serialfc_disable_rs485(serialfc_handle h)
{
    return ioctl_action(h, IOCTL_FASTCOM_DISABLE_RS485);
}

int serialfc_get_rs485(serialfc_handle h, unsigned *status)
{
    return ioctl_get_boolean(h, IOCTL_FASTCOM_GET_RS485, status);
}

int serialfc_enable_echo_cancel(serialfc_handle h)
{
    return ioctl_action(h, IOCTL_FASTCOM_ENABLE_ECHO_CANCEL);
}

int serialfc_disable_echo_cancel(serialfc_handle h)
{
    return ioctl_action(h, IOCTL_FASTCOM_DISABLE_ECHO_CANCEL);
}

int serialfc_get_echo_cancel(serialfc_handle h, unsigned *status)
{
    return ioctl_get_boolean(h, IOCTL_FASTCOM_GET_ECHO_CANCEL, status);
}

int serialfc_enable_termination(serialfc_handle h)
{
    return ioctl_action(h, IOCTL_FASTCOM_ENABLE_TERMINATION);
}

int serialfc_disable_termination(serialfc_handle h)
{
    return ioctl_action(h, IOCTL_FASTCOM_DISABLE_TERMINATION);
}

int serialfc_get_termination(serialfc_handle h, unsigned *status)
{
    return ioctl_get_boolean(h, IOCTL_FASTCOM_GET_TERMINATION, status);
}

/******************************************************************************/
/*!
	
    - FSCC Family (16c950): 4 - 16
    - Async-335 Family (17D15X): 8, 16
    - Async-PCIe Family (17V35X): 4, 8, 16

*/
/******************************************************************************/
int serialfc_set_sample_rate(serialfc_handle h, unsigned rate)
{
    return ioctl_set_integer(h, IOCTL_FASTCOM_SET_SAMPLE_RATE, rate);
}

int serialfc_get_sample_rate(serialfc_handle h, unsigned *rate)
{
    return ioctl_get_integer(h, IOCTL_FASTCOM_GET_SAMPLE_RATE, (int *)rate);
}

/******************************************************************************/
/*!
	
    - FSCC Family: 0 - 127
    - Async-335 Family (17D15X): 0 - 64
    - Async-PCIe Family (17V35X): 0 - 255

*/
/******************************************************************************/
int serialfc_set_tx_trigger(serialfc_handle h, unsigned level)
{
    return ioctl_set_integer(h, IOCTL_FASTCOM_SET_TX_TRIGGER, level);
}

int serialfc_get_tx_trigger(serialfc_handle h, unsigned *level)
{
    return ioctl_get_integer(h, IOCTL_FASTCOM_GET_TX_TRIGGER, (int *)level);
}

/******************************************************************************/
/*!
	
    - FSCC Family (16c950): 0 - 127
    - Async-335 Family (17D15X): 0 - 64
    - Async-PCIe Family (17V35X): 0 - 255

*/
/******************************************************************************/
int serialfc_set_rx_trigger(serialfc_handle h, unsigned level)
{
    return ioctl_set_integer(h, IOCTL_FASTCOM_SET_RX_TRIGGER, level);
}

/******************************************************************************/
/*!


  \todo
    This is only supported in the FSCC cards but isn't currently implemented.

*/
/******************************************************************************/
int serialfc_get_rx_trigger(serialfc_handle h, unsigned *level)
{
    return ioctl_get_integer(h, IOCTL_FASTCOM_GET_RX_TRIGGER, (int *)level);
}

/******************************************************************************/
/*!
	
  \note
    This is only supported on the Async-335 and FSCC cards. Each also has it's 
	own supported range.
	
    - FSCC Family (16c950): 200 Hz - 270 MHz
    - Async-335 Family (17D15X): 6 MHz - 180 MHz
	
	The Async-PCIe family doesn't use a variable clock generator to achieve
	baud rates so this is not required.

*/
/******************************************************************************/
int serialfc_set_clock_rate(serialfc_handle h, unsigned rate)
{
    //TODO: This needs something different for linux
    return ioctl_set_integer(h, IOCTL_FASTCOM_SET_CLOCK_RATE, rate);
}

/******************************************************************************/
/*!
	
  \note
    This is only supported on the FSCC cards.

  \note
    If you apply an external clock to the card before turning on isochronous
    mode your system will freeze due to too many serial interrupts. Make sure 
    and apply the clock after you are the isochronous mode (so the interrupts 
    are disabled).
	
  \note
	There are 8 different isochronous combinations you can use.
	
	0: Transmit using external RI#
	1: Transmit using internal BRG
	2: Receive using external DSR#
	3: Transmit using external RI#, receive using external DSR#
	4: Transmit using internal BRG, receive using external DSR#
	5: Receive using internal BRG
	6: Transmit using external RI#, receive using internal BRG
	7: Transmit using internal BRG, receive using internal BRG
	8: Transmit and receive using external RI#
	9: Transmit clock is output on DTR#
   10: Transmit clock is output on DTR#, receive using external DSR#

*/
/******************************************************************************/
int serialfc_enable_isochronous(serialfc_handle h, unsigned mode)
{
    return ioctl_set_integer(h, IOCTL_FASTCOM_ENABLE_ISOCHRONOUS, mode);
}

/******************************************************************************/
/*!
	
  \note
    This is only supported on the FSCC cards.

  \note
    If you have an external clock applied to the card while turning off 
    isochronous mode your system will freeze due to too many serial interrupts. 
    Make sure and remove the clock before you disable isochronous mode (while 
    the interrupts are disabled).

*/
/******************************************************************************/
int serialfc_disable_isochronous(serialfc_handle h)
{
    return ioctl_action(h, IOCTL_FASTCOM_DISABLE_ISOCHRONOUS);
}

/******************************************************************************/
/*!
	
  \note
    This is only supported on the FSCC cards.

*/
/******************************************************************************/
int serialfc_get_isochronous(serialfc_handle h, int *mode)
{
    return ioctl_get_integer(h, IOCTL_FASTCOM_GET_ISOCHRONOUS, mode);
}

/******************************************************************************/
/*!

  
  \note
    This is only supported on the FSCC cards.

*/
/******************************************************************************/
int serialfc_enable_external_transmit(serialfc_handle h, unsigned num_frames)
{
    return ioctl_set_integer(h, IOCTL_FASTCOM_ENABLE_EXTERNAL_TRANSMIT, num_frames);
}

/******************************************************************************/
/*!

  
  \note
    This is only supported on the FSCC cards.

*/
/******************************************************************************/
int serialfc_disable_external_transmit(serialfc_handle h)
{
    return ioctl_action(h, IOCTL_FASTCOM_DISABLE_EXTERNAL_TRANSMIT);
}

/******************************************************************************/
/*!

  
  \note
    This is only supported on the FSCC cards.

*/
/******************************************************************************/
int serialfc_get_external_transmit(serialfc_handle h, unsigned *num_frames)
{
    return ioctl_get_integer(h, IOCTL_FASTCOM_GET_EXTERNAL_TRANSMIT, (int *)num_frames);
}

/******************************************************************************/
/*!

  
  \note
    This is only supported on the FSCC cards.

*/
/******************************************************************************/
int serialfc_set_frame_length(serialfc_handle h, unsigned num_chars)
{
    return ioctl_set_integer(h, IOCTL_FASTCOM_SET_FRAME_LENGTH, num_chars);
}

/******************************************************************************/
/*!
  
  \note
    This is only supported on the FSCC cards.

*/
/******************************************************************************/
int serialfc_get_frame_length(serialfc_handle h, unsigned *num_chars)
{
    return ioctl_get_integer(h, IOCTL_FASTCOM_GET_FRAME_LENGTH, (int *)num_chars);
}

/******************************************************************************/
/*!
  
  \note
    This is only supported on the FSCC cards.

*/
/******************************************************************************/
int serialfc_enable_9bit(serialfc_handle h)
{
    return ioctl_action(h, IOCTL_FASTCOM_ENABLE_9BIT);
}

/******************************************************************************/
/*!
  
  \note
    This is only supported on the FSCC cards.

*/
/******************************************************************************/
int serialfc_disable_9bit(serialfc_handle h)
{
    return ioctl_action(h, IOCTL_FASTCOM_DISABLE_9BIT);
}

/******************************************************************************/
/*!
  
  \note
    This is only supported on the FSCC cards.

*/
/******************************************************************************/
int serialfc_get_9bit(serialfc_handle h, unsigned *status)
{
    return ioctl_get_boolean(h, IOCTL_FASTCOM_GET_9BIT, status);
}

int serialfc_enable_fixed_baud_rate(serialfc_handle h, unsigned rate)
{
    return ioctl_set_integer(h, IOCTL_FASTCOM_ENABLE_FIXED_BAUD_RATE, rate);
}

int serialfc_disable_fixed_baud_rate(serialfc_handle h)
{
    return ioctl_action(h, IOCTL_FASTCOM_DISABLE_FIXED_BAUD_RATE);
}

int serialfc_get_fixed_baud_rate(serialfc_handle h, int *rate)
{
    return ioctl_get_integer(h, IOCTL_FASTCOM_GET_FIXED_BAUD_RATE, rate);
}

int serialfc_get_card_type(serialfc_handle h, unsigned *type)
{
    return ioctl_get_integer(h, IOCTL_FASTCOM_GET_CARD_TYPE, (int *)type);
}
 
int serialfc_write(serialfc_handle h, char *buf, unsigned size, unsigned *bytes_written, 
                   OVERLAPPED *o)
{
//TODO
    UNUSED(h);
    UNUSED(buf);
    UNUSED(size);
    UNUSED(bytes_written);
    UNUSED(o);

    return 0;
#if 0
  BOOL result;
        
  result = WriteFile(h, buf, size, (DWORD*)bytes_written, o);

  return (result == TRUE) ? ERROR_SUCCESS : GetLastError();
#endif
}

int serialfc_read(serialfc_handle h, char *buf, unsigned size, unsigned *bytes_read, 
                  OVERLAPPED *o)
{
//TODO
    UNUSED(h);
    UNUSED(buf);
    UNUSED(size);
    UNUSED(bytes_read);
    UNUSED(o);

    return 0;
#if 0
  BOOL result;

  result = ReadFile(h, buf, size, (DWORD*)bytes_read, o);

  return (result == TRUE) ? ERROR_SUCCESS : GetLastError();
#endif
}

int serialfc_disconnect(serialfc_handle h)
{
    int result;

#ifdef _WIN32
    result = CloseHandle(h);

    return (result == TRUE) ? 0 : GetLastError();
#else

    result = close(h);

    return (result != -1) ? 0 : errno;
#endif
}
