#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**************
 * STRUCTURES *
 **************/

/*
 * This stack implementation is a "Linked List Stack" (often abbreviated to "Linked Stack"),
 * which uses a singly-linked list to store a collection of elements.
 *
 * This approach, in contrast to the "Array Stack", is typically more memory efficient
 * for large stacks (because memory is allocated per-element instead of having lots of
 * empty space in an array) but slightly less runtime efficient on average due to the
 * expensiveness of allocating memory every time a new item is pushed.
 *
 * This structure represents a node in the linked stack that holds a single piece of
 * abstracted (void *) data.
 */
typedef struct stackFrame {
	void *data;
	struct stackFrame *next;
} Frame;

/*
 * Metadata top of the stack. 
 * Contains the function pointers for working with the abstracted list data.
 */
typedef struct stack {
	Frame *top;					// Stack frame at the top of the stack
	unsigned int size;			// Number of stack frames in the stack
	void (*deleteData)(void *);	// Function pointer to free an element in the stack
	char *(*printData)(void *);	// Function pointer to create a string from a stack element
} Stack;


/*************
 * FUNCTIONS *
 *************/

/*
 * Function to initialize the Stack metadata head to the appropriate function pointers.
 * Allocates memory to the struct, unless any of the function pointers are NULL. In this
 * case, NULL is returned instead and no memory is allocated.
 *
 * The Stack provides an interface to a generic collection of data. The two 
 * function pointers allow the struct to print and delete its data.
 * The (void *) arguments are to be casted into their proper data type (i.e. whatever
 * data type the tree will be holding) and do as follows:
 *
 *  char *printFunc(void *toPrint)  : return a string representation of `toPrint`
 *  void deleteFunc(void *toDelete) : free all memory associated with `toDelete`
 *
 * Examples of these functions are provided for string (char *) data in the README.
 */
Stack *stackNew(void (*deleteFunc)(void *), char *(*printFunc)(void *));


/*
 * Allocates memory for a new Frame struct and returns a pointer to it.
 */
Frame *stackFrameNew(void *data);


/*
 * Removes every element from a Stack without deleting the stack itself.
 */
void stackClear(Stack *stack);


/*
 * Frees all memory associated with a Stack, including the stack itself.
 */
void stackFree(Stack *stack);


/*
 * Pushes the data to the top of the stack.
 */
void stackPush(Stack *stack, void *data);


/*
 * Returns the top of the stack without removing it.
 */
void *stackPeek(const Stack *stack);


/*
 * Returns the top of the stack after removing it from the stack.
 */
void *stackPop(Stack *stack);


/*
 * Returns the number of elements in the stack.
 */
unsigned int stackGetSize(const Stack *stack);


/*
 * Returns true if the Stack contains 0 elements, and false otherwise.
 */
bool stackIsEmpty(const Stack *stack);


/*
 * Returns a string representing the element at the top of the Stack using the stack's
 * `printData` function pointer to create the string.
 *
 * The string msut be freed by the calling function after use.
 */
char *stackTopToString(const Stack *stack);


/*
 * A convenient alias for printing the string returned by `stackTopToString(stack)`
 * and then freeing the string that was created after printing it.
 * A newline is printed after the stack-element-string is done printing.
 */
void stackPrintTop(const Stack *stack);


/*
 * Returns a string representing the Stack using the stack's `printData` function pointer
 * to create the string, starting from the top of the stack and working downwards.
 *
 * The string must be freed by the calling function after use.
 */
char *stackToString(const Stack *stack);


/*
 * A convenient alias for printing the string returned by `stackToString(stack)`
 * and then freeing the string that was created after printing it.
 * A newline is printed after the stack-string is done printing.
 */
void stackPrint(const Stack *stack);


/*
 * Execute a function `func` on each node in the stack
 * starting from the top and working downwards.
 */
void stackMap(Stack *stack, void (*func)(Frame *));

#endif	// STACK_H

