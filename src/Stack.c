#include "Stack.h"


Stack *stackNew(int maxSize, void (*deleteFunc)(void *), char *(*printFunc)(void *)) {
	if (deleteFunc == NULL || printFunc == NULL) {
		return NULL;
	}

	Stack *toReturn = malloc(sizeof(Stack) + (sizeof(void*) * maxSize));

	// Can't assume malloc works every time, no matter how unlikely
	if (toReturn == NULL) {
		return NULL;
	}

	toReturn->top = -1;
	toReturn->maxSize = maxSize;
	toReturn->deleteData = deleteFunc;
	toReturn->printData = printFunc;

	return toReturn;
}


void stackClear(Stack *stack) {
	if (stack == NULL) {
		return;
	}

	while (!stackIsEmpty(stack)) {
		// stackPop already removes and frees the stack DynFrame struct,
		// so we only have to delete the frame's stored data
		stack->deleteData(stackPop(stack));
	}
}


void stackFree(Stack *stack) {
	if (stack == NULL) {
		return;
	}

	stackClear(stack);
	free(stack);
}


bool stackPush(Stack *stack, void *data) {
	if (stack == NULL || stackIsFull(stack)) {
		return false;
	}

	(stack->data)[++stack->top] = data;
	return true;
}


void *stackPeek(const Stack *stack) {
	if (stack == NULL || stackIsEmpty(stack)) {
		return NULL;
	}

	return (stack->data)[stack->top];
}


void *stackPop(Stack *stack) {
	if (stack == NULL || stackIsEmpty(stack)) {
		return NULL;
	}

	return (stack->data)[(stack->top)--];
}


int stackGetSize(const Stack *stack) {
	if (stack == NULL) {
		return 0;
	}
	return stack->top + 1;
}


bool stackIsEmpty(const Stack *stack) {
	return stack->top < 0;
}


bool stackIsFull(const Stack *stack) {
	return stack->top == stack->maxSize - 1;
}


char *stackTopToString(const Stack *stack) {
	if (stack == NULL) {
		return NULL;
	}

	char *toReturn;
	if (stackIsEmpty(stack)) {
		toReturn = malloc(sizeof(char));
		toReturn[0] = '\0';
	} else {
		toReturn = stack->printData(stackPeek(stack));
	}

	return toReturn;
}


void stackPrintTop(const Stack *stack) {
	if (stack == NULL) {
		return;
	}

	char *toPrint = stackTopToString(stack);
	printf("%s\n", toPrint);
	free(toPrint);
}


char *stackToString(const Stack *stack) {
	if (stack == NULL) {
		return NULL;
	}

	// Start with the top of the stack
	char *toReturn = stackTopToString(stack);
	size_t length = strlen(toReturn);

	// Iterate over all elements beyond the first
	void *cur;
	for (int i = stack->top-1; i >= 0; i--) {
		cur = (stack->data)[i];

		char *dataStr = stack->printData(cur);
		length += strlen(dataStr) + 1;	// +1 for newline
		toReturn = realloc(toReturn, length + 1);	// +1 for null terminator
		strcat(toReturn, "\n");
		strcat(toReturn, dataStr);
		free(dataStr);
	}

	return toReturn;
}


void stackPrint(const Stack *stack) {
	if (stack == NULL) {
		return;
	}

	char *toPrint = stackToString(stack);
	printf("%s\n", toPrint);
	free(toPrint);
}


void stackMap(Stack *stack, void (*func)(void *)) {
	if (stack == NULL) {
		return;
	}

	for (int i = stack->top; i >= 0; i--) {
		func((stack->data)[i]);
	}
}

