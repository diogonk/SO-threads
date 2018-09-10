//*****************************************************************************
//
// hello.c - Simple hello world example.
//
// Copyright (c) 2013-2014 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
// This is part of revision 2.1.0.12573 of the EK-TM4C1294XL Firmware Package.
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "hw_memmap.h"
#include "hw_types.h"
#include "driverlib/gpio.h"
#include "drivers/pinout.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "Threads/thread.h"
#include "Threads/pingpong-tasks1.h"
#include "debug.h"

#include <stdlib.h>

int testafila(void);
#define STACK_SIZE 64

uint32_t *createThreadStack(void);

uint32_t Thread1Stack[STACK_SIZE];
uint32_t Thread2Stack[STACK_SIZE];
//uint32_t Thread3Stack[STACK_SIZE];

//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>Hello World (hello)</h1>
//!
//! A very simple ``hello world'' example.  It simply displays ``Hello World!''
//! on the UART and is a starting point for more complicated applications.
//!
//! Open a terminal with 115,200 8-N-1 to see the output for this demo.
//
//*****************************************************************************

//*****************************************************************************
//
// System clock rate in Hz.
//
//*****************************************************************************
uint32_t g_ui32SysClock;

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void __error__(char *pcFilename, uint32_t ui32Line)
{
  UARTprintf("%s %d\n", pcFilename, ui32Line);
}
#endif

//*****************************************************************************
//
// Configure the UART and its pins.  This must be called before UARTprintf().
//
//*****************************************************************************
void ConfigureUART(void)
{
  //
  // Enable the GPIO Peripheral used by the UART.
  //
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

  //
  // Enable UART0
  //
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

  //
  // Configure GPIO Pins for UART mode.
  //
  ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
  ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
  ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
  ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_2);

  //
  // Initialize the UART for console I/O.
  //
  UARTStdioConfig(0, 115200, g_ui32SysClock);
}

uint32_t *createThreadStack(void)
{
  uint32_t *aux;
  aux = malloc(STACK_SIZE * sizeof(uint32_t));
  return aux;
}

//*****************************************************************************
//
// Print "Hello World!" to the UART on the Intelligent UART Module.
//
//*****************************************************************************
int main(void)
{
  char teste[10]; //
  uint32_t cont;
  // Run from the PLL at 120 MHz.
  //
  g_ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                           SYSCTL_OSC_MAIN | SYSCTL_USE_PLL |
                                           SYSCTL_CFG_VCO_480),
                                          120000000);

  //
  // Configure the device pins.
  //
  PinoutSet(false, false);

  //
  // Enable the GPIO pins for the LED D1 (PN1).
  //
  ROM_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1);
  ROM_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_2);

  //
  // Initialize the UART.
  //
  ConfigureUART();

  //
  // Hello!
  //
  UARTprintf("\n\n\n\n\n\n\n\n\n\n\n");
  UARTprintf("\n\n\n\n\n\n\n\n\n\n\n");
  UARTprintf("\n\n\n\n\n\n\n\n\n\n\n");
  UARTprintf("Hello, world  TIVA CCCC !\n");

  UARTprintf("Ligando o LED\n");
  //
  // Turn on D1.
  //
  LEDWrite(CLP_D1, 1);
  LEDWrite(CLP_D2, 0);

  //
  // Delay for a bit.
  //
  SysCtlDelay(g_ui32SysClock / 10 / 3);

  //
  UARTprintf("Desligando o LED\n");
  //
  LEDWrite(CLP_D1, 0);
  LEDWrite(CLP_D2, 1);
  //
  // Delay for a bit.
  //
  SysCtlDelay(g_ui32SysClock / 10 / 3);
  UARTprintf("Criando Tarefa 1\n");
  createThread(BodyPing, Thread1Stack, STACK_SIZE);
  UARTprintf("Criando Tarefa 2\n");
  createThread(BodyPong, Thread2Stack, STACK_SIZE);
  startSwitcher(); // start the thread switching (this does not return)
}
