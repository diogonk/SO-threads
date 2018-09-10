/* tasks.h */
typedef struct {
    uint32_t *ThreadStack;
    void (*ThreadFn )();
    uint32_t Attributes;
    uint32_t id;
} ThreadControlBlock;

void createThread(void (*ThreadFn )(), uint32_t *ThreadStack, uint32_t StackSize);
uint32_t getCurrentThread(void)
void startSwitcher(void);
