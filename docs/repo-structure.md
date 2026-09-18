# Repo Structure

## Top-level layout

```
tools/
cmake/
engine/
demo/
docs/
```

- `tools/` — build/orchestration scripts. See [build-orchestration.md](build-orchestration.md).
- `cmake/` — shared CMake helper modules, included by both `engine/` and `demo/`.
- `engine/` — engine and editor, one CMake project.
- `demo/` — demo game, a separate CMake project that consumes an installed
  engine package.
- `docs/` — project docs.

## engine/

- Single CMake project (`engine/CMakeLists.txt`) with its own
  `install()`/export.
- Editor is folded into engine, not a separate target — gated by a
  `WITH_EDITOR` compile flag. The editor runs in-process with the engine
  (see [tech-stack.md](tech-stack.md)) and its per-frame UI/render
  interleaving isn't a clean library boundary.
- `engine/src/` is flat for now — no subdivision by concern
  (core/ecs/render/editor/vendor). Split into subdirectories once there's
  enough code to warrant it.

## demo/

- Separate CMake project (`demo/CMakeLists.txt`). Consumes engine via
  `find_package(engine)` against an installed engine tree, not
  `add_subdirectory`.
- `demo/src/` is flat for now, same rationale as `engine/src/`.

## Module file convention

- Module interface units (`.cppm`) and implementation units (`.cpp`) are
  colocated in the same directory, one pair per logical module (e.g.
  `entity.cppm` + `entity.cpp`) — not split into parallel `include/`/`src/`
  trees.
- No `include/` directory: the public/private distinction is expressed via
  CMake's `FILE_SET CXX_MODULES` (interface units) vs. private
  `target_sources` (implementation units), not by directory location.
