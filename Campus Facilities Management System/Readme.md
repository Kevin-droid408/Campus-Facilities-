# Request Processing & Activity Scheduling System

A C++ console application built on **custom implementations** of classic data structures — a circular linked-list queue, a linked-list stack, a binary max-heap priority queue, and a sorted singly linked list. It demonstrates two independent subsystems sharing one interactive menu:

1. **Request Processing** — submit, prioritize, process, and audit support-desk style requests.
2. **Activity Scheduling** — schedule calendar activities with automatic overlap detection.

No STL containers are used for the data structures themselves (only `std::vector` as the heap's backing store, `std::string`, and `<iostream>`), so every algorithmic detail is visible in the source.

---

## Table of Contents

- [Features](#features)
- [Project Structure](#project-structure)
- [Data Structures Used](#data-structures-used)
- [Architecture](#architecture)
- [Building](#building)
- [Running](#running)
- [Usage](#usage)
- [Class Reference](#class-reference)
- [Design Notes & Rules Enforced](#design-notes--rules-enforced)
- [Known Limitations](#known-limitations)
- [Testing](#testing)
- [License](#license)

---

## Features

### Request Processing
- **Two independent intake streams**
  - *Normal* requests → FIFO **circular linked-list queue**
  - *Priority* requests → **binary max-heap** ordered by priority, then by submission order
- **Four priority levels**: `LOW (1)`, `NORMAL (2)`, `HIGH (3)`, `EMERGENCY (4)`
- **Tie-breaking**: equal-priority requests are served in *submission order* (lower ID first)
- **Audit trail**: every processed request is pushed onto a **stack** so the most recent processing can be inspected
- **Status lifecycle**: `PENDING → IN_PROGRESS → COMPLETE`
- Empty-state messages for every operation (no silent failures)

### Activity Scheduling
- **Sorted insertion** by `(date, start time)` — the list stays chronologically ordered
- **Automatic conflict detection** using the half-open interval overlap test: `newStart < existingEnd && newEnd > existingStart`
- **Date normalization**: input like `26-3-7` is stored as `26-03-07` so lexicographic string ordering equals chronological ordering
- **Validation**: rejects `duration <= 0`, out-of-range start times, and activities that end after midnight
- **Human-readable output**: times printed as `HH:MM` with zero padding

---

## Project Structure

---

## Data Structures Used

| Structure | Implementation | Used For |
|-----------|----------------|----------|
| **Queue** | Circular singly linked list (`rear->next == front`) | Normal request intake (FIFO) |
| **Stack** | Singly linked list (`topNode` head pointer) | Processed-request audit trail (LIFO) |
| **Priority Queue** | Binary max-heap on `std::vector<T>` | Priority request intake |
| **Sorted List** | Singly linked list with ordered insert | Activity scheduler |

All four are **templated** (`template <class T>`), so the same code could hold any type — they happen to hold `Request` and `Activity` here.

### Why these choices?

- **Circular queue** gives O(1) enqueue and O(1) dequeue with no wasted "front pointer" sentinel.
- **Linked stack** gives O(1) push/pop with no capacity limit — good for an unbounded audit log.
- **Max-heap** gives O(log n) insert and O(log n) extract-max, which is exactly what "always serve the highest priority" needs.
- **Sorted linked list** keeps activities in chronological order while allowing O(n) insertion (n is small in a personal calendar).

---

## Architecture

The two subsystems are **fully decoupled** — the scheduler never sees a `Request`, and the processor never sees an `Activity`. Only `main.cpp` knows about both.

---

## Building

### Requirements
- A C++11 (or later) compiler: `g++`, `clang++`, or MSVC 2015+
- No external libraries

### Compile the main application

```bash
g++ -std=c++17 -Wall -Wextra -Iinclude main.cpp src/*.cpp -o Program.exe
