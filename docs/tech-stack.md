# Tech Stack

## Goals

These shape the choices below, not just "what ships fastest":

- Deepen C++/modules knowledge.
- Use modern, current tooling and practices.

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
- 2D only.
- ECS storage: sparse-set (per-component pools, dense/sparse arrays,
  generational entity IDs). Exact layout finalized during implementation.

## Editor

- Dear ImGui (docking branch) owns the editor UI — panels, docks, menus,
  inspectors, and the viewport panel — drawn in-process in the same SDL3
  window and `SDL_GPU` swapchain as the engine. No second GUI toolkit, no
  embedded/foreign native window.
- SDL3 and Dear ImGui (plus its `imgui_impl_sdl3`/`imgui_impl_sdlgpu3`
  backends) are wrapped behind hand-written module interface units — their
  headers are included only inside those wrapper modules' global module
  fragments, never included directly elsewhere in the project.
- Per frame: build the ImGui UI first (this fixes the viewport panel's
  content-region size/position for the frame), render the scene into an
  offscreen `SDL_GPU` texture sized to that viewport panel, then render
  ImGui's draw data — which samples that texture via `ImGui::Image()` for
  the viewport panel — into the swapchain backbuffer, then present.
- The offscreen scene texture and the swapchain backbuffer are cleared
  separately, as two independent render passes.
- Viewport input (camera control, picking, etc.) is routed to the engine
  only when the viewport panel reports hover/focus
  (`ImGui::IsWindowHovered()` / `IsItemHovered()`); everything else goes
  through ImGui's own input handling.
- Detaching a panel to its own OS-level window uses ImGui's multi-viewport
  mode (`ImGuiConfigFlags_ViewportsEnable`), not foreign-window embedding.
- No cross-language FFI boundary — editor and engine are both C++, no
  bindings layer.
