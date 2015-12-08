/**
 * @file stack.c
 * @author: Brecht Vandevoort
 *
 * @brief Implementation of the stack.
 */
#include "stack.h"

#include <string.h>
#include <stdlib.h>

/* Private functions */
/**
 * @brief Allocates more space for the given stack
 * @param stack The stack.
 */
void growStack(Stack *stack)
{
	uint16_t *tmpBuffer = stack->buffer;
	uint32_t oldMaxSize = stack->maxSize;
	
	stack->maxSize = 2 * oldMaxSize;
	stack->buffer = (uint16_t*) malloc(sizeof(uint16_t) * stack->maxSize);
	
	memcpy(stack->buffer, tmpBuffer, oldMaxSize * sizeof(uint16_t));

	free(tmpBuffer);
}

/*Public functions */
void initStack(Stack *stack)
{
	stack->size = 0;
	stack->maxSize = STACK_START_SIZE;
	stack->buffer = (uint16_t*) malloc(sizeof(uint16_t) * stack->maxSize);
}

void destroyStack(Stack *stack)
{
	free(stack->buffer);
	stack->size = 0;
	stack->maxSize = 0;
}

void pushStack(uint16_t value, Stack *stack)
{
	if(stack->size == stack->maxSize)
	{
		growStack(stack);
	}
	stack->buffer[stack->size] = value;
	stack->size += 1;
}

int popStack(uint16_t *result, Stack *stack)
{
	if (stack->size == 0)
		return -1;
	
	stack->size -= 1;
	*result = stack->buffer[stack->size];

	return 0;
}

