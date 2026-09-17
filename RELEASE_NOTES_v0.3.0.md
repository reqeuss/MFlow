# MFlow v0.3.0 — Native Media Engine Foundation 🚀

MFlow v0.3.0 marks the first native-engine milestone of the project.

The project is moving toward a fully independent multimedia engine written in C++20, designed to process media without delegating work to FFmpeg or another external multimedia executable.

## ✨ Highlights

- 🧩 Native media-engine foundation
- 🚫 No FFmpeg dependency or external multimedia executable
- 🖥️ Windows and Linux support
- 🔎 Native media/file probing foundation
- 🧵 Parallel execution scheduler
- 💾 Buffer and memory-management foundation
- 🔄 Native stream/file copy path
- 💻 Cross-platform C++20 CLI
- 🧪 Automated tests
- 📊 Benchmarks and pipeline examples
- 🌍 English, French, Spanish and German documentation

## 🧠 Core philosophy

> **Move less data. Do less work. Measure everything.**

MFlow is being designed to analyze the requested result before executing the processing graph. The long-term goal is to avoid unnecessary decoding, encoding, memory allocations, data copies, CPU/GPU transfers and disk I/O whenever the requested operation does not require them.

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

## ✅ Available in v0.3.0

- Platform and architecture detection
- Hardware-thread detection
- Basic media/file probing
- Detection of common media/container families
- Native pipeline execution
- Parallel scheduler
- Buffer management foundation
- Native binary stream/file copy
- CLI commands for version, system information, probing, conversion, pipeline demonstration and benchmarking
- Windows and Linux build support

## ⚠️ Current limitations

v0.3.0 is **not yet a complete multimedia transcoder**.

Native codec encoding/decoding for formats such as H.264, H.265, AV1, AAC and Opus is not yet implemented. Native container parsers, demuxers and muxers are also still being developed incrementally.

When an unsupported codec or resize operation is requested, MFlow explicitly reports that the operation is not implemented instead of silently delegating the work to an external executable.

The current conversion path is a native binary stream/file copy, not a codec transcode.

## 🏗️ Architecture direction

The v0.3.x series will progressively introduce the internal media model required for real native processing:

- Packet model
- Stream model
- Timestamp handling
- Frame model
- Native container parsing
- Native demuxing/muxing
- Audio sample representation
- Pixel formats
- Native codec foundations

## 🗺️ Roadmap

### v0.3.x

- Packet system
- Stream system
- Timestamp system
- Improved probing
- Native media fixtures
- Media-specific benchmarks
- Stability improvements

### v0.4.x

- Native MP4 parser
- MP4 demuxer
- MP4 muxer
- Metadata handling
- Stream/container integration

### v0.5.x and beyond

- Frame system
- Audio sample system
- Native codec implementations
- Zero-copy execution
- Pipeline fusion
- Asynchronous I/O
- Hardware acceleration
- GPU-native processing paths

## 🔨 Build

### Windows

```powershell
cmake -S . -B build
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
```

### Linux

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
ctest --test-dir build --output-on-failure
```

## 💻 CLI

```text
mflow version
mflow info
mflow probe <file>
mflow convert <input> <output> [--no-overwrite]
mflow pipeline-demo
mflow benchmark
```

## 📦 Release source archives

GitHub will automatically provide source archives for the `v0.3.0` tag:

- `MFlow-v0.3.0.zip`
- `MFlow-v0.3.0.tar.gz`

These archives contain the source tree for the exact tagged commit.

## 🧪 CI

The latest `main` commit used for this release preparation has a successful GitHub Actions CI run across the configured build matrix.

## 📜 License

MFlow is released under the MIT License.

---

**MFlow v0.3.0** — Native Media Engine Foundation.