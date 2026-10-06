/**
 * @file q1_stack.c
 * @brief Stack implementation using an Array without built-in libraries.
 * 
 * Operations supported:
 *  - PUSH(x)   : Insert element onto the stack (handles Stack Overflow)
 *  - POP()     : Remove and return top element (handles Stack Underflow)
 *  - PEEK()    : View top element without removing (handles Stack Underflow)
 *  - DISPLAY() : Display all elements from top to bottom
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_CAPACITY 5  /* Fixed capacity to easily demonstrate overflow */

/* Stack Structure */
typedef struct {
    int arr[MAX_CAPACITY];
    int top;
} Stack;

/* Function to initialize the stack */
void initStack(Stack *s) {
    s->top = -1;
}

/* Check if stack is full */
int isFull(const Stack *s) {
    return s->top == MAX_CAPACITY - 1;
}

/* Check if stack is empty */
int isEmpty(const Stack *s) {
    return s->top == -1;
}

/*
 * PUSH Operation
 * Time Complexity:  O(1)
 * Space Complexity: O(1) auxiliary
 */
int push(Stack *s, int x) {
    if (isFull(s)) {
        printf("\n[ERROR] Stack Overflow! Capacity (%d) reached. Cannot push element: %d\n", MAX_CAPACITY, x);
        return 0; /* Operation failed */
    }
    s->top++;
    s->arr[s->top] = x;
    printf("[SUCCESS] Pushed %d onto the stack. (Current top index: %d)\n", x, s->top);
    return 1; /* Operation succeeded */
}

/*
 * POP Operation
 * Time Complexity:  O(1)
 * Space Complexity: O(1) auxiliary
 */
int pop(Stack *s, int *poppedValue) {
    if (isEmpty(s)) {
        printf("\n[ERROR] Stack Underflow! Stack is empty. Cannot pop element.\n");
        return 0; /* Operation failed */
    }
    *poppedValue = s->arr[s->top];
    s->top--;
    printf("[SUCCESS] Popped %d from the stack. (New top index: %d)\n", *poppedValue, s->top);
    return 1; /* Operation succeeded */
}

/*
 * PEEK Operation
 * Time Complexity:  O(1)
 * Space Complexity: O(1) auxiliary
 */
int peek(const Stack *s, int *peekValue) {
    if (isEmpty(s)) {
        printf("\n[ERROR] Stack Underflow! Stack is empty. No top element to peek.\n");
        return 0; /* Operation failed */
    }
    *peekValue = s->arr[s->top];
    printf("[PEEK] Top element is: %d (at index %d)\n", *peekValue, s->top);
    return 1; /* Operation succeeded */
}

/*
 * DISPLAY Operation
 * Time Complexity:  O(N) where N is current number of elements
 * Space Complexity: O(1) auxiliary
 */
void display(const Stack *s) {
    if (isEmpty(s)) {
        printf("\n[DISPLAY] Stack is currently EMPTY.\n");
        return;
    }

    printf("\n--- CURRENT STACK (Top to Bottom) ---\n");
    for (int i = s->top; i >= 0; i--) {
        if (i == s->top) {
            printf(" | %4d | <-- TOP (index %d)\n", s->arr[i], i);
        } else {
            printf(" | %4d |     (index %d)\n", s->arr[i], i);
        }
    }
    printf(" ---------\n");
    printf("Total Elements: %d / %d\n\n", s->top + 1, MAX_CAPACITY);
}

/* Interactive Menu-Driven Program */
int main(void) {
    Stack s;
    initStack(&s);

    int choice, value;

    printf("====================================================\n");
    printf("         STACK IMPLEMENTATION USING ARRAY           \n");
    printf("           (Fixed Capacity: %d Elements)            \n", MAX_CAPACITY);
    printf("====================================================\n");

    while (1) {
        printf("\n---------------- STACK MENU ----------------\n");
        printf(" 1. PUSH(x)   - Insert element\n");
        printf(" 2. POP()     - Remove top element\n");
        printf(" 3. PEEK()    - View top element\n");
        printf(" 4. DISPLAY() - Show all elements\n");
        printf(" 5. EXIT\n");
        printf("--------------------------------------------\n");
        printf("Enter your choice (1-5): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Exiting program.\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter integer value to push: ");
                if (scanf("%d", &value) == 1) {
                    push(&s, value);
                } else {
                    printf("Invalid value entered.\n");
                    while (getchar() != '\n'); /* Flush buffer */
                }
                break;

            case 2:
                pop(&s, &value);
                break;

            case 3:
                peek(&s, &value);
                break;

            case 4:
                display(&s);
                break;

            case 5:
                printf("\nExiting program. Thank you!\n");
                exit(0);

            default:
                printf("Invalid choice! Please select an option between 1 and 5.\n");
        }
    }

    return 0;
}
