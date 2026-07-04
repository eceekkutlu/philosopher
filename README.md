*This project has been created as part of the 42 curriculum by zkutlu.*

# Philosopher

## Description

Philosopher is a multithreaded C simulation of the classic Dining Philosophers problem.
Its main goal is to coordinate concurrent philosopher routines safely while avoiding deadlocks,
race conditions, starvation, and incorrect death detection.

Each philosopher repeatedly performs three actions:

- takes forks and eats
- sleeps
- thinks

The project demonstrates practical use of POSIX threads and mutexes to protect shared state,
serialize console output, and monitor simulation stop conditions.

## Features

- thread creation and lifecycle management with pthread
- mutex-protected forks
- synchronized shared state access for life/death and meal tracking
- timestamped action logging
- optional simulation stop condition via required meal count
- edge case handling for one philosopher

## Instructions

### Requirements

- Linux or macOS
- C compiler (cc)
- Make
- pthread support

### Compilation

```bash
make
```

This builds the executable named philo.

### Execution

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Argument rules:

- all arguments must be positive integers
- required argument count: 4 numbers after the program name
- optional 5th number sets the minimum meal count for each philosopher

Example:

```bash
./philo 5 800 200 200
./philo 5 800 200 200 7
```

### Useful Make Targets

- make: compile the project
- make clean: remove object files
- make fclean: remove object files and executable
- make re: rebuild from scratch

## Project Structure

```text
philosopher/
├── main.c
├── create_func.c
├── for_died.c
├── utils.c
├── write_func.c
├── philo.h
├── Makefile
└── README.md
```

## Resources

Classic references used for this topic:

- POSIX Threads Programming (LLNL): https://hpc-tutorials.llnl.gov/posix/
- Linux pthread documentation (man pages): https://man7.org/linux/man-pages/man7/pthreads.7.html
- The Dining Philosophers Problem overview: https://en.wikipedia.org/wiki/Dining_philosophers_problem
- The Little Book of Semaphores (Allen B. Downey): https://greenteapress.com/wp/semaphores/

### AI Usage Disclosure

I used AI at the beginning of the project to better understand the thread synchronization structure of the Dining Philosophers problem. During development, I also used it for idea exchange on possible code optimizations, such as lock ordering, timing behavior, and shared-state checks. AI support mainly helped me think through alternatives and improve clarity. The final code and project output were completed by me.
