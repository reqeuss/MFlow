# MFlow

Efficient open-source multimedia processing engine.

> Move less data. Do less work. Measure everything.

MFlow is a local-first C++20 multimedia engine focused on efficient execution: avoiding unnecessary downloads, decoding, encoding, conversions, memory copies and CPU/GPU transfers.

## Status

**v0.1 — Foundation.** This release provides the execution architecture, not a replacement for FFmpeg yet.

Included:
- C++20 core
- pipeline engine
- reusable buffer pool
- parallel scheduler
- system detection
- lightweight media probing
- CLI
- tests and benchmarks
- cross-platform CI

## Build

### Windows

```powershell
cmake -S . -B build
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
```

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
mflow pipeline-demo
mflow benchmark
```

## Architecture

```text
INPUT -> DEMUX -> STREAM PLANNER -> DECODE -> FILTER -> ENCODE -> MUX -> OUTPUT
                                      |                  |
                                      +-- MEMORY POOL --+
                                                 |
                                             SCHEDULER
```

The long-term design targets zero-copy paths, buffer lifetime planning, pipeline fusion, asynchronous I/O, hardware acceleration and stream-aware processing.

## Example

If a workflow only needs audio, MFlow should eventually avoid downloading and decoding an unnecessary video stream. If a GPU can decode, filter and encode without returning frames to system RAM, MFlow should preserve that path.

## Roadmap

See `docs/ROADMAP.md` and `docs/ARCHITECTURE.md`.

## Contributing

Performance work should include reproducible benchmarks whenever possible. Do not publish speed claims without documenting hardware, media, compiler and software versions.

## License

MIT.
