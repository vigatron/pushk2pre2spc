# PUSHK Archiver: representation-first compression filter `spc` 

[![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://isocpp.org/)
[![CMake](https://img.shields.io/badge/CMake-3.16+-green.svg)](https://cmake.org/)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

**Early-stage diagnostic tool** for the PUSHK Archiver project — a representation-first compression pipeline with the custom `spc` filter. (MIT License)

---

## 📌 What is this?

`pushk2pre2spc` is the second practical utility in the **PUSHK Archiver** series.

It follows the **representation-first** philosophy:

> Before compression, determine exactly which byte values (0–255) are actually used.

This information becomes the foundation for subsequent compression stages:

pushk → pre → spc


Currently, the tool implements only the **representation analysis stage** (`pre`) and outputs a human-readable presence map.

---

## ✨ Features

- Reads any binary file with optional offset and length
- Detects which of the 256 possible byte values are present
- Outputs a **16×16 visual map**
  - `#` = present
  - `.` = absent
- Written in modern **C++17**
- Header-only modules
- Zero external dependencies
- Extremely lightweight and fast

---

## 🛠 Building

```bash
# Clone the repository
git clone https://github.com/vigatron/pushk2pre2spc.git
cd pushk2pre2spc

# Create build directory
mkdir build && cd build

# Configure and build
cmake ..
cmake --build . --config Release

# (Optional) Install system-wide
sudo cmake --install .
```


### 🔧 Resulting Binary

```bash
pushk2pre2spc
````

---

## ▶️ Usage

	pushk2pre2spc <mode> <file> [offset] [length]


### Parameters

| Parameter | Description                               | Default  |
| --------- | ----------------------------------------- | -------- |
| `mode`    | Currently supported: `t` (text map)       | required |
| `file`    | Path to the binary file                   | required |
| `offset`  | Starting byte offset                      | `0`      |
| `length`  | Number of bytes to read (`0` = until EOF) | `0`      |

---

