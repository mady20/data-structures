// author: mady 
// date: 09/09/2025 12:28 PM
// stack.c 


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct s_stack {
  int stack_ptr;
  int capacity;
  int* array;
};

typedef struct s_stack Stack;

void init(Stack* stack){
  stack->capacity = 3;
  stack->stack_ptr = -1;
  stack->array = (int*)malloc(sizeof(int) * stack->capacity);
}

bool isEmpty(Stack* stack){
  return stack->stack_ptr == -1;
}


void destroy(Stack* stack){
  free(stack->array);
  stack->array = NULL;   
  stack->capacity = 0;
  stack->stack_ptr = -1;
}

bool peek(Stack* stack , int* value){
  if (!isEmpty(stack)){
    *value = stack->array[stack->stack_ptr];
    return true;
  }
  return false;
}

void push(Stack* stack, int value){
  if(stack->stack_ptr == stack->capacity - 1){
    stack->capacity *= 2;
    int* tmp = (int*) realloc(stack->array, stack->capacity * sizeof(int));
        if (!tmp) {
            fprintf(stderr, "Memory Reallocation Failed!\n");
            exit(1);
        }
        stack->array = tmp;
  }
  stack->array[++stack->stack_ptr] = value; 
}


int size(Stack* stack){
  return stack->stack_ptr + 1;
}

bool pop(Stack* stack, int* value){
  if(stack->stack_ptr > -1){
    *value = stack->array[stack->stack_ptr--];
    return true;
  }
  return false;
}

int main(void){
  Stack stack; 
  init(&stack);
  push(&stack, 1);  
  push(&stack, 2);  
  push(&stack, 3);
  push(&stack, 4);
  push(&stack, 5);
  while(!isEmpty(&stack)){
    int cur;
    if(pop(&stack, &cur)){
      printf("%d\n", cur);
    }
  }
  destroy(&stack);
  return 0;
}
