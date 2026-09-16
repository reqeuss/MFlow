# MFlow

Efficient open-source multimedia processing engine.

> Move less data. Do less work. Measure everything.

MFlow is a local-first C++20 multimedia engine focused on efficient execution: avoiding unnecessary decoding, encoding, conversions, memory copies and CPU/GPU transfers.

## Status

**v0.2 — First conversion pipeline.**

This release introduces the first real media conversion command through an external media backend while keeping the conversion interface inside MFlow. The core remains modular so future native backends, zero-copy paths and hardware acceleration can be added without changing the CLI contract.

Included:
- C++20 core
- pipeline engine
- reusable buffer pool
- parallel scheduler
- system detection
- lightweight media probing
- media conversion API
- CLI conversion command
- tests and benchmarks
- cross-platform CI

## Build

### Windows

```powershell
cmake -S . -B build
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
```

With Ninja, executables are normally placed directly in `build/`.

### Linux/macOS

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
ctest --test-dir build --output-on-failure
```

## CLI

```text
mflow version
mflow info
mflow probe <file>
mflow convert <input> <output> [options]
mflow pipeline-demo
mflow benchmark
```

### Convert a video

MFlow v0.2 requires a media conversion backend available on `PATH`.

```powershell
mflow convert input.mp4 output.mp4
```

Select codecs:

```powershell
mflow convert input.mp4 output.mp4 --video-codec libx264 --audio-codec aac
```

Resize while converting:

```powershell
mflow convert input.mp4 output.mp4 --scale 1280:720
```

Prevent overwriting an existing output:

```powershell
mflow convert input.mp4 output.mp4 --no-overwrite
```

Check whether the backend is detected:

```powershell
mflow info
```

The output includes `Conversion backend: available` when a compatible backend is found.

## Architecture

```text
INPUT -> DEMUX -> STREAM PLANNER -> DECODE -> FILTER -> ENCODE -> MUX -> OUTPUT
                                      |                  |
                                      +-- MEMORY POOL --+
                                                 |
                                             SCHEDULER
```

The v0.2 conversion layer is intentionally isolated from the core execution engine. This lets MFlow evolve its scheduling, memory and stream-planning logic independently from individual media backends.

The long-term design targets zero-copy paths, buffer lifetime planning, pipeline fusion, asynchronous I/O, hardware acceleration and stream-aware processing.

## Efficiency Principle

MFlow is designed around a simple rule:

> Don't process what you don't need.

For example, a future audio-only workflow should be able to avoid unnecessary video processing. Likewise, a hardware pipeline should preserve frames on the accelerator instead of repeatedly copying them through system memory.

## Roadmap

See `docs/ROADMAP.md` and `docs/ARCHITECTURE.md`.

## Contributing

Performance work should include reproducible benchmarks whenever possible. Do not publish speed claims without documenting hardware, media, compiler and software versions.

## License

MIT.
