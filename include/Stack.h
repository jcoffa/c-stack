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
 * Metadata top of the stack. 
 * Contains the function pointers for working with the abstracted stack data.
 *
 * This stack implementation is an "Array Stack", which uses an array to store a collection of elements.
 *
 * This approach, in contrast to the "Linked List Stack", is less memory efficient
 * for large stacks (because there is typically empty within the underlying array
 * whenever the stack isn't full, whereas the linked list stack allocates memory
 * per-element) but slightly more runtime efficient on average due to no memory
 * allocation being performed whenever a new element is pushed onto the stack.
 */
typedef struct stack {
	int top;					// Number of elements in the stack
	int maxSize;				// Maximum number of elements this stack can hold
	void (*deleteData)(void *);	// Function pointer to free an element in the stack
	char *(*printData)(void *);	// Function pointer to create a string from a stack element
	void *data[];				// Data stored by the stack
} Stack;


/*************
 * FUNCTIONS *
 *************/

/*
 * Function to initialize the Stack metadata head to the appropriate function pointers
 * and giving the maximum size of the stack.
 * Allocates memory to the struct, unless any of the function pointers are NULL. In this
 * case, NULL is returned instead and no memory is allocated.
 *
 * The Stack provides an interface to a generic collection of data. The two 
 * function pointers allow the struct to print and delete its data.
 * The (void *) arguments are to be casted into their proper data type (i.e. whatever
 * data type the stack will be holding) and do as follows:
 *
 *  char *printFunc(void *toPrint)  : return a string representation of `toPrint`
 *  void deleteFunc(void *toDelete) : free all memory associated with `toDelete`
 *
 * Examples of these functions are provided for string (char *) data in the README.
 */
Stack *stackNew(int maxSize, void (*deleteFunc)(void *), char *(*printFunc)(void *));


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
 * If the push operation can't be completed for whatever reason,
 * this function returns `false`. Otherwise, it returns `true` for a
 * successful push.
 *
 * `false` may be returned if `stack` is NULL, or if the stack is full.
 */
bool stackPush(Stack *stack, void *data);


/*
 * Returns the top of the stack without removing it,
 * or NULL if the stack is empty.
 *
 * NULL may also be returned if NULL was actually being stored in that
 * position in the stack.
 */
void *stackPeek(const Stack *stack);


/*
 * Returns the top of the stack after removing it from the stack,
 * or NULL if the stack is empty.
 *
 * NULL may also be returned if NULL was actually being stored in that
 * position in the stack.
 */
void *stackPop(Stack *stack);


/*
 * Returns the number of elements in the stack, or -1 if the stack is NULL.
 */
int stackGetSize(const Stack *stack);


/*
 * Returns true if the Stack contains 0 elements, and false otherwise.
 */
bool stackIsEmpty(const Stack *stack);


/*
 * Returns true if the Stack doesn't have space to store any more elements, and false otherwise.
 */
bool stackIsFull(const Stack *stack);


/*
 * Returns a string representing the element at the top of the Stack using the stack's
 * `printData` function pointer to create the string.
 *
 * The string must be freed by the calling function after use.
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
 * Execute a function `func` on each element in the stack
 * starting from the top and working downwards.
 */
void stackMap(Stack *stack, void (*func)(void *));

#endif	// STACK_H

