// C program for array implementation of stack 
#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 

// A structure to represent a stack 
typedef struct 
{ 
	unsigned short top; 
	unsigned capacity; 
	unsigned short* array; 
} Stack; 

// function to create a stack of given capacity. It initializes size of 
// stack as 0 
Stack* createStack(unsigned capacity) 
{ 
	Stack* stack = (Stack*) malloc(sizeof(Stack)); 
	stack->capacity = capacity; 
	stack->top = -1; 
	stack->array = (unsigned short*) malloc(stack->capacity * sizeof(unsigned short)); 
	return stack; 
} 

// Stack is full when top is equal to the last index 
int isFull(Stack* stack) 
{ return stack->top == stack->capacity - 1; } 

// Stack is empty when top is equal to -1 
int isEmpty(Stack* stack) 
{ return stack->top == -1; } 

// Function to add an item to stack. It increases top by 1 
void push(Stack* stack, unsigned short item) 
{ 
	if (isFull(stack)) 
		return; 
	stack->array[++stack->top] = item; 
	printf("%d pushed to stack\n", item); 
} 

// Function to remove an item from stack. It decreases top by 1 
unsigned short pop(Stack* stack) 
{ 
	if (isEmpty(stack)) 
		return (unsigned short) -0xffff; 
	return stack->array[stack->top--]; 
} 
