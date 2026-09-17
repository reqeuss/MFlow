# MFlow

> **Move less data. Do less work. Measure everything.**

MFlow is a local, open-source native multimedia engine written in C++20.

The project aims to build an independent multimedia engine whose planner can determine which operations are actually required before processing data.

## 🌍 Languages

- 🇫🇷 [Français](README.md)
- 🇬🇧 English — this README
- 🇪🇸 [Español](README.es.md)
- 🇩🇪 [Deutsch](README.de.md)

## 🚀 v0.3.0

MFlow 0.3.0 establishes the first foundations of the native media engine.

**MFlow does not require an external multimedia executable.** The current native path is implemented directly inside the project.

### Current features

- Platform and architecture detection
- Lightweight media file probing
- MP4, Matroska/WebM, WAV, MP3 and Ogg family detection
- Pipeline execution
- Parallel scheduler
- Buffer management foundations
- Native file/stream copying
- Windows and Linux CLI
- Tests and benchmarks

### Not implemented yet

Full codec transcoding is not available yet. This release does not claim native H.264, H.265, AV1, AAC, Opus or similar codec encoding/decoding.

Unsupported codec or scaling requests are rejected explicitly instead of being delegated to an external program.

## 🧠 Philosophy

> **Don't process what you don't need.**

The long-term planner will be able to reason about decoding, encoding, stream copying, format conversion, memory allocation and CPU/GPU transfers before executing a graph.

```text
INPUT
  ↓
STREAM PLANNER
  ↓
WORK GRAPH
  ├── VIDEO → DECODE → FILTER → ENCODE ─┐
  └── AUDIO → DECODE → PROCESS → ENCODE ┤
                                          ↓
                                         MUX
                                          ↓
                                       OUTPUT
```

## 🔨 Build

### Windows

Requirements: CMake 3.20+, a C++20 compiler and Git.

```powershell
cmake -S . -B build
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
```

```powershell
.\build\mflow.exe version
.\build\mflow.exe info
```

### Linux

Requirements: CMake 3.20+, a C++20 compiler and Git.

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
ctest --test-dir build --output-on-failure
./build/mflow version
./build/mflow info
```

## 🖥️ CLI

```text
mflow version
mflow info
mflow probe <file>
mflow convert <input> <output> [--no-overwrite]
mflow pipeline-demo
mflow benchmark
```

`mflow convert` currently performs a native buffered copy. Codec transcoding will be introduced only when implemented natively.

## 🗺️ Roadmap

- v0.3.x: packets, streams, timestamps, probing and stability
- v0.4.x: native MP4 parsing, demuxing, muxing and metadata
- v0.5.x: frames, pixel/audio formats and first native codecs
- Later: H.264, H.265, AV1, AAC, Opus, MKV/WebM, zero-copy, GPU acceleration and asynchronous I/O

## 🤝 Contributing

Keep the architecture modular. Add tests for behavior changes and reproducible benchmarks for performance claims.

## 📜 License

MIT.
