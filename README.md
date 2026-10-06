# Data Structures and Algorithms Assignment: Stack & Circular Queue

This repository contains the complete C implementations and theoretical analyses for:
1. **Question 1**: Array-based Stack implementation with Overflow/Underflow handling.
2. **Question 2**: Array-based Circular Queue implementation with full/empty queue disambiguation.

---

## Table of Contents
- [Q1: Stack Implementation & Analysis](#q1-stack-implementation--analysis)
  - [Overview & Operations](#q1-overview--operations)
  - [Complexity Analysis](#q1-complexity-analysis)
  - [Fixed Stack Size & Capacity Overflow Analysis](#fixed-stack-size--capacity-overflow-analysis)
- [Q2: Circular Queue Implementation & Analysis](#q2-circular-queue-implementation--analysis)
  - [Overview & Operations](#q2-overview--operations)
  - [Distinguishing Full vs. Empty Queue](#distinguishing-full-vs-empty-queue)
  - [Comparison: Circular Queue vs. Linear Queue](#comparison-circular-queue-vs-linear-queue)
  - [1. Memory Utilization](#1-memory-utilization)
  - [2. Time Complexity](#2-time-complexity)
  - [3. Space Complexity](#3-space-complexity)
  - [4. The Linear Queue Problem (False Overflow)](#4-the-linear-queue-problem-false-overflow)
- [Compilation & Execution Guide](#compilation--execution-guide)

---

## Q1: Stack Implementation & Analysis

### Q1 Overview & Operations
A **Stack** is a linear data structure that operates under the **LIFO (Last In, First Out)** principle. The implementation in [`q1_stack.c`](q1_stack.c) provides:
- **`PUSH(x)`**: Adds an integer `x` to the top of the stack after verifying that `top < MAX_CAPACITY - 1`. If full, reports **Stack Overflow**.
- **`POP()`**: Removes and returns the element at the top after verifying `top != -1`. If empty, reports **Stack Underflow**.
- **`PEEK()`**: Retrieves the value of the top element without removing it.
- **`DISPLAY()`**: Traverses from `top` down to index `0` and displays elements along with their indices.

### Q1 Complexity Analysis

| Operation | Time Complexity | Auxiliary Space Complexity | Explanation |
| :--- | :---: | :---: | :--- |
| **`PUSH(x)`** | **$\mathcal{O}(1)$** | **$\mathcal{O}(1)$** | Direct index access (`arr[++top] = x`). No loops or shifts. |
| **`POP()`** | **$\mathcal{O}(1)$** | **$\mathcal{O}(1)$** | Decrements top pointer (`x = arr[top--]`). Constant time. |
| **`PEEK()`** | **$\mathcal{O}(1)$** | **$\mathcal{O}(1)$** | Direct read of `arr[top]` without modifying the pointer. |
| **`DISPLAY()`** | **$\mathcal{O}(n)$** | **$\mathcal{O}(1)$** | Traverses all $n$ active elements currently in the stack. |

- **Total Space Complexity**: **$\mathcal{O}(N)$**, where $N$ is the maximum fixed capacity (`MAX_CAPACITY`) allocated in contiguous memory.

---

### Fixed Stack Size & Capacity Overflow Analysis

When a stack has a fixed size ($N$) and a user attempts to insert an element when the stack is already full (`top == N - 1`):

1. **Stack Overflow Condition**:
   - The stack cannot accommodate any additional elements because all pre-allocated slots are occupied.
   - Without defensive bounds-checking, attempting to write at `arr[top + 1]` results in **Out-of-Bounds Memory Write (Buffer Overflow)**.
2. **Consequences of Unchecked Overflow in C**:
   - **Memory Corruption**: Overwrites adjacent variables or call stack memory.
   - **Undefined Behavior / Crashes**: Can trigger `Segmentation Fault` or abnormal termination.
   - **Security Vulnerabilities**: In systems programming, unchecked stack overflows can lead to exploitable security vulnerabilities (e.g., return address overwriting).
3. **Defensive Handling (Implemented in this project)**:
   - The program performs an upfront condition check (`isFull()`). If `top == MAX_CAPACITY - 1`, the insertion is gracefully rejected, an informative error message is displayed, and the existing stack state is preserved intact.
4. **Alternative Solutions in Production**:
   - **Dynamic Resizing**: When full, reallocate the underlying array with doubled capacity using `realloc()` (amortized $\mathcal{O}(1)$ insertion time).
   - **Linked List Stack**: Uses dynamic node allocation on the heap, bounded only by available system RAM.

---

## Q2: Circular Queue Implementation & Analysis

### Q2 Overview & Operations
A **Queue** is a linear data structure operating under the **FIFO (First In, First Out)** principle. A **Circular Queue** connects the last position of the array back to the first position in a ring-like structure using modulo arithmetic.

Operations in [`q2_circular_queue.c`](q2_circular_queue.c):
- **`ENQUEUE(x)`**: Inserts `x` at `(rear + 1) % CAPACITY`.
- **`DEQUEUE()`**: Removes the element at `front` and advances `front = (front + 1) % CAPACITY`.
- **`FRONT()`**: Reads the current front element.
- **`DISPLAY()`**: Displays the active elements in logical order and shows the physical buffer array.

---

### Distinguishing Full vs. Empty Queue

A classical challenge in circular queues is disambiguating whether the queue is completely empty or completely full, because in both states `front` and `rear` can point to the same relative position.

In our implementation:
- **Initial State / Empty Condition**:
  $$\text{isEmpty} \iff \text{front} == -1$$
  When the last remaining element is dequeued (`front == rear`), the pointers are reset back to `-1` (`front = -1, rear = -1`).
- **Full Condition**:
  $$\text{isFull} \iff (\text{rear} + 1) \pmod{\text{CAPACITY}} == \text{front}$$
  This condition correctly handles:
  1. `front == 0` and `rear == CAPACITY - 1` (queue filled from start to end).
  2. `rear == front - 1` (rear has wrapped around and arrived directly behind `front`).

---

### Comparison: Circular Queue vs. Linear Queue

| Parameter | Linear Queue (Simple Array) | Circular Queue (Array) |
| :--- | :--- | :--- |
| **Memory Utilization** | **Poor**: Once `rear` hits the last index, spaces vacated by `dequeue()` are wasted. | **Optimal**: Vacated spaces at the beginning are reused via modulo wrapping. |
| **False Overflow** | Suffers from false overflow frequently. | Completely eliminates false overflow. |
| **Pointer Reset** | Requires shifting elements ($\mathcal{O}(n)$) or resetting only when completely empty. | Automatically resets when empty; wraps pointers in $\mathcal{O}(1)$. |
| **Index Math** | Linear progression (`rear++`, `front++`). | Modular arithmetic (`(index + 1) % SIZE`). |

---

### 1. Why a Circular Queue Provides Better Utilization of Memory
In a simple linear queue, elements are deleted from `front` and inserted at `rear`. Once `rear` reaches `CAPACITY - 1`, no new elements can be enqueued, even if multiple elements have been dequeued from `front`. Those memory cells remain unreachable and wasted.

A circular queue solves this by treating the array as a logical ring:
$$\text{next\_index} = (\text{current\_index} + 1) \pmod{\text{CAPACITY}}$$
When `rear` reaches the end of the array, it automatically wraps around to index `0` (provided index `0` was freed by a previous dequeue). Every allocated memory byte is utilized up to 100% capacity before reporting an overflow.

---

### 2. Time Complexity of ENQUEUE and DEQUEUE

- **`ENQUEUE(x)`**: **$\mathcal{O}(1)$**
  - Checking `isFull()` is a single arithmetic check.
  - Advancing `rear` via `(rear + 1) % CAPACITY` is constant time.
  - Storing `arr[rear] = x` is an $\mathcal{O}(1)$ array assignment.
- **`DEQUEUE()`**: **$\mathcal{O}(1)$**
  - Checking `isEmpty()` is a single comparison.
  - Retrieving `arr[front]` is an $\mathcal{O}(1)$ read.
  - Advancing `front` via `(front + 1) % CAPACITY` is constant time.

Neither operation requires shifting any elements.

---

### 3. Space Complexity of the Queue

- **Auxiliary Space Complexity**: **$\mathcal{O}(1)$**
  - Operations modify only index variables (`front`, `rear`, `x`) without allocating dynamic memory during run time.
- **Total Space Complexity**: **$\mathcal{O}(N)$**
  - Where $N$ is the fixed array capacity (`CAPACITY`). Contiguous space of $N \times \text{sizeof(int)}$ is allocated upfront.

---

### 4. What Problem Occurs in a Linear Queue When REAR Reaches the Last Index?

This problem is known as **"False Overflow" (or Phantom Overflow / Premature Overflow)**:

#### Scenario:
Consider a linear queue with `CAPACITY = 5`:
1. Insert 5 elements: `[10, 20, 30, 40, 50]`. Now `front = 0`, `rear = 4`.
2. Dequeue 3 elements: `10`, `20`, `30` are removed. Now `front = 3`, `rear = 4`.
3. Indices `0`, `1`, and `2` are now completely free and empty.
4. The user attempts to enqueue a new element `60`.

#### The Failure:
- In a linear queue, the overflow condition is simply:
  $$\text{rear} == \text{CAPACITY} - 1$$
- Since `rear == 4`, the linear queue declares **"Queue Overflow"**, even though **3 out of 5 slots (60% of total memory) are completely empty!**

#### Consequences in Linear Queue:
- **Artificial rejection of valid requests**: System refuses incoming data despite plenty of available storage.
- **Expensive workarounds**:
  - Shifting all remaining elements left upon each dequeue ($\mathcal{O}(n)$ per dequeue, degrading performance).
  - Shifting elements only when `rear == CAPACITY - 1` (intermittent $\mathcal{O}(n)$ latency spikes).

#### The Circular Queue Resolution:
The circular queue eliminates this entirely: when `rear` reaches index 4, `(4 + 1) % 5 = 0`. It checks if index `0` is free (`0 != front`). Since `front = 3`, index `0` is available, and `60` is placed into index `0` in **$\mathcal{O}(1)$** time.

---

## Compilation & Execution Guide

### Requirements
- GCC or any standard C compiler (MinGW, Clang).

### 1. Compile and Run Stack (Q1)
```bash
gcc q1_stack.c -o q1_stack
```
**Run on Windows:**
```powershell
.\q1_stack.exe
```
**Run on Linux / macOS:**
```bash
./q1_stack
```

### 2. Compile and Run Circular Queue (Q2)
```bash
gcc q2_circular_queue.c -o q2_circular_queue
```
**Run on Windows:**
```powershell
.\q2_circular_queue.exe
```
**Run on Linux / macOS:**
```bash
./q2_circular_queue
```
