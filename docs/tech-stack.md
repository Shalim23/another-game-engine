# Tech Stack

## Goals

These shape the choices below, not just "what ships fastest":

- Deepen C++/modules knowledge.
- Deepen cross-language FFI/binding experience (C++ ↔ another language).

## Language

- C++23, using C++ modules (not headers) as the primary organization unit.

## Compiler

- Clang 23, installed from LLVM's official apt repo (`apt.llvm.org`).
- Binaries are versioned (`clang-23`, `clang++-23`) — the build points at
  them explicitly, no bare `clang`/`clang++` symlink.

## Build system

- CMake + Ninja. Ninja is required for CMake's C++ module dependency
  scanning.

## Dependency management

- CMake `FetchContent`. Dependencies are built from source as part of the
  project build, using the same compiler/flags as the rest of the project —
  required for module interface (BMI) compatibility.
- No binary caching: clean builds recompile dependencies from source.

## Engine backend

- SDL3. Covers windowing/input/audio/gamepad, plus `SDL_GPU` as the
  rendering abstraction over Vulkan/D3D12/Metal.
- Rendering pipeline, ECS, and scene graph are built on top of SDL3, not
  provided by it.

## Editor

- PySide6 (Qt) owns the editor shell: `QApplication`, top-level window,
  docks, menus, inspectors, layout.
- C++/SDL3/Vulkan owns the viewport window, rendering, swapchain, and
  input — a single embedded viewport, no detached/floating Qt viewport
  windows.
- Embedding direction: Qt creates the native child window; SDL wraps it
  (`SDL_CreateWindowWithProperties`). Fetch the X11 window id via
  `SDL_GetNumberProperty(..., SDL_PROP_WINDOW_X11_WINDOW_NUMBER, 0)` — it's
  numeric, not a pointer property.
- Qt's event loop does not pump SDL events on its own — SDL is polled from
  the Qt/main thread via a timer-driven tick.
- Qt controls the embedded window's resize; on resize, mark the Vulkan
  swapchain dirty and recreate it. No GL/Vulkan context sharing between Qt
  and the engine.
- nanobind exposes high-level engine commands and state to the editor, not
  individual render objects. Release the GIL for long-running C++ calls;
  reacquire it for any callback into Python.
