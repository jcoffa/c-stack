#include "Stack.h"


Stack *stackNew(void (*deleteFunc)(void *), char *(*printFunc)(void *)) {
	if (deleteFunc == NULL || printFunc == NULL) {
		return NULL;
	}

	Stack *toReturn = malloc(sizeof(Stack));

	// Can't assume malloc works every time, no matter how unlikely
	if (toReturn == NULL) {
		return NULL;
	}

	toReturn->top = NULL;
	toReturn->size = 0;
	toReturn->deleteData = deleteFunc;
	toReturn->printData = printFunc;

	return toReturn;
}


Frame *stackFrameNew(void *data) {
	Frame *toReturn = malloc(sizeof(Frame));

	// Can't assume malloc works every time, no matter how unlikely
	if (toReturn == NULL) {
		return NULL;
	}

	toReturn->data = data;
	toReturn->next = NULL;

	return toReturn;
}


void stackClear(Stack *stack) {
	if (stack == NULL) {
		return;
	}

	while (!stackIsEmpty(stack)) {
		// stackPop already removes and frees the stack Frame struct,
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


void stackPush(Stack *stack, void *data) {
	if (stack == NULL) {
		return;
	}

	Frame *toPush = stackFrameNew(data);

	toPush->next = stack->top;
	stack->top = toPush;
	(stack->size)++;
}


void *stackPeek(const Stack *stack) {
	if (stack == NULL || stack->top == NULL) {
		return NULL;
	}

	return stack->top->data;
}


void *stackPop(Stack *stack) {
	if (stack == NULL || stack->top == NULL) {
		return NULL;
	}

	// Save the top frame and its data
	Frame *top = stack->top;
	void *toReturn = top->data;

	// Move the stack pointer
	stack->top = stack->top->next;
	(stack->size)--;

	// Free the removed frame and return its data
	free(top);
	return toReturn;
}


unsigned int stackGetSize(const Stack *stack) {
	if (stack == NULL) {
		return 0;
	}
	return stack->size;
}


bool stackIsEmpty(const Stack *stack) {
	return stackGetSize(stack) == 0;
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
		toReturn = stack->printData(stack->top->data);
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

	// Prepare to iterate over the rest of the stack beyond the top
	Frame *cur;
	if (stackIsEmpty(stack)) {
		// If the stack is empty then `cur = stack->top->next`
		// will error out or segfault since `stack->top` is NULL,
		// so this guard is necessary
		cur = NULL;
	} else {
		cur = stack->top->next;
	}

	while (cur != NULL) {
		char *frameStr = stack->printData(cur->data);
		length += strlen(frameStr) + 1;	// +1 for newline
		toReturn = realloc(toReturn, length + 1);	// +1 for null terminator
		strcat(toReturn, "\n");
		strcat(toReturn, frameStr);
		free(frameStr);

		cur = cur->next;
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

