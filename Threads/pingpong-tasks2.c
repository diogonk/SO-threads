// PingPongOS - PingPong Operating System
// Prof. Carlos A. Maziero, DINF UFPR
// Versão 1.1 -- Julho de 2016

// Teste da gestão básica de tarefas

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "thread.h"

#define MAXTASK 1000

uint32_t activeThread = 0;

// corpo das threads
void BodyTask(void* arg)
{

  UARTprintf("Iniciei  tarefa %lu\n", getCurrentThread());
  activeThread = getCurrentThread();
  while (activeThread <= MAXTASK)
  {
  }
  //while(id != activeThread) {}

  //activeThread++;
  // passa o controle para a proxima tarefa
  // while(currentThread != task[])
  // next = (task_id() < MAXTASK) ? task_id() + 1 : 1;
  // task_switch(&task[next]);

  UARTprintf("Encerrei tarefa %lu\n", getCurrentThread());
  //task_exit(0);
	return;
}
