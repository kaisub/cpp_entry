# C++ Entry Project

[![C++ CI Pipeline](https://github.com/kaisub/cpp_entry/actions/workflows/ci.yml/badge.svg)](https://github.com/kaisub/cpp_entry/actions/workflows/ci.yml)

## Overview
This is a modern C++ project template featuring automated builds, unit testing with Google Test, and static code analysis (Cppcheck & Clang-Tidy) via GitHub Actions.

**Key Features:**
* Sample implementations for various C++ language code rules.
* Sample implementations for data manipulation.
* Sample implementations for basic algorithms.

---

## 🛠️ Prerequisites & Installation

Depending on your operating system, install the required toolchains and static analysis tools.

### Windows (MSVC)
```powershell
# Cppcheck
winget install cppcheck

# Clang-Tidy (LLVM)
winget install LLVM

# Code Coverage
winget install OpenCppCoverage.OpenCppCoverage
```

### Windows MSYS2 (UCRT64 Environment)
Open your UCRT64 terminal and run:

```bash
# CMake and GCC Toolchain
pacman -S mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-gcc

# Cppcheck
pacman -S mingw-w64-ucrt-x86_64-cppcheck

# Code Coverage (gcovr & dependencies)
pacman -S mingw-w64-ucrt-x86_64-python-pip
pacman -S mingw-w64-ucrt-x86_64-libxml2 mingw-w64-ucrt-x86_64-libxslt mingw-w64-ucrt-x86_64-python-lxml
/ucrt64/bin/python.exe -m pip install gcovr --break-system-packages
```

### Ubuntu / WSL
```bash
sudo apt update
sudo apt install cmake g++ cppcheck clang-tidy gcovr
```

---

## 🚀 Workflow & Scripts

The project includes a set of automated scripts in the `scripts_builds/` directory to simplify the development process. 

> **Note:** Use `.bat` scripts on Windows (CMD/PowerShell) and `.sh` scripts on Linux/MSYS2. You can append the `--clean` flag to most build scripts to force a fresh build.

| Script Name | Description |
| :--- | :--- |
| **`clean`** | Removes `build`, `bin`, `deps`, and `coverage` directories. |
| **`build_all`** | Configures and builds the main application and unit tests. |
| **`build_code`** | Configures and builds ONLY the main application. |
| **`build_run_uts`** | Builds and immediately executes the unit tests. |
| **`code_check`** | Runs Cppcheck and Clang-Tidy static analysis. |
| **`generate_coverage_*`** | Generates an HTML code coverage report (requires tests to be run first). |

---

## 💻 Manual Commands & VS Code Shortcuts

### VS Code Task Shortcuts
If you have configured `tasks.json`, you can use the following shortcuts:
* `Ctrl + Shift + F5` : Build project
* `F7` : Build & Run application
* `Ctrl + Shift + T` : Run Unit Tests
* `Ctrl + Shift + C` : Clean workspace

### Running Static Analysis manually
```bash
# Run Cppcheck
cmake --build build --target run_cppcheck

# Run Clang-Tidy
cmake --build build --target run_tidy
```