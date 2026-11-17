# Build Instructions

## Prerequisites

- **CMake 3.16+**
- **C++17 compiler** (GCC 7+, Clang 6+, MSVC 2017+)

## Building

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

## Resulting Binary

```bash
pushk2pre2spc
```
