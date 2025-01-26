# MultiEffekt-Plugin

## Overview

**MultiEffekt-Plugin** is an audio plugin developed in C++ using the [JUCE](https://juce.com/) framework. The goal is to access multiple effects inside a single plugin in any desired order, allowing you to shape and enhance your sound. This plugin is currently under development.


## Effects
- **Distortion**: Multiple distortion type to select from: Saturation, Hard & Soft Clipping.
- **Delay**: A flexible delay module supporting different delay times for each channel (currently just Single Tapping Delay; PingPong delay planned)
- **Panner**: Includes a mono and stereo panner, with dynamic LFO modulation for creative stereo imaging.
- **Reverb** (in development)
- **Equalizer** (in development)
- **Compressor** (in development)

## Features

- **Modern C++**: Leverages the C++20 standard for optimized and robust code.
- **JUCE Framework Integration**: Offers seamless integration with JUCE for efficient audio plugin development.
- **Unit Testing with GoogleTest**: Supports unit testing with the GoogleTest framework.
- **Package Management with CPM**: Facilitates easy inclusion and installation of packages via CPM.
- **Cross-Platform CMake Build System**: Uses CMake for consistent, cross-platform build configuration.
- **Automated Build Script**: A Python script to simplify setup and build processes.
- **Visual Studio Compatibility**: Configured for Visual Studio 2022, but can be adjusted in the Python script.

## Prerequisites

- **CMake**: Version 3.25 or higher.
- **Python**: Version 3.x (for running `build.py`).
- **Visual Studio**: 2022 (the project uses the Visual Studio 17 generator).

## Getting Started

### Cloning the Repository

Clone the repository including:

```bash
git clone git@github.com:Diversiam90815/MultiEffekt-Plugin.git
```

### Build Instructions

#### Prepare the Build Environment

Before building the project, you need to generate the necessary build files using CMake. This can be done using the `build.py` script with the `--prepare` or `-p` option.

```bash
cd MultiEffekt-Plugin
python build.py -p
```

For a **Debug** build, add the `--debug` or `-d` option:

```bash
python build.py -pd
```

This sets up the build environment for a Debug configuration.

#### Build the Project

To build the project, use the `--build` or `-b` option:

```bash
python build.py -b
```

This will compile the project using the build files generated during the preparation step.

- **Release Build**: By default, the build is configured for a Release build.
- **Debug Build**: To build the project in Debug mode, include the `--debug` or `-d` option:

  ```bash
  python build.py -bd
  ```

**Important**: You do not need to run the `--prepare` step separately, the script will automatically prepare the build environment before building.

### Running the Plugin

After a successful build, the application can be found in the build output directory. Currently, the audio plugin is set to build VST3 and standalone executable binaries. They can be found within the respective folder.


## Project Structure

- `cmake/` - Contains CMake files:
  - `cpm.cmake` - Installing the currently latest version of CMake's package manager CPM into the Lib folder.

- `plugin/` - Containing the JUCE audio plugin project.

- `test/` - Containing the GoogleTest project.
    
- `CMakeLists.txt` - The top-level CMake build configuration file.
- `build.py` - Python script to automate build preparation and compilation.
- `Project.h.in` - CMake configures this during compliation and sets project specific data that can be used project-wide.
- `.clang-format` - Containing uniform format rules for the C++ code. See "Code Formatting with Clang-Format". 
- `ReadMe.md` - Project documentation (this file).


## Build Script (`build.py`) Details

The `build.py` script automates setup and compilation. It can be used with various coman line arguments:
  - `-p`, `--prepare`: Prepares the project for building or IDE usage.
  - `-b`, `--build`: Builds the project.
  - `-d`, `--debug`: Sets the configuration to Debug mode, usable with `--prepare` and `--build`.
  - `-v`, `--version`: Prints the installed CMake and Python versions.

### Script Usage Examples

- **Print out the current version of CMake and Python installed**:

  ```bash
  python build.py --version 
  ```

- **Prepare the Project for Release Build**:

  ```bash
  python build.py --prepare
  ```

- **Prepare the Project for Debug Build**:

  ```bash
  python build.py --prepare --debug
  ```

- **Build the Project in Release Mode**:

  ```bash
  python build.py --build
  ```

- **Build the Project in Debug Mode**:

  ```bash
  python build.py --build --debug
  ```

- **Prepare and Build the Project in Release Mode**:

  ```bash
  python build.py --prepare --build
  ```

**Note**: The `--debug` or `-d` option affects both preparation and building steps. If you include it, both steps will use the Debug configuration.


## Code Formatting with Clang-Format

This project includes a `.clang-format` file that defines the code style guidelines for consistent formatting across the codebase. You can automatically format your code according to these standards using your editor's shortcut.

### How to Use

- **In Visual Studio (or compatible editors on macOS):**
  - Open the file you wish to format.
  - Press `Cmd + K`, then `Cmd + D` to auto-format the current file using the predefined style.

This will format your code based on the rules specified in the `.clang-format` file, ensuring consistency and improving code readability.

