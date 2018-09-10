// PingPongOS - PingPong Operating System
// Prof. Carlos A. Maziero, DINF UFPR
// Versão 1.1 -- Julho de 2016

// Teste da gestão básica de tarefas

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "thread.h"

#define MAXTASK 20

uint32_t activeThread = 0;

// corpo das threads
void BodyTask(void *arg)
{

  uint8_t status = 0;
  while (1)
  {
    if (activeThread == getCurrentThread() && status == 0)
    {
      UARTprintf("Iniciei  tarefa %i\n", getCurrentThread());
      activeThread++;
      status = 1;
    }
    if (activeThread == getCurrentThread() && status == 1)
    {
      UARTprintf("Ence&& status == 0 \n(", getCurrentThread());
      activeThread--;
      status = 2;
    }
  }
}