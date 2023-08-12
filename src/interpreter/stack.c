#include "interpreter.h"

// -----Basic Stack Functions-----

Stack *stack_push(Stack **stack)
{
	Stack *new = xmalloc(sizeof(Stack));
	if (pipe(new->pd) == -1)
	{
		printf("piping failed\n");
	}
	new->written_to = false;
	new->next = *stack;
	*stack = new;
	return *stack;
}

Stack *stack_top(Stack **stack)
{
	Stack	*top;

	top = *stack;
	if (*stack == NULL)
		return (NULL);
	return (top);
}

Stack *stack_pop(Stack **stack)
{
	Stack	*pop;

	pop = *stack;
	if (*stack == NULL)
		return (NULL);
	*stack = (*stack)->next;
	free(pop);
	return (*stack);
}