#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "stack_calculator.h"

// Allocate a new Stack struct and return a pointer to it.
Stack *stack_create(void) {
  // this one is complete, no need to change it!
  Stack *out;
  out = (Stack *)calloc(1, sizeof(Stack));
  return out;
}

// Add a new node at the front of the stack. Return false if we are unable to do
// so (eg, if memory allocation fails).
bool stack_push(Stack *s, CalculatorItem item) {
  // your code here
  Node *new_node = calloc(1, sizeof(Node));
  if (new_node) {
	new_node->item = item;
	new_node->next = s->top;
	s->top = new_node;
  	return true;
  }

  return false;


}

// Pop the stack and put the result into the output pointer.
// return false if the stack is NULL or if it is empty.
bool stack_pop(Stack *s, CalculatorItem *output) {
  // your code here
  if (!s || stack_empty(s)) {
	  return false;
  }

 *output  = s->top->item; 
 Node *delete_node = s->top;
 s->top = s->top->next;
 free(delete_node);
 delete_node = NULL;

  
  return true;
	
}

// Returns true if the specified stack is empty.
bool stack_empty(Stack *s) {
  // your code here
	if (!s || s->top == NULL) {
		return true;
	}
  return false;
}

// Free all of the memory used by this stack, including its linked list.
// When you are done, set the pointer to NULL.
void stack_delete(Stack **s) {
  // your code here
  CalculatorItem o;
  while (!stack_empty(*s)) {
	stack_pop(*s, &o);
  }

  free(*s);
  *s = NULL;

}

// Returns true if we were able to successfully perform the computation step,
// and false if there was an error of some kind.
bool stack_compute_step(Stack *s, CalculatorItem item) {
  // your code here
  if (item.type == NUMBER) {
	 stack_push(s, item);
  } 

  else {
	  CalculatorItem num1, num2;

	  if (stack_empty(s)) {
		  return false;
	  }

	  stack_pop(s, &num2);

	  if (stack_empty(s)) {
		  return false;
	  }

	  stack_pop(s, &num1);

	  if (item.type == ADD) {
		  CalculatorItem x = {NUMBER, num1.value+num2.value};
		  stack_push(s, x);
	  }

	  else if (item.type == SUBTRACT) {
		  CalculatorItem x = {NUMBER, num1.value-num2.value};
		  stack_push(s, x);
	  }

	  else if (item.type == MULTIPLY) {
		  CalculatorItem x = {NUMBER, num1.value*num2.value};
		  stack_push(s, x);
	  }

	  else if (item.type == DIVIDE) {
		  if (num2.value == 0) {
			  return false;
		  }

		  CalculatorItem x = {NUMBER, num1.value/num2.value};
		  stack_push(s, x);
	  }

  }

  return true;
}

/*
int main(void) {
	Stack *test = stack_create();
	CalculatorItem a = {NUMBER, 1};
	CalculatorItem b = {NUMBER, 2};
	CalculatorItem c = {NUMBER, 3};
	stack_push(test, a);
	stack_push(test, b);
	stack_push(test, c);

	printf("%f\n", test->top->item.value);
	printf("%f\n", test->top->next->item.value);
	printf("%f\n", test->top->next->next->item.value);

	printf("********************\n");
	
	CalculatorItem *p_x = malloc(sizeof(CalculatorItem));

	stack_pop(test, p_x);
	printf("Poppped output is %f.\n", (p_x->value));
	stack_pop(test, p_x);
	printf("Poppped output is %f.\n", (p_x->value));
	stack_pop(test, p_x);
	printf("Poppped output is %f.\n", (p_x->value));
	
	free(p_x);
	p_x = NULL;

	stack_delete(&test);

	return 0;
}
*/

