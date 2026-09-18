# MFlow

> **Move less data. Do less work. Measure everything.**

**MFlow is an open-source native multimedia engine written in C++20.**

MFlow is being built as an independent multimedia stack. The long-term goal is to handle media containers, packets, streams, timestamps, frames, codecs, filters, scheduling and muxing inside MFlow rather than delegating media work to an external multimedia executable.

> 🚧 **Status:** MFlow is under active development. **v0.4.1** focuses on user-local installation and distribution. Native demuxing, muxing and codec implementations are still in development.

---

## 🧭 Repository Hub

This README is the **main entry point for the GitHub repository**.

| Section | Purpose |
|---|---|
| 🚀 [Getting Started](#-getting-started) | Install, build and run MFlow |
| 🖥️ [CLI](#️-cli) | Available commands |
| 🧠 [Architecture](#-architecture) | Understand how MFlow is designed |
| 🧩 [Current Foundation](#-current-native-foundation) | See what exists today |
| 🗺️ [Roadmap](#️-roadmap) | Follow future development |
| 📦 [Releases](#-releases) | Version milestones |
| 🧪 [Development](#-development) | Build and test the project |
| 📖 [Documentation](#-documentation) | Technical documentation |
| 🌍 [Languages](#-languages) | Translated READMEs |
| 📜 [Changelog](CHANGELOG.md) | Detailed version history |

### 📁 Repository map

- **[core/](core/)** — native MFlow engine and public C++ interfaces
- **[cli/](cli/)** — command-line interface
- **[tests/](tests/)** — automated tests
- **[benchmarks/](benchmarks/)** — performance benchmarks
- **[examples/](examples/)** — example programs
- **[docs/](docs/)** — technical documentation
- **[scripts/](scripts/)** — installation and development scripts
- **[.github/](.github/)** — CI and repository automation

---

## 🚀 Getting Started

### Windows — install MFlow globally for your user

No administrator account is required.

From the repository in PowerShell:

```powershell
Set-ExecutionPolicy -Scope CurrentUser RemoteSigned
.\scripts\install-windows.ps1
```

The installer builds MFlow and installs:

```text
%LOCALAPPDATA%\MFlow\bin\mflow.exe
```

It also adds the directory to the current user's PATH.

Then open a new terminal if necessary:

```powershell
mflow version
mflow info
```

You can now run `mflow` from **any directory**.

### Linux — install MFlow globally for your user

```bash
chmod +x scripts/install-linux.sh
./scripts/install-linux.sh
```

The executable is installed under:

```text
~/.local/bin/mflow
```

If required:

```bash
export PATH="$HOME/.local/bin:$PATH"
```

Then:

```bash
mflow version
mflow info
```

### Build manually

Windows:

```powershell
cmake -S . -B build
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
```

Linux:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
ctest --test-dir build --output-on-failure
```

---

## 🖥️ CLI

After installation:

```text
mflow version
mflow info
mflow probe <file>
mflow convert <input> <output> [--no-overwrite]
mflow pipeline-demo
mflow benchmark
```

The current `convert` operation provides MFlow's native stream-copy path. It does not yet perform general codec transcoding.

---

## 🧠 Architecture

MFlow is **not intended to be a thin wrapper around FFmpeg or another multimedia executable**.

The target architecture is:

```text
INPUT
  ↓
DEMUX
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

The planner should eventually determine the minimum amount of work required.

For a container-only change:

```text
MP4
 ↓
H.264 packets
 ↓
Remux
 ↓
MP4
```

No decode or encode should be necessary when the streams are already compatible.

For a resize:

```text
DEMUX → DECODE → RESIZE → ENCODE → MUX
```

The core principle is:

> **Move less data. Do less work. Measure everything.**

---

## 🧩 Current Native Foundation

MFlow currently provides reusable native abstractions for:

- **Packet** — packet data, stream ID, PTS, DTS, duration and flags
- **Stream** — video, audio and data stream metadata
- **Timestamp** — rational timebases and time conversion
- **PacketQueue** — thread-safe packet buffering
- **MediaContext** — container, streams, duration and packet ownership
- **Pipeline** — processing stages operating on MFlow packets
- **Scheduler** — parallel task execution
- **Memory** — reusable buffer infrastructure
- **Media probing** — lightweight native file/container detection

### Not implemented yet

MFlow does not currently claim full native support for:

- H.264 / H.265 / AV1 decoding or encoding
- AAC / Opus decoding or encoding
- Native MP4 demuxing/muxing
- General audio/video transcoding
- Video scaling
- GPU codec pipelines

Unsupported operations are explicitly rejected instead of silently falling back to an external multimedia executable.

---

## 🗺️ Roadmap

### v0.4.x — Media foundations

- [x] Packet model
- [x] Stream model
- [x] Timestamp model
- [x] Packet queue
- [x] Media context
- [x] User-local installation
- [ ] Timestamp normalization and ordering
- [ ] Native MP4 box parser
- [ ] Native MP4 demuxer
- [ ] Native MP4 muxer
- [ ] Raw video frame system
- [ ] Audio sample system

### v0.5.x — Codec foundations

- Native codec interfaces
- Pixel formats
- Audio sample formats
- Decoder/encoder abstractions
- First constrained native codec implementations

### Future

- H.264
- H.265
- AV1
- AAC
- Opus
- MKV/WebM
- Zero-copy processing
- GPU pipelines
- Hardware acceleration
- Asynchronous I/O
- Pipeline fusion
- Advanced stream planning

Each milestone should add a real reusable engine capability.

---

## 📦 Releases

| Version | Focus |
|---|---|
| **v0.4.1** | User-local installation and global `mflow` command |
| **v0.4.0** | Native packet and stream foundation |
| **v0.3.0** | Native media engine foundation |
| **v0.1.0** | Core scheduler, pipeline and foundation |

See **[CHANGELOG.md](CHANGELOG.md)** for the detailed history.

---

## 🧪 Development

### Requirements

- CMake 3.20+
- C++20-compatible compiler
- Git
- Windows or Linux

### Tests

```bash
ctest --test-dir build --output-on-failure
```

### Repository structure

```text
MFlow/
├── .github/       CI and automation
├── benchmarks/    Performance benchmarks
├── cli/           Command-line interface
├── core/          Native MFlow engine
├── docs/          Technical documentation
├── examples/      Examples
├── scripts/       Install/development scripts
├── tests/         Automated tests
├── CMakeLists.txt
├── CHANGELOG.md
├── LICENSE
└── README*.md
```

---

## 📖 Documentation

The README is the repository hub. Detailed technical material belongs in **[docs/](docs/)**.

Recommended documentation areas:

- Architecture
- Media model
- Containers
- Codecs
- Pipeline planner
- Memory management
- Scheduler
- Hardware acceleration
- Performance
- Contributing

---

## 🌍 Languages

- 🇬🇧 **English — this README**
- 🇫🇷 [Français](README.fr.md)
- 🇪🇸 [Español](README.es.md)
- 🇩🇪 [Deutsch](README.de.md)

---

## 🤝 Contributing

Contributions are welcome.

For engine changes, prefer:

1. small modular changes;
2. tests for new behavior;
3. documented limitations;
4. reproducible benchmarks for performance claims;
5. no hidden external multimedia dependencies.

---

## 🔐 Independence

MFlow is designed to become an independent multimedia stack.

The project does not use FFmpeg as a hidden fallback for features that MFlow has not implemented. Unsupported native operations should fail explicitly until their own implementation is available.

---

## 📜 License

MFlow is released under the **MIT License**.

---

**MFlow v0.4.1** · Native multimedia engine · C++20
