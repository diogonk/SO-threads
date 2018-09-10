// PingPongOS - PingPong Operating System
// Prof. Carlos A. Maziero, DINF UFPR
// Versão 1.2 -- Outubro de 2016

// Interface do núcleo para as aplicações

#ifndef __PPOS__
#define __PPOS__

#include "ppos_data.h"		// estruturas de dados necessárias


// funções gerais ==============================================================

// Inicializa o sistema operacional; deve ser chamada no inicio do main()
void ppos_init () ;

// gerência de tarefas =========================================================

// Cria uma nova tarefa. Retorna um ID> 0 ou erro.
int task_create (task_t *task,			// descritor da nova tarefa
                 void (*start_func)(void *),	// funcao corpo da tarefa
                 void *arg) ;			// argumentos para a tarefa

// Termina a tarefa corrente, indicando um valor de status encerramento
void task_exit (int exitCode) ;

// alterna a execução para a tarefa indicada
int task_switch (task_t *task) ;

// retorna o identificador da tarefa corrente (main deve ser 0)
int task_id ();

// operações de escalonamento ==================================================

// libera o processador para a próxima tarefa, retornando à fila de tarefas
// prontas ("ready queue")
void task_yield () ;

// define a prioridade estática de uma tarefa (ou a tarefa atual)
void task_setprio (task_t *task, int prio) ;

// retorna a prioridade estática de uma tarefa (ou a tarefa atual)
int task_getprio (task_t *task) ;

// operações de sincronização ==================================================

// a tarefa corrente aguarda o encerramento de outra task
int task_join (task_t *task) ;

// operações de gestão do tempo ================================================

// suspende a tarefa corrente por t milissegundos
void task_sleep (int t) ;

// retorna o relógio atual (em milisegundos)
unsigned int systime () ;

// operações de IPC ============================================================

// semáforos

// cria um semáforo com valor inicial "value"
int sem_create (semaphore_t *s, int value) ;

// requisita o semáforo
int sem_down (semaphore_t *s) ;

// libera o semáforo
int sem_up (semaphore_t *s) ;

// destroi o semáforo, liberando as tarefas bloqueadas
int sem_destroy (semaphore_t *s) ;

// mutexes

// Inicializa um mutex (sempre inicialmente livre)
int mutex_create (mutex_t *m) ;

// Solicita um mutex
int mutex_lock (mutex_t *m) ;

// Libera um mutex
int mutex_unlock (mutex_t *m) ;

// Destrói um mutex
int mutex_destroy (mutex_t *m) ;

// barreiras

// Inicializa uma barreira
int barrier_create (barrier_t *b, int N) ;

// Chega a uma barreira
int barrier_join (barrier_t *b) ;

// Destrói uma barreira
int barrier_destroy (barrier_t *b) ;

// filas de mensagens

// cria uma fila para até max mensagens de size bytes cada
int mqueue_create (mqueue_t *queue, int max, int size) ;

// envia uma mensagem para a fila
int mqueue_send (mqueue_t *queue, void *msg) ;

// recebe uma mensagem da fila
int mqueue_recv (mqueue_t *queue, void *msg) ;

// destroi a fila, liberando as tarefas bloqueadas
int mqueue_destroy (mqueue_t *queue) ;

// informa o número de mensagens atualmente na fila
int mqueue_msgs (mqueue_t *queue) ;

#endif
