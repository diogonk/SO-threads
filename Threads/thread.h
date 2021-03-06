#ifndef __THREAD_H__
#define __THREAD_H__

/* tasks.h */
#include <stdint.h>
#include "hw_nvic.h"
#define MAX_THREADS 100

typedef struct ThreadControlBlock {
    uint32_t *ThreadStack;
    void (*ThreadFn )();
    uint32_t Attributes;
    uint32_t id;
} ThreadControlBlock;

void createThread(void (*ThreadFn )(), uint32_t *ThreadStack, uint32_t StackSize);
uint32_t getCurrentThread(void);
void startSwitcher(void);

#endif