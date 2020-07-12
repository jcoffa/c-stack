#include "Stack.h"


Stack *stackNew(size_t elemSize, void (*deleteFunc)(void *), char *(*printFunc)(void *));


void stackClear(Stack *stack);


void stackFree(Stack *stack);


void stackPush(Stack *stack, void *data);


void *stackPeek(Stack *stack);


void *stackPop(Stack *stack);


bool stackIsEmpty(const Stack *stack);


char *stackTopToString(const Stack *stack);


void stackPrintTop(const Stack *stack);


char *stackToString(const Stack *stack);


void stackPrint(const Stack *stack);

