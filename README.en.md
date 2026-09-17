# MFlow

> **Move less data. Do less work. Measure everything.**

MFlow is a local, open-source, native multimedia engine written in C++20.

The project is designed to become a truly independent multimedia engine, with no FFmpeg dependency and no external multimedia executable.

## 🌍 Languages

- 🇬🇧 **English — this README**
- 🇫🇷 [Français](README.fr.md)
- 🇪🇸 [Español](README.es.md)
- 🇩🇪 [Deutsch](README.de.md)

## 🚀 v0.3.0

MFlow 0.3.0 establishes the first foundations of the native media engine.

**No FFmpeg. No external multimedia executable.** Media processing is being implemented directly inside MFlow.

### Current features

- Platform and architecture detection
- Lightweight media file probing
- MP4, Matroska/WebM, WAV, MP3 and Ogg family detection
- Native execution pipeline
- Parallel scheduler
- Buffer management foundations
- Native file/stream copying
- Windows and Linux CLI
- Tests and benchmarks

### Not implemented yet

Full codec transcoding is not available yet. This release does not claim native H.264, H.265, AV1, AAC, Opus or similar codec encoding/decoding.

Unsupported codec or scaling requests are rejected explicitly instead of being delegated to an external program.

## 🧠 Philosophy

MFlow follows one simple rule:

> **Don't process what you don't need.**

The long-term planner will determine whether an operation requires decoding, encoding, format conversion, stream copying, additional memory allocation, CPU/GPU transfers, or none of these.

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
├── README.en.md
├── README.es.md
├── README.de.md
├── CHANGELOG.md
└── LICENSE
```

## 🔨 Build

### 🪟 Windows

Requirements: CMake 3.20+, a C++20-compatible compiler and Git.

```powershell
cmake -S . -B build
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
.\build\mflow.exe version
.\build\mflow.exe info
```

### 🐧 Linux

Requirements: CMake 3.20+, a C++20-compatible compiler and Git.

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

### Native copy

```text
mflow convert input.mp4 backup.mp4
```

In v0.3.0, `convert` performs a native buffered file copy. It does not perform codec transcoding yet.

## ⚡ Performance

MFlow focuses on eliminating unnecessary work instead of simply increasing the number of threads.

Future benchmarks should document the MFlow version, operating system, CPU, GPU, RAM, compiler, input media, output format and processing parameters.

Performance claims should be backed by reproducible measurements.

## 🧩 Native architecture

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

The next steps are real `Packet`, `Stream` and `Frame` models, followed by native parsers, demuxers and muxers.

## 🗺️ Roadmap

### v0.3.x

- Packet model
- Stream model
- timestamps
- improved probing
- stability and tests
- real media benchmarks

### v0.4.x

- native MP4 parser
- MP4 demuxer/muxer
- metadata
- audio/video stream model

### v0.5.x

- frame system
- pixel formats
- audio sample formats
- first native codec implementations

### Later

- H.264 / H.265 / AV1
- AAC / Opus
- MKV / WebM
- zero-copy processing
- GPU processing
- pipeline fusion
- asynchronous I/O
- hardware acceleration

Intermediate releases such as `v0.3.1`, `v0.3.2` and beyond will add functionality incrementally while preserving the native architecture.

## 🧪 Testing

```bash
ctest --test-dir build --output-on-failure
```

MFlow is intended to remain buildable and testable on both Windows and Linux.

## 🤝 Contributing

Contributions are welcome. Keep the architecture modular, add tests for behavior changes and provide reproducible benchmarks for performance-related changes.

## 🔐 Independence

MFlow is designed to operate without FFmpeg or another external multimedia executable. Unsupported features are rejected explicitly rather than silently falling back to an external dependency.

## 📜 License

MFlow is distributed under the MIT License.

---

**MFlow v0.3.0 — Native media engine foundation.**
