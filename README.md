# Prime Number Generator Program

## Overview
This program generates prime numbers using different algorithms and approaches. It supports sequential, parallel, cyclic, and Miller-Rabin primality tests. The program provides a user-friendly menu for the user to select the desired method for prime number generation.

## Features
- **Sequential Prime Generation**: Generates prime numbers sequentially up to a given limit.
- **Parallel Prime Generation**: Uses parallel threads to generate prime numbers, improving performance.
- **Cyclic Prime Generation**: Implements cyclic techniques to generate primes.
- **Miller-Rabin Test**: Uses the Miller-Rabin primality test to generate primes, suitable for large numbers.

## Requirements
- **C Compiler (GCC)**: The program is written in C, so you need GCC or a compatible C compiler to build it.
- **POSIX-compliant System**: The program uses `sleep`, `clock_gettime`, and `pthread` for parallelism, which requires a POSIX-compliant system (Linux, macOS, etc.).

## Installation

1. Clone or download the repository to your local machine.
2. Open a terminal and navigate to the project directory.
3. Ensure that you have the necessary build tools installed (GCC, Make).

```bash
git clone https://github.com/rafailsialakis/Prime-Gen
```

## Compilation

You can compile the program using the provided `Script file` by running the following commands:

```bash
cd Prime-Gen
```
```bash
chmod +x build.sh
```
```bash
./primegenerator
```

