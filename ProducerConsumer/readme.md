# Producer-Consumer Problem using Semaphores

This project demonstrates the classic Producer-Consumer problem using semaphores, pthreads, and shared memory in C++.

The producer will generate and place 10 items in the shared buffer with a size of 2 and then enter a wait cycle until a new spot has oppened in the table.
Conversely, the consumer with consume 10 items out of the shared buffer with a size of 2 and enter a wait cycle until a new item has been placed within the table.

The project uses the semaphore library to establish a shared memorey data type. The actual area opened is the semProducer, semConsumer, and the semMutex. These three shared memory locations work together to sycronize the passing of data over the structure created called SharedBuffer which simply creates a data type to hold the virtual table and the index within the table. Both processes start within seperate threads and additionally creates another thread within their own running.

A sleep(1) command is used within the producer to help simulate the time it would take for a real system to generate data that needs to be stored.

## Requirements

- C++ compiler with support for C++11 or higher
- Linux/Unix environment
- Pthread library
- Real-time library

## Compilation

Compile the producer and consumer programs:

```sh
$ g++ producer.cpp -pthread -lrt -o producer
$ g++ consumer.cpp -pthread -lrt -o consumer