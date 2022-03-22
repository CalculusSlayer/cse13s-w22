#include "stack_calculator.h"
#include <stdio.h>

void stack_print(Stack *x);
void check_empty(Stack *x);

void stack_print(Stack *x) {
	printf("Stack: ");
	Node *temp = x->top;
	while (temp) {
		printf("%f ", temp->item.value);
		temp = temp->next;
	}

	printf("\n");
	check_empty(x);

	return;
}

void check_empty(Stack *x) {
	if (stack_empty(x)) {
		printf("Stack is empty according to stack_empty.\n");
	}

	else {
		printf("Stack is NOT empty according to stack_empty.\n");
	}

	return;
}	

int main(void) {
	Stack *test = stack_create();
	stack_print(test);
	printf("\n");
	
	CalculatorItem a = {NUMBER, 0};
	CalculatorItem b = {NUMBER, 20};
	CalculatorItem c = {NUMBER, 40};

	printf("Pushing 0 to stack.\n");
	stack_push(test, a);
	stack_print(test);
	printf("\n");

	printf("Pushing 20 to stack.\n");
	stack_push(test, b);
	stack_print(test);
	
	printf("\n");

	CalculatorItem popper;
	printf("Popping 20 from stack.\n");
	stack_pop(test, &popper);
	stack_print(test);
	printf("%f was popped from stack.\n", popper.value);
	
	printf("\n");

	printf("Popping 0 from stack.\n");
	stack_pop(test, &popper);
	stack_print(test);
	printf("%f was popped from stack.\n", popper.value);

	stack_push(test, a);
	stack_push(test, b);
	stack_push(test, c);

	stack_delete(&test);

	return 0;
}
