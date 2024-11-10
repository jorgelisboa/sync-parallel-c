
# Sync-Parallel-C

This repository provides practical examples of synchronization and coordination in parallel programming using C. The examples focus on key concepts like signals, readers-writers, deadlocks, and barriers, which are essential for writing correct and efficient multi-threaded programs.

## Synchronization Concepts in Parallel Programming

### 1. **Signals (Condition Variables)**

A **signal** is used to notify one or more threads that are waiting on a condition variable that they can proceed. Condition variables allow threads to wait for certain conditions before executing further.

**Example**:
- **Thread 1** signals **Thread 2** to proceed after completing some work.
- **Thread 2** waits for the signal from **Thread 1** to continue execution.

```c
pthread_cond_signal(&cond_var);  // Signal
pthread_cond_wait(&cond_var, &lock);  // Wait for signal
```

#### Comparison:
- **Signal vs Mutex**: A **mutex** ensures mutual exclusion, locking a resource for only one thread at a time. A **signal** helps threads coordinate and communicate when to proceed.

---

### 2. **Readers and Writers Problem**

In the **readers-writers** problem, multiple threads can read shared data at the same time, but only one thread (the writer) can modify the data at any moment. This is crucial to avoid data inconsistency.

**Example**:
- **Readers** can access data concurrently.
- **Writers** need exclusive access to modify data.

```c
pthread_mutex_lock(&resource_mutex);  // Writer lock for exclusive access
pthread_mutex_lock(&reader_count_mutex);  // Reader locks before modifying data
```

#### Comparison:
- **Readers-Writers vs Mutexes**: **Readers-writers** synchronization allows multiple readers but ensures exclusive access for writers, whereas a **mutex** generally locks a resource for a single thread at a time.

---

### 3. **Deadlocks**

A **deadlock** occurs when two or more threads are unable to proceed because each is waiting for the other to release resources. This can happen if threads lock resources in an inconsistent order.

**Example**:
- **Thread 1** locks Resource A and waits for Resource B.
- **Thread 2** locks Resource B and waits for Resource A.

```c
pthread_mutex_lock(&resourceA);
pthread_mutex_lock(&resourceB);  // Deadlock if Thread 1 holds A and Thread 2 holds B
```

#### Comparison:
- **Deadlock vs Barrier**: A **deadlock** is an undesirable situation where threads are stuck waiting for each other. A **barrier** is a designed synchronization point where threads wait for all to arrive before continuing.

---

### 4. **Barriers**

A **barrier** is a synchronization primitive that forces threads to wait until all threads have reached the same point in their execution before proceeding further. This is used in parallel algorithms to ensure all threads are synchronized before continuing.

**Example**:
- All threads must reach the barrier before any can proceed.

```c
pthread_barrier_wait(&barrier);  // Waits at the barrier until all threads are ready
```

#### Comparison:
- **Barrier vs Signal**: A **barrier** ensures that all threads wait for each other at a certain point, while a **signal** is a one-way notification to specific threads to proceed.

---

## Summary of Comparisons

| **Concept**        | **Purpose**                                        | **Key Difference**                    |
|--------------------|----------------------------------------------------|---------------------------------------|
| **Signal**         | Notifies waiting threads to proceed                | Used for signaling between threads   |
| **Readers-Writers**| Manages concurrent reading and exclusive writing   | Allows concurrent readers, exclusive writers |
| **Deadlock**       | Prevents threads from being stuck forever          | Caused by improper resource locking  |
| **Barrier**        | Synchronizes threads at a common point             | All threads must reach the barrier before proceeding |

---

## Conclusion

These synchronization techniques are essential for managing multi-threaded environments in parallel programming. By understanding **signals**, **readers-writers**, **deadlocks**, and **barriers**, you can ensure safe, efficient, and deadlock-free parallel programs. This repository aims to demonstrate these concepts through practical C code examples.
