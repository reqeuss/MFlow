# MFlow

> **Move less data. Do less work. Measure everything.**

MFlow is an open-source, local and native multimedia engine written in C++20.

The project aims to build an independent multimedia engine with its own architecture, without requiring FFmpeg or another external multimedia executable.

## 🌍 Languages

- 🇬🇧 **English — this README**
- 🇫🇷 [Français](README.fr.md)
- 🇪🇸 [Español](README.es.md)
- 🇩🇪 [Deutsch](README.de.md)

## 🚀 v0.4.0

MFlow 0.4.0 introduces the first reusable native media data model: packets, streams, timestamps, packet queues and media context. No external multimedia executable is used.

### What works

MFlow's native packet, stream and timestamp foundation is now available. Codec decoding/encoding and full demux/mux support are still being implemented incrementally.


### What works

- Platform and architecture detection
- Lightweight media file probing
- Detection of MP4, Matroska/WebM, WAV, MP3 and Ogg families
- Native execution pipeline
- Parallel scheduler
- Buffer management
- Native file/stream copying
- Windows and Linux CLI
- Tests and benchmarks

### What is not implemented yet

Full codec conversion is not available yet. MFlow therefore does not claim native H.264, H.265, AV1, AAC, Opus, or similar encoding/decoding support in this release.

Unsupported codec or scaling requests are explicitly rejected instead of being delegated to an external program.

## 🧠 Philosophy

MFlow is built around one simple rule:

> **Do not process what you do not need.**

Over time, the planner will determine whether an operation actually requires:

- decoding;
- encoding;
- format conversion;
- direct stream copying;
- additional memory allocation;
- CPU/GPU transfers;
- or none of these operations.

Target architecture:

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

## 📦 Project structure

```text
MFlow/
├── core/
│   ├── include/mflow/
│   └── src/
├── cli/
├── tests/
├── benchmarks/
├── examples/
├── docs/
├── CMakeLists.txt
├── README.md
├── README.fr.md
├── README.es.md
├── README.de.md
├── CHANGELOG.md
└── LICENSE
```

## 🔨 Build

### Windows

Requirements: CMake 3.20+, a C++20-compatible compiler and Git.

```powershell
cmake -S . -B build
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
```

With Ninja, executables are normally placed directly in `build/`.

```powershell
.\build\mflow.exe version
.\build\mflow.exe info
```

### Linux

Requirements: CMake 3.20+, a C++20-compatible compiler and Git.

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
ctest --test-dir build --output-on-failure
```

Then:

```bash
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

### System information

```text
mflow info
```

Displays the platform, architecture, hardware thread count and native media engine status.

### Probe a file

```text
mflow probe input.mp4
```

MFlow currently inspects known container/file signatures without launching an external program.

### Native copy

```text
mflow convert input.mp4 backup.mp4
```

In v0.3.0, this command uses MFlow's native copy path. It does not perform codec transcoding yet.

To prevent overwriting an existing file:

```text
mflow convert input.mp4 backup.mp4 --no-overwrite
```

## ⚡ Performance

MFlow focuses on reducing unnecessary work rather than simply increasing thread count.

Future media benchmarks should document:

- MFlow version;
- operating system;
- CPU;
- GPU;
- RAM;
- compiler;
- input media;
- output format;
- processing parameters.

No serious performance comparison should be published without reproducible measurements.

## 🧩 Native architecture

Components are separated so the engine can evolve incrementally:

```text
Media Probe
    ↓
Stream Model
    ↓
Planner
    ↓
Pipeline / Scheduler
    ↓
Decoder / Filter / Encoder
    ↓
Muxer
```

The next development steps are real `Packet`, `Stream` and `Frame` models, followed by native parsers, demuxers and muxers.

## 🗺️ Roadmap

### v0.3.x

- stability;
- additional tests;
- Packet model;
- Stream model;
- timestamps;
- improved probing;
- real media benchmarks.

### v0.4.x

- native MP4 parser;
- MP4 demuxer/muxer;
- metadata;
- audio/video stream model.

### v0.5.x

- frames;
- pixel formats;
- audio formats;
- first native codec implementations.

### Later

- H.264 / H.265 / AV1;
- AAC / Opus;
- MKV/WebM;
- zero-copy;
- GPU processing;
- pipeline fusion;
- asynchronous I/O;
- hardware acceleration.

Intermediate versions (`v0.3.1`, `v0.3.2`, etc.) will progressively add these capabilities while keeping the foundation stable.

## 🧪 Tests

```bash
ctest --test-dir build --output-on-failure
```

The project is intended to remain buildable and testable on Windows and Linux.

## 🤝 Contributing

Contributions are welcome. For significant changes, prefer modular architecture, tests and reproducible benchmarks for performance-related work.

## 🔐 Independence

MFlow is designed to operate without an external multimedia executable. Features that are not implemented are explicitly rejected instead of silently falling back to an external dependency.

## 📜 License

MFlow is distributed under the MIT License.

---

**MFlow v0.4.0** — Native packet and stream engine.
