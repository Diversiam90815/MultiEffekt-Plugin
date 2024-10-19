# Plugin-Distortion

## Overview

**Plugin-Distortion** is an audio plugin developed in C++ using the [JUCE](https://juce.com/) framework. It applies various distortion effects to audio signals, allowing you to shape and enhance your sound. This plugin is currently under development.

## Features

- **Real-Time Parameter Control**: Adjust parameters like gain, tone, and level with an intuitive GUI.
- **Cross-Platform Support**: Compatible with Windows, macOS, and Linux.
- **Plugin Formats**: Available as VST3, AU (macOS), and Standalone application.
- **Automated Build Script**: Simplify the build process with a provided Python script.

## Prerequisites

- **CMake**: Version 3.25 or higher.
- **Python**: Version 3.x (for running `build.py`).
- **JUCE Framework**: Included as a submodule in `submodules/JUCE`.
- **Compiler**:
  - **Windows**: Visual Studio 2022 or higher.
  - **macOS**: Xcode 12 or higher.
  - **Linux**: GCC 9.0 or higher.

## Getting Started

### Cloning the Repository

Clone the repository along with its submodules:

```bash
git clone --recurse-submodules https://github.com/Diversiam90815/Plugin-Distortion.git
```

If you've already cloned the repository without submodules, initialize them with:

```bash
git submodule update --init --recursive
```

### Build Instructions

#### 1. Prepare the Build Environment

Navigate to the project directory and run the build preparation script:

```bash
cd Plugin-Distortion
python build.py --prepare
```

For a **Debug** build, add the `--debug` or `-d` option:

```bash
python build.py --prepare --debug
```

#### 2. Build the Plugin

To build the project, use the `--build` or `-b` option:

```bash
python build.py --build
```

Or combine preparation and building in one command:

```bash
python build.py --prepare --build
```

For a **Debug** build:

```bash
python build.py --prepare --build --debug
```

#### 3. Run the Plugin

After building, you can find the plugin in the `build` directory:

- **Standalone Application**:
  - **Windows**: `build/Release/PluginDistortion_Standalone.exe`
  - **macOS**: `build/Release/PluginDistortion_Standalone.app`
  - **Linux**: `build/Release/PluginDistortion_Standalone`
- **VST3 Plugin**: Located in `build/Release/VST3/PluginDistortion.vst3`
- **AU Plugin** (macOS only): Located in `build/Release/AU/PluginDistortion.component`

## Usage

- **In a DAW**:
  1. Copy the plugin file to your DAW's plugin directory.
  2. Rescan for plugins within your DAW.
  3. Insert the plugin onto an audio track.
  4. Adjust the parameters to achieve the desired distortion effect.

- **Standalone Application**:
  1. Run the `PluginDistortion_Standalone` executable.
  2. Use the built-in audio input/output settings to route audio through the plugin.
  3. Adjust the parameters in real-time to hear the changes.

## Project Structure

- `Source/` - Main source code:
  - `PluginProcessor.h/.cpp` - Audio processing logic.
  - `PluginEditor.h/.cpp` - GUI components.
  - `Parameters.h` - Plugin parameters definitions.
- `submodules/` - Contains the JUCE framework.
- `CMakeLists.txt` - CMake build configuration.
- `build.py` - Python script for building the project.
- `README.md` - Project documentation.
- `.clang-format` - Code style guidelines.

## Build Script Details (`build.py`)

The `build.py` script automates the build process:

- **Options**:
  - `--prepare` or `-p`: Generates build files using CMake.
  - `--build` or `-b`: Compiles the plugin.
  - `--debug` or `-d`: Builds in Debug mode.

**Examples**:

- Prepare and build in **Release** mode:

  ```bash
  python build.py --prepare --build
  ```

- Prepare and build in **Debug** mode:

  ```bash
  python build.py --prepare --build --debug
  ```

## Customization

- **Add New Effects**: Extend `PluginProcessor.cpp` with additional distortion algorithms.
- **Modify the Interface**: Customize the look and feel in `PluginEditor.cpp`.
- **Adjust Parameters**: Update `Parameters.h` to add or modify plugin controls.

## FAQ

### Q: The plugin isn't showing up in my DAW. What should I do?

**A:** Ensure you've copied the plugin file (`.vst3` or `.component`) to the correct plugin directory for your DAW and operating system. After copying, rescan your plugins within the DAW settings.

### Q: I get an error about missing JUCE modules when building.

**A:** Make sure you've initialized and updated the submodules. Run:

```bash
git submodule update --init --recursive
```

### Q: The build script fails with a CMake error. What could be wrong?

**A:** Verify that you have CMake version 3.25 or higher installed. You can check your CMake version with:

```bash
cmake --version
```

### Q: How do I build the plugin for a different platform?

**A:** The project uses CMake, which supports cross-platform builds. You'll need to run the build process on the target platform with the appropriate compiler and dependencies installed.


## Contributing

Contributions are welcome! To contribute:

1. **Fork** the repository.
2. **Create** a new branch for your feature:

   ```bash
   git checkout -b feature/your-feature
   ```

3. **Commit** your changes:

   ```bash
   git commit -m "Add your feature"
   ```

4. **Push** to your branch:

   ```bash
   git push origin feature/your-feature
   ```

5. **Submit** a pull request.

Please ensure your code adheres to the project's coding standards and includes appropriate documentation.

## License

This project is licensed under the [MIT License](LICENSE).

## Contact

For questions or feedback:

- **GitHub**: [Diversiam90815](https://github.com/Diversiam90815)
- **Website**: [www.diversiam.com](https://www.diversiam.com)

---

Feel free to explore, modify, and use this audio distortion plugin in your projects. Enjoy creating unique sounds!

## Code Formatting with Clang-Format

This project includes a `.clang-format` file that defines the code style guidelines for consistent formatting across the codebase. You can automatically format your code according to these standards using your editor's formatting shortcut.

### How to Use

- **In Visual Studio (or compatible editors)**:
  - Open the file you wish to format.
  - Press `Ctrl + K`, then `Ctrl + D` (Windows) or `Cmd + K`, then `Cmd + D` (macOS) to auto-format the current file using the predefined style.

This ensures consistency and improves code readability throughout the project.

---

*Note: This plugin is currently under development, and some features may not be fully implemented yet. Stay tuned for updates!*
