# GLFW + OpenGL Test Application

This document describes the `main_test.cpp` file, which is a standalone test application for verifying OpenGL and GLFW setup. This test creates a simple window with OpenGL rendering to ensure the graphics stack is properly configured.

## Overview

`main_test.cpp` is a minimal OpenGL/GLFW test program that:

- Initializes GLFW (Graphics Library Framework)
- Creates an OpenGL 3.3 Core Profile context
- Initializes GLEW (OpenGL Extension Wrangler Library)
- Displays system OpenGL information
- Renders a red background in a window
- Provides basic error handling and debugging utilities

## Purpose

This test file serves as:

1. **Setup Verification** - Confirms that GLFW, GLEW, and OpenGL are properly installed and linked
2. **Development Reference** - Provides a baseline for future OpenGL-based maze rendering
3. **Debugging Tool** - Includes error callbacks and OpenGL error checking utilities

## Dependencies

### Required Libraries

1. **GLFW3** - Cross-platform window and input handling

   - Handles window creation, context management, and input events
   - Website: https://www.glfw.org/

2. **GLEW** - OpenGL Extension Wrangler Library

   - Manages OpenGL extensions and function pointers
   - Website: http://glew.sourceforge.net/

3. **OpenGL** - Graphics rendering API
   - System framework on macOS
   - Version requirement: OpenGL 3.3 Core Profile or higher

### Installation (macOS)

```bash
brew install glfw glew
```

## Building

### Using VS Code Tasks

The project includes a configured build task in `.vscode/tasks.json`:

1. Open `main_test.cpp` in VS Code
2. Press `Cmd+Shift+B` (Build)
3. Or use the Command Palette: `Tasks: Run Build Task`

### Manual Compilation

```bash
g++ --std=c++17 -g main_test.cpp \
    src/builder.cpp \
    src/runner.cpp \
    src/welcome.cpp \
    -framework OpenGL \
    -lglfw \
    -lGLEW \
    -o main_test
```

**Note:** The source files (`builder.cpp`, `runner.cpp`, `welcome.cpp`) are included in the build but not currently used by this test.

## Running

```bash
./main_test
```

### Expected Output

**Console Output:**

```
Using OpenGL: 4.1
Renderer used: [Your GPU Name]
Shading Language: [GLSL Version]
```

**Window Display:**

- A 640x480 window titled "Space Invaders"
- Red background (RGB: 1.0, 0.0, 0.0)
- Window remains open until closed by user

## Code Structure

### Error Handling

#### GLFW Error Callback

```cpp
void error_callback(int error, const char *description)
```

Handles GLFW-specific errors and prints them to stderr.

#### OpenGL Error Checking

```cpp
inline void gl_debug(const char *file, int line)
```

Checks for OpenGL errors using `glGetError()` and reports them with context. Handles common error codes:

- `GL_INVALID_ENUM` - Invalid enumeration value
- `GL_INVALID_VALUE` - Invalid numeric value
- `GL_INVALID_OPERATION` - Operation not allowed in current state
- `GL_INVALID_FRAMEBUFFER_OPERATION` - Framebuffer is incomplete
- `GL_OUT_OF_MEMORY` - Not enough memory

### Initialization Sequence

1. **Set Error Callback**

   ```cpp
   glfwSetErrorCallback(error_callback);
   ```

2. **Initialize GLFW**

   ```cpp
   if (!glfwInit())
       return -1;
   ```

3. **Configure OpenGL Context**

   ```cpp
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
   ```

   - Uses Core Profile (no deprecated features)
   - Requests OpenGL 3.3
   - Forward compatible (macOS requirement)

4. **Create Window**

   ```cpp
   window = glfwCreateWindow(640, 480, "Space Invaders", NULL, NULL);
   ```

5. **Make Context Current**

   ```cpp
   glfwMakeContextCurrent(window);
   ```

6. **Initialize GLEW**

   ```cpp
   GLenum err = glewInit();
   ```

   Must happen after making context current!

7. **Query OpenGL Info**
   ```cpp
   glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]);
   glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]);
   ```

### Render Loop

```cpp
glClearColor(1.0, 0.0, 0.0, 1.0);  // Set clear color to red
while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);   // Clear with red
    glfwSwapBuffers(window);         // Present frame
    glfwPollEvents();                // Process events
}
```

### Cleanup

```cpp
glfwDestroyWindow(window);
glfwTerminate();
```

## Debugging

### Common Issues

#### 1. Undefined Symbols Error

```
Undefined symbols for architecture arm64:
  "_glfwInit", "_glClear", etc.
```

**Solution:** Ensure linking flags are included:

- `-framework OpenGL`
- `-lglfw`
- `-lGLEW`

#### 2. GLEW Initialization Failed

**Cause:** GLEW initialized before OpenGL context is current
**Solution:** Always call `glewInit()` after `glfwMakeContextCurrent()`

#### 3. Black or No Window Appears

**Check:**

- GLFW initialization succeeded
- Window creation succeeded (not NULL)
- `glfwSwapBuffers()` is called in render loop
- `glfwPollEvents()` is called to process window events

#### 4. OpenGL Version Errors

**Solution:** macOS is limited to OpenGL 4.1. Ensure version hints don't exceed:

```cpp
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
```

## Future Integration

This test file provides the foundation for future graphical maze rendering:

### Planned Features

1. **2D Maze Rendering** - Render the maze using OpenGL primitives
2. **Smooth Player Movement** - Animate player position with interpolation
3. **Enhanced Visuals** - Textures, colors, lighting effects
4. **Input Handling** - Real-time keyboard input via GLFW callbacks
5. **Performance** - Hardware-accelerated rendering for large mazes

### Integration Points

- Use `Maze` class from `builder.h` to generate maze data
- Adapt `GameRunner` logic for graphical input/output
- Replace ASCII rendering with OpenGL vertex buffers
- Add shaders for customizable rendering effects

## Technical Notes

### OpenGL Core Profile vs Compatibility

This application uses **Core Profile**, which:

- Removes deprecated fixed-function pipeline
- Requires modern shader-based rendering
- Provides better performance and forward compatibility
- Is the only option on modern macOS

### macOS Specifics

- **OpenGL 4.1 Maximum** - macOS deprecated OpenGL and caps at version 4.1
- **Forward Compatibility Required** - Must set `GLFW_OPENGL_FORWARD_COMPAT`
- **Frameworks** - OpenGL linked as a framework, not a library

### C++ Standards

- Compiled with C++17 (`--std=c++17`)
- Uses standard library (`<cstdio>`)
- Compatible with the C++20 standard used in main project

## Resources

- [GLFW Documentation](https://www.glfw.org/documentation.html)
- [GLEW Documentation](http://glew.sourceforge.net/basic.html)
- [OpenGL 3.3 Core Profile](https://www.khronos.org/opengl/wiki/Core_And_Compatibility_in_Contexts)
- [OpenGL on macOS](https://developer.apple.com/opengl/)

## License

This test file is part of the Maze CLI project. See main project license for details.
