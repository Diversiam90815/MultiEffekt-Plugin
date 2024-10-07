# PluginTemplate

## Overview

PluginTemplate is a C++ audio plugin project template that uses the [JUCE](https://juce.com/) framework. This template provides a starting point for developing audio plugins, including CMake build scripts and a Python script for automated building.

## Features

- **C++20 Standard**: Utilizes modern C++ features for efficient and robust code.
- **JUCE Integration**: Seamlessly integrates the JUCE framework for audio plugin development.
- **CMake Build System**: Cross-platform build configuration using CMake.
- **Automated Build Script**: Python script to simplify the build and preparation process.
- **Visual Studio Support**: Configured for building with Visual Studio 2019 or higher.

## Prerequisites

- **CMake**: Version 3.25 or higher.
- **Python**: Version 3.x (for running `build.py`).
- **Visual Studio**: 2019 or higher (the project uses the Visual Studio 17 generator).
- **JUCE Framework**: Included as a submodule in `submodules/JUCE`.

## Getting Started

### Cloning the Repository

Clone the repository including its submodules:

```bash
git clone --recurse-submodules https://github.com/Diversiam90815/Plugin-Template.git
```

If you've already cloned the repository without submodules, initialize them with:

```bash
git submodule update --init --recursive
```

### Build Instructions

#### 1. Prepare the Build Environment

Before building the project, you need to generate the necessary build files using CMake. This can be done using the `build.py` script with the `--prepare` or `-p` option.

```bash
cd PluginTemplate
python build.py --prepare
```

**Note**: By default, this prepares the project for a Release build. If you wish to prepare for a Debug build, include the `--debug` or `-d` option:

```bash
python build.py --prepare --debug
```

This sets up the build environment for a Debug configuration.

#### 2. Build the Project

To build the project, use the `--build` or `-b` option:

```bash
python build.py --build
```

This will compile the project using the build files generated during the preparation step.

- **Release Build**: By default, the build is configured for a Release build.
- **Debug Build**: To build the project in Debug mode, include the `--debug` or `-d` option:

  ```bash
  python build.py --build --debug
  ```

**Important**: If you did not run the `--prepare` step separately, the script will automatically prepare the build environment before building.

#### 3. Combined Preparation and Build

You can combine preparation and building in a single command. This is useful if you want to ensure that your build environment is up-to-date before compiling.

- **Release Build**:

  ```bash
  python build.py --prepare --build
  ```

- **Debug Build**:

  ```bash
  python build.py --prepare --build --debug
  ```

In both cases, including the `--debug` or `-d` option switches the configuration to Debug mode.

### Running the Plugin

After a successful build, the Standalone application can be found in the build output directory. Navigate to:

```
build/<Configuration>/PluginTemplate_Standalone.exe
```

Replace `<Configuration>` with `Release` or `Debug` depending on your build configuration.

## Project Structure

- `Source/` - Contains the source code:
  - `PluginProcessor.h/.cpp` - The main processing code for the plugin.
  - `PluginEditor.h/.cpp` - The GUI editor for the plugin.
  - `Parameters.h` - Definitions for plugin parameters.
- `submodules/` - Contains the JUCE framework as a Git submodule.
- `CMakeLists.txt` - The CMake build configuration file.
- `build.py` - Python script to automate build preparation and compilation.
- `ReadMe.md` - Project documentation (this file).

## CMake Configuration Details

Key configurations in `CMakeLists.txt`:

- **Project Setup**:
  - Project name: `PluginTemplate`
  - Version: `1.0`
  - Language: `CXX` (C++)
- **C++ Standard**: C++20
- **JUCE Integration**:
  - JUCE is added via `add_subdirectory(submodules/JUCE)`.
  - The plugin is added using `juce_add_plugin` with:
    - Company Name: `DiversiamProduction`
    - Plugin Manufacturer Code: `3160`
    - Plugin Code: `IOTO`
    - Formats: `Standalone`
    - Product Name: `${PROJECT_NAME}`
- **Source Files**:
  - Headers and source files are specified and grouped.
- **Compiler Definitions**:
  - Disables web browser and CURL support in JUCE to streamline the build.
  - Sets various JUCE options for audio and media formats.
  - Defines `ENV_DEVELOPMENT` and `_CRT_SECURE_NO_WARNINGS`.
- **Compiler Options**:
  - For Release configuration: `/Oi`, `/Gy` (enable intrinsic functions and function-level linking).
  - For Debug configuration: `/Od`, `/Z7` (disable optimizations and enable debug information).
  - General options: `/sdl`, `/MP` (enable additional security checks and multi-processor compilation).
  - Warnings are not treated as errors (`/WX-`).
  - Suppresses specific warnings: `C4146`, `C4996`.
- **Linking Libraries**:
  - Links against `juce_audio_utils`, `juce_audio_plugin_client`, and `juce_core`.

## Build Script (`build.py`) Details

The `build.py` script simplifies the build process with the following features:

- **Auto CWD Management**: Changes working directory automatically and restores it afterward.
- **Command Execution**: Runs system commands and handles output and errors.
- **Build Preparation**:
  - Generates build files using CMake with the specified generator (`Visual Studio 17`).
  - The `--debug` or `-d` option affects the configuration by setting the `TARGET_CONFIG` to `Debug` (default is `Release`).
- **Build Execution**:
  - Cleans previous builds if necessary.
  - Builds the project using the generated build files.
- **Command-Line Arguments**:
  - `-p`, `--prepare`: Prepares the project for building or IDE usage.
    - **Usage**: `python build.py --prepare` (for Release build)
    - **Debug Build**: Include `--debug` to prepare for Debug build.
  - `-b`, `--build`: Builds the project.
    - **Usage**: `python build.py --build` (for Release build)
    - **Debug Build**: Include `--debug` to build in Debug mode.
  - `-d`, `--debug`: Switches the configuration to Debug mode for both preparation and building.
    - **Usage**: Can be combined with `--prepare` and/or `--build`.

### Script Usage Examples

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

- **Prepare and Build the Project in Debug Mode**:

  ```bash
  python build.py --prepare --build --debug
  ```

**Note**: The `--debug` or `-d` option affects both preparation and building steps. If you include it, both steps will use the Debug configuration.


## Code Formatting with Clang-Format

This project includes a `.clang-format` file that defines the code style guidelines for consistent formatting across the codebase. You can automatically format your code according to these standards using your editor's shortcut.

### How to Use

- **In Visual Studio (or compatible editors on macOS):**
  - Open the file you wish to format.
  - Press `Cmd + K`, then `Cmd + D` to auto-format the current file using the predefined style.

This will format your code based on the rules specified in the `.clang-format` file, ensuring consistency and improving code readability.


## Customization

You can customize the project by modifying:

- **Plugin Information**: Update the company name, manufacturer code, plugin code, and product name in `CMakeLists.txt`.
- **JUCE Modules**: Enable or disable JUCE modules as needed.
- **Source Code**: Implement your plugin logic in `PluginProcessor.cpp` and design your GUI in `PluginEditor.cpp`.

## Troubleshooting

- **Missing Submodules**: If you encounter errors related to missing JUCE modules, ensure you've cloned the repository with submodules.
- **CMake Errors**: Make sure you have the required CMake version (3.25 or higher).
- **Compiler Errors**: Ensure you're using a compatible compiler (Visual Studio 2019 or higher) and that your environment is correctly set up.
- **Incorrect Build Configuration**: If the build is not using the desired configuration (Debug or Release), ensure you're using the `--debug` or `-d` option appropriately.


## Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository.
2. Create a new branch: `git checkout -b feature/YourFeature`.
3. Commit your changes: `git commit -am 'Add some feature'`.
4. Push to the branch: `git push origin feature/YourFeature`.
5. Submit a pull request.

