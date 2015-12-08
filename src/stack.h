/**
 * @file stack.h
 * @author: Brecht Vandevoort
 *
 * @brief Definition of the stack
 */

#ifndef STACK_H
#define STACK_H

#include <stdint.h>

#define STACK_START_SIZE 1

/**
 * @brief Representation of the stack
 */
typedef struct
{
	uint16_t *buffer;
	uint32_t size;
	uint32_t maxSize;
} Stack;

/**
 * @brief Initializes the stack.
 * @param stack The stack to initialize.
 */
void initStack(Stack *stack);

/**
 * @brief Destroys the stack.
 * @param stack The stack to destroy.
 */
void destroyStack(Stack *stack);

/**
 * @brief Pushes a value on top of the stack.
 * @param value The value to push.
 * @param stack The stack.
 */
void pushStack(uint16_t value, Stack *stack);

/**
 * @brief Pops an item from the stack.
 * @param result Pointer to write the popped value into.
 * @param stack The stack.
 * @return 0 on success, -1 if failed.
 */
int popStack(uint16_t *result, Stack *stack);

#endif
