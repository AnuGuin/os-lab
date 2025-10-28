```markdown
# OS Lab (AnuGuin/os-lab)

A collection of operating systems laboratory exercises, projects, and notes created to learn and demonstrate core OS concepts such as processes and threads, synchronization, memory management, scheduling, system calls, and basic kernel concepts.

This README is intended to provide a clear project layout, build/run instructions, and contribution guidance so students and contributors can quickly get started.

## Table of Contents

- [About](#about)
- [Repository structure](#repository-structure)
- [Prerequisites](#prerequisites)
- [Build / Run](#build--run)
- [Common lab tasks](#common-lab-tasks)
- [Testing](#testing)
- [Contributing](#contributing)
- [Academic honesty](#academic-honesty)
- [License](#license)
- [Contact](#contact)

## About

This repository houses lab assignments and example code for operating systems coursework. Each lab is designed to be relatively self-contained and contains its own README with objectives, instructions, and test cases where applicable.

Typical topics covered:
- Processes and threads
- Synchronization (mutexes, semaphores, condition variables)
- Memory management (paging, allocation strategies)
- Scheduling algorithms and performance measurement

Open the individual lab directories for detailed instructions and the expected deliverables.

## Prerequisites

Make sure you have the tools required to build and run the exercises. Common tools:

- gcc / clang (C compiler)
- make
- gdb (debugger)
- valgrind (memory checking, optional)
- nasm / objdump (for assembly / low-level labs)
- qemu-system-x86_64 (for kernel / bootloader experiments)
- Python 3 (for test harnesses / helpers)

Install on Ubuntu/Debian:
sudo apt update
sudo apt install build-essential gdb valgrind qemu-system-x86 nasm python3 python3-pip

Adjust to your OS / package manager as needed.

## Build / Run

There is usually a top-level Makefile and per-lab Makefiles.

Common commands:

- Build everything (if provided)
  make all

- Build a single lab (example for lab01)
  cd labs/lab01-processes
  make

- Clean build artifacts
  make clean

- Run a program
  ./bin/<program> [args]

- Run a kernel/bootable image (if present)
  qemu-system-x86_64 -kernel path/to/kernel -nographic

Read the README.md inside each lab folder for lab-specific build and run instructions.

## Common lab tasks

- Compile C sources:
  gcc -Wall -Wextra -O2 -o bin/myprog src/myprog.c

- Run tests:
  cd labs/labXX
  ./run_tests.sh    # or `make test` if provided

- Use gdb:
  gdb --args ./bin/myprog arg1 arg2

- Check for memory errors:
  valgrind --leak-check=full ./bin/myprog

## Testing

Where provided, test harnesses live in the lab directory (e.g., tests or scripts folders). Use the provided scripts to verify your solution against expected outputs.

If you add tests, follow the repository's naming conventions so CI/test scripts can discover them automatically.

## Academic honesty

This repo is intended for learning. Do not copy other students' solutions or post full solutions publicly if your course policy forbids it. Use this repository as a study aid and a reference for implementing your own solutions.

## License

Unless otherwise noted in individual lab folders, code in this repository is available under the MIT License. Check LICENSE (if present) for details.

## Contact

Owner: AnuGuin — https://github.com/AnuGuin
