/**
 * @file q2_circular_queue.c
 * @brief Circular Queue implementation using an Array without built-in libraries.
 * 
 * Operations supported:
 *  - ENQUEUE(x) : Insert element into the queue (handles Queue Overflow)
 *  - DEQUEUE()  : Remove and return the front element (handles Queue Underflow)
 *  - FRONT()    : View front element without removing (handles Queue Underflow)
 *  - DISPLAY()  : Display all elements in circular FIFO order and array buffer layout
 * 
 * Accurately distinguishes between:
 *  - Empty Queue : front == -1
 *  - Full Queue  : (rear + 1) % CAPACITY == front
 */

#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 5  /* Fixed capacity to easily demonstrate wrapping and overflow */

/* Circular Queue Structure */
typedef struct {
    int arr[CAPACITY];
    int front;
    int rear;
} CircularQueue;

/* Function to initialize circular queue */
void initQueue(CircularQueue *q) {
    q->front = -1;
    q->rear = -1;
}

/*
 * Check if the Circular Queue is empty.
 * Returns 1 if empty, 0 otherwise.
 */
int isEmpty(const CircularQueue *q) {
    return q->front == -1;
}

/*
 * Check if the Circular Queue is full.
 * Condition: (rear + 1) % CAPACITY == front
 * Covers both:
 *  1. front == 0 && rear == CAPACITY - 1
 *  2. rear == front - 1 (rear has wrapped around behind front)
 */
int isFull(const CircularQueue *q) {
    return (q->rear + 1) % CAPACITY == q->front;
}

/*
 * ENQUEUE Operation
 * Time Complexity:  O(1)
 * Space Complexity: O(1) auxiliary
 */
int enqueue(CircularQueue *q, int x) {
    if (isFull(q)) {
        printf("\n[ERROR] Queue Overflow! The circular queue is FULL.\n");
        printf("        Cannot enqueue element %d (front = %d, rear = %d, capacity = %d)\n",
               x, q->front, q->rear, CAPACITY);
        return 0; /* Operation failed */
    }

    if (isEmpty(q)) {
        /* First element being inserted */
        q->front = 0;
        q->rear = 0;
    } else {
        /* Circularly advance rear */
        q->rear = (q->rear + 1) % CAPACITY;
    }

    q->arr[q->rear] = x;
    printf("[SUCCESS] Enqueued %d at index %d. (front: %d, rear: %d)\n",
           x, q->rear, q->front, q->rear);
    return 1; /* Operation succeeded */
}

/*
 * DEQUEUE Operation
 * Time Complexity:  O(1)
 * Space Complexity: O(1) auxiliary
 */
int dequeue(CircularQueue *q, int *dequeuedValue) {
    if (isEmpty(q)) {
        printf("\n[ERROR] Queue Underflow! The circular queue is EMPTY. Cannot dequeue.\n");
        return 0; /* Operation failed */
    }

    *dequeuedValue = q->arr[q->front];
    int removedIndex = q->front;

    if (q->front == q->rear) {
        /* Last remaining element was removed; reset to empty state */
        q->front = -1;
        q->rear = -1;
        printf("[SUCCESS] Dequeued %d from index %d. Queue is now EMPTY (front: -1, rear: -1)\n",
               *dequeuedValue, removedIndex);
    } else {
        /* Circularly advance front */
        q->front = (q->front + 1) % CAPACITY;
        printf("[SUCCESS] Dequeued %d from index %d. New front: index %d (rear: %d)\n",
               *dequeuedValue, removedIndex, q->front, q->rear);
    }

    return 1; /* Operation succeeded */
}

/*
 * FRONT Operation
 * Time Complexity:  O(1)
 * Space Complexity: O(1) auxiliary
 */
int getFront(const CircularQueue *q, int *frontValue) {
    if (isEmpty(q)) {
        printf("\n[ERROR] Queue is EMPTY. No front element available.\n");
        return 0; /* Operation failed */
    }

    *frontValue = q->arr[q->front];
    printf("[FRONT] Front element is: %d (at index %d)\n", *frontValue, q->front);
    return 1; /* Operation succeeded */
}

/*
 * DISPLAY Operation
 * Time Complexity:  O(N) where N is number of active elements
 * Space Complexity: O(1) auxiliary
 */
void display(const CircularQueue *q) {
    if (isEmpty(q)) {
        printf("\n[DISPLAY] Circular Queue is EMPTY.\n");
        return;
    }

    printf("\n--- CIRCULAR QUEUE (Logical Order: Front to Rear) ---\n");
    int i = q->front;
    int count = 0;
    while (1) {
        printf(" Position [%d]: %d", i, q->arr[i]);
        if (i == q->front && i == q->rear) {
            printf("  <-- FRONT & REAR\n");
        } else if (i == q->front) {
            printf("  <-- FRONT\n");
        } else if (i == q->rear) {
            printf("  <-- REAR\n");
        } else {
            printf("\n");
        }

        count++;
        if (i == q->rear) {
            break;
        }
        i = (i + 1) % CAPACITY;
    }
    printf("Active Elements: %d / %d\n", count, CAPACITY);

    /* Array buffer visualization */
    printf("\n--- PHYSICAL ARRAY BUFFER VISUALIZATION ---\n[ ");
    for (int idx = 0; idx < CAPACITY; idx++) {
        /* Check if idx is active */
        int isActive = 0;
        if (!isEmpty(q)) {
            if (q->front <= q->rear) {
                if (idx >= q->front && idx <= q->rear) isActive = 1;
            } else {
                if (idx >= q->front || idx <= q->rear) isActive = 1;
            }
        }

        if (isActive) {
            printf("%d ", q->arr[idx]);
        } else {
            printf("- "); /* Unused or freed slot */
        }
    }
    printf("]  (Indices: 0 to %d)\n\n", CAPACITY - 1);
}

/* Interactive Menu-Driven Program */
int main(void) {
    CircularQueue q;
    initQueue(&q);

    int choice, value;

    printf("====================================================\n");
    printf("     CIRCULAR QUEUE IMPLEMENTATION USING ARRAY     \n");
    printf("            (Fixed Capacity: %d Elements)           \n", CAPACITY);
    printf("====================================================\n");

    while (1) {
        printf("\n------------- CIRCULAR QUEUE MENU -------------\n");
        printf(" 1. ENQUEUE(x) - Insert element\n");
        printf(" 2. DEQUEUE()  - Remove front element\n");
        printf(" 3. FRONT()    - View front element\n");
        printf(" 4. DISPLAY()  - Show queue contents & buffer\n");
        printf(" 5. EXIT\n");
        printf("-----------------------------------------------\n");
        printf("Enter your choice (1-5): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Exiting program.\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter integer value to enqueue: ");
                if (scanf("%d", &value) == 1) {
                    enqueue(&q, value);
                } else {
                    printf("Invalid value entered.\n");
                    while (getchar() != '\n'); /* Flush buffer */
                }
                break;

            case 2:
                dequeue(&q, &value);
                break;

            case 3:
                getFront(&q, &value);
                break;

            case 4:
                display(&q);
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
