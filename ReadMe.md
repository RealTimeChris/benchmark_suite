# Benchmark Suite

Hello and welcome to bnch_swt or "Benchmark Suite". This is a collection of classes/functions for the purpose of benchmarking CPU and GPU performance.

The following operating systems and compilers are officially supported:

### Compiler Support
----
![MSVC](https://img.shields.io/github/actions/workflow/status/RealTimeChris/benchmarksuite/benchmark.yml?style=plastic&logo=microsoft&logoColor=green&label=MSVC&labelColor=pewter&color=blue&branch=main)
![GCC](https://img.shields.io/github/actions/workflow/status/RealTimeChris/benchmarksuite/benchmark.yml?style=plastic&logo=linux&logoColor=green&label=GCC&labelColor=pewter&color=blue&branch=main)
![CLANG](https://img.shields.io/github/actions/workflow/status/RealTimeChris/benchmarksuite/benchmark.yml?style=plastic&logo=apple&logoColor=green&label=CLANG&labelColor=pewter&color=blue&branch=main)
![NVCC](https://img.shields.io/badge/NVCC-Supported-blue?style=plastic&logo=nvidia&logoColor=green&labelColor=pewter)

### Operating System Support
----
![Windows](https://img.shields.io/github/actions/workflow/status/RealTimeChris/benchmarksuite/benchmark.yml?style=plastic&logo=microsoft&logoColor=green&label=Windows&labelColor=pewter&color=blue&branch=main)
![Linux](https://img.shields.io/github/actions/workflow/status/RealTimeChris/benchmarksuite/benchmark.yml?style=plastic&logo=linux&logoColor=green&label=Linux&labelColor=pewter&color=blue&branch=main)
![Mac](https://img.shields.io/github/actions/workflow/status/RealTimeChris/benchmarksuite/benchmark.yml?style=plastic&logo=apple&logoColor=green&label=MacOS&labelColor=pewter&color=blue&branch=main)

# Quickstart Guide for benchmarksuite

This guide will walk you through setting up and running benchmarks using `benchmarksuite`.

## Table of Contents
- [Installation](#installation)
  - [Method 1: vcpkg + CMake (Recommended)](#method-1-vcpkg--cmake-recommended)
  - [Method 2: Manual Installation](#method-2-manual-installation)
  - [Requirements](#requirements)
- [Basic Example](#basic-example)
- [Creating Benchmarks](#creating-benchmarks)
- [CPU vs GPU Benchmarking](#cpu-vs-gpu-benchmarking)
- [Running Benchmarks](#running-benchmarks)
  - [Common CMake Options](#common-cmake-options)
  - [Complete Project Example](#complete-project-example)
- [Output and Results](#output-and-results)
- [Features](#features)
- [API Conventions](#api-conventions)
- [Migrating from Pre-1.0.0](#migrating-from-pre-100)

## Installation

### Method 1: vcpkg + CMake (Recommended)

**Step 1: Add to vcpkg.json**

Create or update your `vcpkg.json` in your project root:

```json
{
  "name": "your-project-name",
  "version": "1.0.0",
  "dependencies": [
    "benchmarksuite"
  ]
}
```

**Step 2: Configure CMake**

In your `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.20)
project(YourProject LANGUAGES CXX CUDA)  # Add CUDA if using GPU benchmarks

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# For CUDA support (optional)
set(CMAKE_CUDA_STANDARD 20)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)

# Find the package
find_package(benchmarksuite CONFIG REQUIRED)

# Create your executable
add_executable(your_benchmark main.cpp)

# Link against benchmarksuite (header-only, just sets up includes)
target_link_libraries(your_benchmark PRIVATE benchmarksuite::benchmarksuite)

# If using CUDA
set_target_properties(your_benchmark PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
```

**Step 3: Configure with vcpkg toolchain**

```bash
# Configure
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=[path-to-vcpkg]/scripts/buildsystems/vcpkg.cmake

# Build
cmake --build build --config Release
```

**Step 4: Include in your code**

```cpp
#include <bnch_swt/index.hpp>

int main() {
    // Your benchmarks here
    return 0;
}
```

### Method 2: Manual Installation

If not using vcpkg, you can include benchmarksuite as a header-only library:

**Step 1: Clone the repository**

```bash
git clone https://github.com/RealTimeChris/benchmarksuite.git
```

**Step 2: Add to CMake**

```cmake
# Add as subdirectory
add_subdirectory(path/to/benchmarksuite)

# Or set include directory
target_include_directories(your_target PRIVATE path/to/benchmarksuite/include)
```

**Step 3: Include headers**

```cpp
#include <bnch_swt/index.hpp>
```

### Requirements

To use `benchmarksuite`, ensure you have a C++23 (or later) compliant compiler.

**For CPU Benchmarking:**
- MSVC 2022 or later
- GCC 13 or later  
- Clang 16 or later

**For GPU/CUDA Benchmarking:**
- NVIDIA CUDA Toolkit 11.0 or later
- NVCC compiler
- CUDA-capable GPU

### Platform-Specific Notes

**Windows:**
- Use Visual Studio 2022 or later
- For CUDA: Install CUDA Toolkit from NVIDIA

**Linux:**
- Install build essentials: `sudo apt-get install build-essential`
- For CUDA: Install CUDA Toolkit via package manager or NVIDIA installer

**macOS:**
- Install Xcode Command Line Tools
- CUDA support not available on Apple Silicon (M1/M2/M3)

### Verification

Verify your installation with a simple test:

```cpp
#include <bnch_swt/index.hpp>
#include <iostream>

int main() {
    std::cout << "benchmarksuite successfully installed!" << std::endl;
    return 0;
}
```

## Basic Example
The following example demonstrates how to set up and run a benchmark comparing two integer-to-string conversion functions:

```cpp
// Define benchmark functions as structs with static impl() methods
struct glz_to_chars_benchmark {
    BNCH_SWT_HOST static uint64_t impl(std::vector<int64_t>& test_values, 
                                        std::vector<std::string>& test_values_00,
                                        std::vector<std::string>& test_values_01) {
        uint64_t bytes_processed = 0;
        char newer_string[30]{};
        for (uint64_t x = 0; x < test_values.size(); ++x) {
            std::memset(newer_string, '\0', sizeof(newer_string));
            auto new_ptr = glz::to_chars(newer_string, test_values[x]);
            bytes_processed += test_values_00[x].size();
            test_values_01[x] = std::string{newer_string, static_cast<uint64_t>(new_ptr - newer_string)};
        }
        return bytes_processed;
    }
};

struct jsonifier_to_chars_benchmark {
    BNCH_SWT_HOST static uint64_t impl(std::vector<int64_t>& test_values,
                                        std::vector<std::string>& test_values_00,
                                        std::vector<std::string>& test_values_01) {
        uint64_t bytes_processed = 0;
        char newer_string[30]{};
        for (uint64_t x = 0; x < test_values.size(); ++x) {
            std::memset(newer_string, '\0', sizeof(newer_string));
            auto new_ptr = jsonifier_internal::to_chars(newer_string, test_values[x]);
            bytes_processed += test_values_00[x].size();
            test_values_01[x] = std::string{newer_string, static_cast<uint64_t>(new_ptr - newer_string)};
        }
        return bytes_processed;
    }
};

int main() {
    constexpr uint64_t count = 512;
    
    // Setup test data
    std::vector<int64_t> test_values = generate_random_integers<int64_t>(count, 20);
    std::vector<std::string> test_values_00;
    std::vector<std::string> test_values_01(count);
    
    for (uint64_t x = 0; x < count; ++x) {
        test_values_00.emplace_back(std::to_string(test_values[x]));
    }
    
    // Define benchmark stage with 200 total iterations, 25 measured, CPU benchmarking
    using benchmark = bnch_swt::benchmark_stage<"int-to-string-comparison", 200, 25, 
                                                 bnch_swt::benchmark_types::cpu>;
    
    // Run benchmarks
    benchmark::run_benchmark<"glz::to_chars", glz_to_chars_benchmark>(test_values, test_values_00, test_values_01);
    benchmark::run_benchmark<"jsonifier::to_chars", jsonifier_to_chars_benchmark>(test_values, test_values_00, test_values_01);
    
    // Print results with comparison
    benchmark::print_results(true, true);
    
    return 0;
}
```

## Creating Benchmarks
To create a benchmark:
1. Define your benchmark functions as structs with a static `impl()` method that returns `uint64_t` (bytes processed)
2. Use `bnch_swt::benchmark_stage` with appropriate template parameters
3. Call `run_benchmark` with your benchmark struct and any required arguments

### Benchmark Stage
The `benchmark_stage` structure orchestrates each test and supports both CPU and GPU benchmarking:

```cpp
// Full template signature
template<bnch_swt::string_literal stage_name,              // Required: benchmark stage name
         uint64_t max_execution_count = 200,               // Total iterations (warmup + measured)
         uint64_t measured_iteration_count = 25,           // Iterations to measure
         bnch_swt::benchmark_types benchmark_type = bnch_swt::benchmark_types::cpu,  // CPU or CUDA
         bool clear_cpu_cache_between_each_iteration = false,  // Cache clearing flag
         bnch_swt::string_literal metric_name = bnch_swt::string_literal<1>{}  // Custom metric name
>
struct benchmark_stage;

// Common usage examples
using cpu_benchmark = bnch_swt::benchmark_stage<"my-benchmark">;  // Uses defaults: 200 total, 25 measured, CPU
using gpu_benchmark = bnch_swt::benchmark_stage<"gpu-test", 100, 10, bnch_swt::benchmark_types::cuda>;
using custom_metric = bnch_swt::benchmark_stage<"compression", 200, 25, bnch_swt::benchmark_types::cpu, false, "compression-ratio">;
```

### Template Parameters
- **stage_name** (required): String literal identifying the benchmark stage
- **max_execution_count** (default 200): Total number of iterations including warmup
- **measured_iteration_count** (default 25): Number of iterations to measure for final metrics
- **benchmark_type** (default cpu): `bnch_swt::benchmark_types::cpu` or `bnch_swt::benchmark_types::cuda`
- **clear_cpu_cache_between_each_iteration** (default false): Whether to clear CPU caches between iterations
- **metric_name** (default empty): Custom metric name for specialized benchmarks (e.g., compression ratios)

### Methods
- `run_benchmark<name, function_type>(args...)`: Executes the benchmark function's `impl()` method with the provided arguments
  - **name**: String literal identifying this specific benchmark within the stage
  - **function_type**: Struct type with a static `impl()` method
  - **For CPU**: `run_benchmark<name, function_type>(args...)` where args are forwarded to `impl()`
  - **For CUDA**: `run_benchmark<name, function_type>(grid, block, shared_mem, bytes_processed, args...)` where:
    - `grid`: dim3 specifying grid dimensions
    - `block`: dim3 specifying block dimensions  
    - `shared_mem`: uint64_t bytes of shared memory
    - `bytes_processed`: uint64_t bytes processed for throughput calculation
    - `args...`: Additional arguments forwarded to kernel `impl()`
  - Returns: `performance_metrics<benchmark_type>` object
  
- `print_results(show_comparison = true, show_metrics = true)`: Displays performance metrics and comparisons
  - **show_comparison**: Whether to show head-to-head comparisons between benchmarks
  - **show_metrics**: Whether to show detailed hardware counter metrics

- `get_results()`: Returns a sorted vector of all `performance_metrics` for programmatic access

### Benchmark Function Requirements
Benchmark functions must be defined as structs with a static `impl()` method:

**For CPU benchmarks:**
```cpp
struct my_cpu_benchmark {
    BNCH_SWT_HOST static uint64_t impl(/* your parameters */) {
        // Your CPU code to benchmark
        uint64_t bytes_processed = /* calculate bytes */;
        return bytes_processed;  // Must return bytes processed
    }
};
```

**For CUDA benchmarks:**
```cpp
struct my_cuda_benchmark {
    BNCH_SWT_DEVICE static void impl(/* your parameters */) {
        // Your CUDA kernel code (runs on device)
        // This code will be wrapped in a kernel launch by the framework
        int idx = blockIdx.x * blockDim.x + threadIdx.x;
        // ... your kernel logic
    }
};
```

**Key differences:**
- **CPU**: `impl()` returns `uint64_t` (bytes processed) and uses `BNCH_SWT_HOST`
- **CUDA**: `impl()` returns `void`, uses `BNCH_SWT_DEVICE`, and contains kernel code (not a kernel launch)
- **CUDA**: Bytes processed is passed as a parameter to `run_benchmark()`, not returned from `impl()`
- **CUDA**: The framework automatically wraps your `impl()` in a kernel launch with the specified grid/block dimensions

## CPU vs GPU Benchmarking

As of v1.0.0, benchmarksuite supports both CPU and GPU (CUDA) benchmarking through the `benchmark_types` enum.

### CPU Benchmarks
```cpp
// Define CPU benchmark function
struct cpu_computation_benchmark {
    BNCH_SWT_HOST static uint64_t impl(const std::vector<float>& input, std::vector<float>& output) {
        // Your CPU computation here
        for (size_t i = 0; i < input.size(); ++i) {
            output[i] = std::sqrt(input[i] * input[i] + 1.0f);
        }
        // Return bytes processed for throughput calculation
        return input.size() * sizeof(float);
    }
};

// Create CPU benchmark stage (200 total iterations, 25 measured, CPU type)
using cpu_stage = bnch_swt::benchmark_stage<"cpu-test", 200, 25, bnch_swt::benchmark_types::cpu>;

// Setup data
constexpr size_t data_size = 1024 * 1024;
std::vector<float> input(data_size, 1.0f);
std::vector<float> output(data_size);

// Run the benchmark
cpu_stage::run_benchmark<"my-cpu-function", cpu_computation_benchmark>(input, output);

// Print results
cpu_stage::print_results();
```

### GPU/CUDA Benchmarks
```cpp
// Define CUDA kernel benchmark
struct cuda_kernel_benchmark {
    BNCH_SWT_DEVICE static void impl(float* data, uint64_t size) {
        // Your CUDA kernel code here
        // This runs inside the kernel, NOT as a kernel launch
        int idx = blockIdx.x * blockDim.x + threadIdx.x;
        if (idx < size) {
            data[idx] = data[idx] * 2.0f;  // Example operation
        }
    }
};

// Create CUDA benchmark stage
using cuda_stage = bnch_swt::benchmark_stage<"gpu-test", 100, 10, bnch_swt::benchmark_types::cuda>;

// Setup
constexpr uint64_t data_size = 1024 * 1024;
float* gpu_data;
cudaMalloc(&gpu_data, data_size * sizeof(float));

// Configure kernel launch parameters
dim3 grid{256, 1, 1};
dim3 block{256, 1, 1};
uint64_t shared_memory = 0;
uint64_t bytes_processed = data_size * sizeof(float);

// Run CUDA benchmark
// Parameters: grid, block, shared_mem, bytes_processed, then your kernel args
cuda_stage::run_benchmark<"my-cuda-kernel", cuda_kernel_benchmark>(
    grid, block, shared_memory, bytes_processed, 
    gpu_data, data_size
);

cuda_stage::print_results();
cudaFree(gpu_data);
```

**Important**: For CUDA benchmarks, the `impl()` method contains the kernel code itself (not a kernel launch). The benchmarking framework wraps it in a kernel launch using the provided grid/block dimensions.

### Mixed CPU/GPU Benchmarking
You can benchmark CPU and GPU implementations side-by-side:

```cpp
constexpr uint64_t data_size = 1024 * 1024;

// CPU benchmark function
struct cpu_process_benchmark {
    BNCH_SWT_HOST static uint64_t impl(std::vector<float>& cpu_data) {
        // Process data on CPU
        for (size_t i = 0; i < cpu_data.size(); ++i) {
            cpu_data[i] = cpu_data[i] * 2.0f;
        }
        return cpu_data.size() * sizeof(float);
    }
};

// GPU benchmark function (kernel code, NOT kernel launch)
struct gpu_process_benchmark {
    BNCH_SWT_DEVICE static void impl(float* gpu_data, uint64_t size) {
        int idx = blockIdx.x * blockDim.x + threadIdx.x;
        if (idx < size) {
            gpu_data[idx] = gpu_data[idx] * 2.0f;
        }
    }
};

// Setup test data
std::vector<float> cpu_data(data_size);
float* gpu_data;
cudaMalloc(&gpu_data, data_size * sizeof(float));

// CPU version
using cpu_test = bnch_swt::benchmark_stage<"cpu-vs-gpu", 100, 10, bnch_swt::benchmark_types::cpu>;
cpu_test::run_benchmark<"cpu-version", cpu_process_benchmark>(cpu_data);

// GPU version  
using gpu_test = bnch_swt::benchmark_stage<"cpu-vs-gpu", 100, 10, bnch_swt::benchmark_types::cuda>;
dim3 grid{(data_size + 255) / 256, 1, 1};
dim3 block{256, 1, 1};
gpu_test::run_benchmark<"gpu-version", gpu_process_benchmark>(
    grid, block, 0, data_size * sizeof(float),
    gpu_data, data_size
);

// Print both results for comparison
cpu_test::print_results();
gpu_test::print_results();

cudaFree(gpu_data);
```

This allows direct performance comparison between CPU and GPU implementations of the same algorithm.

### Cache Clearing Option
For more accurate CPU benchmarks, you can enable cache clearing between iterations:

```cpp
// Enable cache clearing (5th template parameter)
using cache_cleared = bnch_swt::benchmark_stage<"cache-test", 200, 25, bnch_swt::benchmark_types::cpu, true>;
```

This is useful when benchmarking memory-bound operations where you want to measure cold cache performance.

### Custom Metrics
You can specify custom metric names for specialized benchmarks that don't measure traditional throughput:

```cpp
// Compression benchmark with custom metric name
using compression_bench = bnch_swt::benchmark_stage<"compression-test", 200, 25, 
                                                     bnch_swt::benchmark_types::cpu, 
                                                     false, 
                                                     "compression-ratio">;

struct compress_benchmark {
    BNCH_SWT_HOST static uint64_t impl(const std::vector<uint8_t>& input) {
        auto compressed = compress_data(input);
        // Return custom metric value (e.g., compression ratio * 1000)
        return (input.size() * 1000) / compressed.size();
    }
};

compression_bench::run_benchmark<"my-compressor", compress_benchmark>(input_data);
compression_bench::print_results();
```

When a custom metric name is provided, the results will display your custom metric instead of standard MB/s throughput.

## Running Benchmarks

**With vcpkg + CMake (recommended):**

```bash
# Configure with vcpkg toolchain
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=[path-to-vcpkg]/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release

# Build
cmake --build build --config Release

# Run
./build/your_benchmark  # Linux/macOS
.\build\Release\your_benchmark.exe  # Windows
```

**Manual CMake build:**

```bash
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
./build/your_benchmark
```

**For CUDA benchmarks, ensure CUDA is enabled:**

```bash
cmake -B build -S . \
  -DCMAKE_TOOLCHAIN_FILE=[path-to-vcpkg]/scripts/buildsystems/vcpkg.cmake \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_CUDA_ARCHITECTURES=86  # Adjust for your GPU architecture
  
cmake --build build --config Release
```

### Common CMake Options

- `-DCMAKE_BUILD_TYPE=Release` - Build optimized release version
- `-DCMAKE_CUDA_ARCHITECTURES=86` - Target specific CUDA compute capability (e.g., 86 for RTX 30xx/40xx)
- `-DCMAKE_CXX_COMPILER=clang++` - Specify C++ compiler
- `-DCMAKE_CUDA_COMPILER=nvcc` - Specify CUDA compiler

### Complete Project Example

**Project structure:**
```
my-benchmark/
├── CMakeLists.txt
├── vcpkg.json
├── main.cpp
└── benchmarks/
    ├── cpu_benchmark.hpp
    └── gpu_benchmark.cuh
```

**CMakeLists.txt:**
```cmake
cmake_minimum_required(VERSION 3.20)
project(MyBenchmark LANGUAGES CXX CUDA)

# C++23 required
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# CUDA 20 for GPU benchmarks
set(CMAKE_CUDA_STANDARD 20)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)

# Find benchmarksuite
find_package(benchmarksuite CONFIG REQUIRED)

# Create executable
add_executable(my_benchmark 
    main.cpp
    benchmarks/cpu_benchmark.hpp
    benchmarks/gpu_benchmark.cuh
)

# Link benchmarksuite
target_link_libraries(my_benchmark PRIVATE 
    benchmarksuite::benchmarksuite
)

# CUDA properties
set_target_properties(my_benchmark PROPERTIES
    CUDA_SEPARABLE_COMPILATION ON
    CUDA_RESOLVE_DEVICE_SYMBOLS ON
)

# Optimization flags
if(MSVC)
    target_compile_options(my_benchmark PRIVATE /O2 /arch:AVX2)
else()
    target_compile_options(my_benchmark PRIVATE -O3 -march=native)
endif()
```

**vcpkg.json:**
```json
{
  "name": "my-benchmark",
  "version": "1.0.0",
  "dependencies": [
    "benchmarksuite"
  ]
}
```

## Output and Results
```
Performance Metrics for: int-to-string-comparisons-1
Metrics for: benchmarksuite::internal::to_chars
Total Iterations to Stabilize                               : 394
Measured Iterations                                         : 20
Bytes Processed                                             : 512.00
Nanoseconds per Execution                                   : 5785.25
Frequency (GHz)                                             : 4.83
Throughput (MB/s)                                           : 84.58
Throughput Percentage Deviation (+/-%)                      : 8.36
Cycles per Execution                                        : 27921.20
Cycles per Byte                                             : 54.53
Instructions per Execution                                  : 52026.00
Instructions per Cycle                                      : 1.86
Instructions per Byte                                       : 101.61
Branches per Execution                                      : 361.45
Branch Misses per Execution                                 : 0.73
Cache References per Execution                              : 97.03
Cache Misses per Execution                                  : 74.68
----------------------------------------
Metrics for: glz::to_chars
Total Iterations to Stabilize                               : 421
Measured Iterations                                         : 20
Bytes Processed                                             : 512.00
Nanoseconds per Execution                                   : 6480.30
Frequency (GHz)                                             : 4.68
Throughput (MB/s)                                           : 75.95
Throughput Percentage Deviation (+/-%)                      : 17.58
Cycles per Execution                                        : 30314.40
Cycles per Byte                                             : 59.21
Instructions per Execution                                  : 51513.00
Instructions per Cycle                                      : 1.70
Instructions per Byte                                       : 100.61
Branches per Execution                                      : 438.25
Branch Misses per Execution                                 : 0.73
Cache References per Execution                              : 95.93
Cache Misses per Execution                                  : 73.59
----------------------------------------
Library benchmarksuite::internal::to_chars, is faster than library: glz::to_chars, by roughly: 11.36%.
```

This structured output helps you quickly identify which implementation is faster or more efficient.

## Features

### Dual Benchmarking Support
- **CPU Benchmarking**: Traditional CPU performance measurement with hardware counters
- **GPU/CUDA Benchmarking**: Native CUDA kernel benchmarking with grid/block configuration
- **Mixed Workloads**: Compare CPU vs GPU implementations side-by-side
- **Automatic Device Selection**: Choose benchmark type via `bnch_swt::benchmark_types::cpu` or `bnch_swt::benchmark_types::cuda`

### Advanced Options
- **Cache Clearing**: Optional cache eviction between iterations for cold-cache benchmarks
- **Custom Metrics**: Define custom metric names for specialized benchmarks (e.g., compression ratios, custom throughput units)
- **Configurable Iterations**: Separate control over warmup iterations and measured iterations
- **Programmatic Access**: Retrieve raw performance metrics via `get_results()` for custom analysis

### Hardware Introspection
- **CPU Properties**: Comprehensive CPU detection and properties via `benchmarksuite_cpu_properties.hpp`
- **GPU Properties**: CUDA device detection and properties via `benchmarksuite_gpu_properties.hpp`

### Performance Counters
- **Cross-platform CPU counters**: Windows, Linux, macOS, Android, Apple ARM
- **CUDA performance events**: GPU-specific performance monitoring via `counters/cuda_perf_events.hpp`

### Utilities
- **Cache management**: Cross-platform cache clearing utilities
- **Aligned constants**: Compile-time aligned data structures
- **Random generators**: High-quality random data generation for benchmarks

## API Conventions

As of v1.0.0, all APIs follow snake_case naming convention:
- Functions: `do_not_optimize_away()`, `generate_random_integers()`, `print_results()`
- Types: `size_type`, `string_literal`
- Variables: `bytes_processed`, `test_values`

## Migrating from Pre-1.0.0

If you're upgrading from an earlier version:

1. **Update package name**: `benchmarksuite` → `benchmarksuite`

2. **Update include paths**: All includes are lowercase (already standard)

3. **Update API calls**: Convert camelCase/PascalCase to snake_case
   - `doNotOptimizeAway()` → `do_not_optimize_away()`
   - `printResults()` → `print_results()`
   - `generateRandomIntegers()` → `generate_random_integers()`

4. **Change benchmark interface**: Lambdas are replaced with structs
   ```cpp
   // Old (lambda-based)
   benchmark_stage<"test">::run_benchmark<"name">([&] {
       // code here
       return bytes_processed;
   });
   
   // New (struct-based)
   struct my_benchmark {
       BNCH_SWT_HOST static uint64_t impl(/* params */) {
           // code here
           return bytes_processed;
       }
   };
   benchmark_stage<"test">::run_benchmark<"name", my_benchmark>(/* args */);
   ```

5. **Update template parameters**: benchmark_stage now has more options
   ```cpp
   // Old (positional parameters)
   benchmark_stage<"test", iterations, measured>
   
   // New (with defaults and additional options)
   benchmark_stage<"test", 200, 25, benchmark_types::cpu, false, "">
   //                      ^^^  ^^  ^^^^^^^^^^^^^^^^^^  ^^^^^  ^^
   //                      max  measured  type         cache  metric
   ```

6. **New feature - Device types**: You can now specify CPU or CUDA benchmarking:
   ```cpp
   // CPU (default)
   benchmark_stage<"test", 200, 25, bnch_swt::benchmark_types::cpu>
   
   // CUDA/GPU
   benchmark_stage<"test", 100, 10, bnch_swt::benchmark_types::cuda>
   ```

7. **New feature - Cache clearing**: Enable cache clearing between iterations for CPU benchmarks:
   ```cpp
   // Clear cache between each iteration (5th parameter)
   benchmark_stage<"test", 200, 25, benchmark_types::cpu, true>
   ```

8. **New feature - Custom metrics**: Specify custom metric names for specialized benchmarks:
   ```cpp
   // Use custom metric instead of default throughput (6th parameter)
   benchmark_stage<"compression-test", 200, 25, benchmark_types::cpu, false, "compression-ratio">
   ```

---

Now you're ready to start benchmarking with **benchmarksuite**!