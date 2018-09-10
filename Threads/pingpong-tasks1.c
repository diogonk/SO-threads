// PingPongOS - PingPong Operating System
// Prof. Carlos A. Maziero, DINF UFPR
// Versão 1.1 -- Julho de 2016

// Teste da gestão básica de tarefas

#include <stdio.h>
#include <stdlib.h>
#include "pingpong-tasks1.h"

volatile uint8_t pingpong = 0;
// corpo da thread Ping
void BodyPing(void)
{
  uint32_t i = 0;
  while (1)
  {
    if (!pingpong)
			i++;
    if (i > (0xFFFFFF - 20))
    {
      UARTprintf("PING\n");
      i = 0;
      pingpong = 1;
    }
  }
}

// corpo da thread Pong
void BodyPong(void *arg)
{
  while (1)
  {
    if (pingpong == 1)
    {
      pingpong = 0;
      UARTprintf("PONG\n");
    }
  }
}
