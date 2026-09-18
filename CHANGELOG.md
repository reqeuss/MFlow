# Changelog

All notable MFlow releases are documented here.

## 0.4.1 — 2026-09-18

### User-local installation

MFlow can now be installed for the current user without administrator privileges.

### Added

- Windows installer script at `scripts/install-windows.ps1`
- Linux installer script at `scripts/install-linux.sh`
- Windows installation under `%LOCALAPPDATA%\\MFlow\\bin`
- Linux installation under `~/.local/bin`
- Automatic Windows user PATH registration
- Current PowerShell PATH update after Windows installation
- CMake user-local installation support
- Lightweight installation that builds only the MFlow CLI

### Usage

After installation, MFlow can be launched from any directory:

```text
mflow version
mflow info
mflow probe input.mp4
mflow convert input.mp4 output.mp4
```

### Independence

The installation system does not add or require FFmpeg or another external multimedia executable.

### Scope

This release changes the distribution and installation workflow. It does not add native codec decoding/encoding or native MP4 demuxing/muxing.

## 0.4.0 — 2026-09-18

### Native packet and stream engine

MFlow 0.4.0 introduces the first reusable native media data model. This release establishes packets, streams, timestamps, queues and a media context without relying on an external multimedia backend.

### Added

- Native Packet model with stream ID, PTS, DTS, duration and flags
- Native Timestamp model with rational timebases and second conversion
- Native Stream model for video, audio and data streams
- Native PacketQueue with thread-safe push, pop, peek, clear and size operations
- Native MediaContext for containers, streams, duration and packet ownership
- Pipeline now uses the shared native packet model
- Unit coverage for packet, stream, timestamp, queue and context behavior
- C++20 build integration for the new stream implementation

### Independence

The new media model is implemented entirely inside MFlow. It does not invoke FFmpeg or another external multimedia executable.

### Scope

This release does not claim native codec decoding, encoding, demuxing or muxing yet. The new abstractions are the foundation required to implement those systems incrementally.

## 0.3.0 — 2026-09-17

### Native media foundation

MFlow 0.3.0 removes the external media-backend execution path and establishes a built-in native media operation layer.

### Added

- Native media engine status in `mflow info`
- Native file/stream copy operation through `mflow convert`
- 1 MiB buffered I/O for the native copy path
- Explicit rejection of codec and scaling requests that are not implemented natively yet
- Cross-platform C++20 build target for Windows and Linux
- Native media probing for MP4-family, Matroska/WebM-family, WAV, MP3 and Ogg signatures
- Existing scheduler, pipeline, memory and benchmark foundations retained

### Independence

MFlow does not invoke or require an external multimedia executable for the v0.3 native path.

This release deliberately does not claim native codec transcoding yet.

## 0.2.0 — Historical

### Development milestone

v0.2.0 was an intermediate development milestone before MFlow moved to the fully native media-engine direction in v0.3.0.

The historical v0.2.x work included early media conversion/CLI experimentation. Parts of that work relied on an external media backend and are therefore not part of the current MFlow architecture.

### Important

The current project direction is native-only: MFlow does not use FFmpeg or another external multimedia executable for media processing. Historical v0.2.x backend-dependent work should not be interpreted as the architecture of current or future releases.

## 0.1.0 — 2026-09-16

### Foundation release

MFlow 0.1.0 established the initial C++20 engine foundation.

### Added

- Cross-platform CMake project structure
- Core scheduler and worker execution foundation
- Pipeline and stage abstraction
- Memory/buffer foundation
- System and platform information
- CLI foundation
- Benchmark executable
- Example pipeline
- Initial automated tests
- Windows/Linux-oriented build foundation

### Initial architecture

The first release focused on creating a small, modular and measurable engine core that could later support native media processing.

### Scope

v0.1.0 did not provide a complete native multimedia codec or container engine. It was the foundation for the later native media work.
