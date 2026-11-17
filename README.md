# PUSHK Archiver: representation-first compression filter `spc` 

[![Language](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://isocpp.org/)
[![Version](https://img.shields.io/badge/version-0.1.0-blue.svg)](README.md)
[![CMake](https://img.shields.io/badge/CMake-3.16+-green.svg)](https://cmake.org/)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Author](https://img.shields.io/badge/Author-Vigatron-blue.svg)](https://github.com/vigatron)
[![Date](https://img.shields.io/badge/Date-2026-orange.svg)]()

**Early-stage diagnostic tool** for the PUSHK Archiver project — a representation-first compression pipeline with the custom `spc` filter. (MIT License)

---

## Command Line CLI

```bash
pushk2pre2spc <mode> <file> [offset] [length]
```

### Parameters

| Parameter | Description | Default | Options / Details |
| --- | --- | --- | --- |
| ``mode`` | String defining program mode(s).<br>Each character is optional and can be combined. | required | ``i`` — Show input parameters<br/> ``n`` — Binary map<br/> ``t`` — Text map<br/> ``s`` — Size<br/> ``j`` — JSON output<br/>Example: ``"tn"`` → Text + Binary map |
| ``file`` | Path to the binary file | required | Full or relative path must be provided |
| ``offset`` | Starting byte offset | ``0`` | Defines where reading begins;<br> default is start of file |
| ``length`` | Number of bytes to read (``0`` = until EOF) | ``0`` | If > 0, reads only the specified range; <br>if ``0``, reads until end of file |

---

### External Dependencies

This project does not use external libraries or dependencies.

---

## What is this?

`pushk2pre2spc` is the second practical utility in the **PUSHK Archiver** series.

It follows the **representation-first** philosophy:

> Before compression, determine exactly which byte values (0–255) are actually used.

This information becomes the foundation for subsequent compression stages:

pushk → pre → spc


Currently, the tool implements only the **representation analysis stage** (`pre`) and outputs a human-readable presence map.

---

## Features

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

## Building

See [docs/build.md](docs/build.md)

---

**Copyright 2026 V01G04A81**

