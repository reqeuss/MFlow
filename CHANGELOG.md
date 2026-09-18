# Changelog

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

### Next

- Timestamp normalization and ordering
- Native MP4 box parser
- MP4 demuxer
- MP4 muxer
- Raw frame and audio sample abstractions
- Native codec foundations

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

This release deliberately does not claim native codec transcoding yet. Codec, demuxer and muxer implementations will be introduced incrementally in later releases.

### Next

- Packet and stream models
- Native MP4 box parser
- Native demux/mux interfaces
- Timestamp and metadata handling
- Raw frame/audio abstractions
- Native codec implementations
- Zero-copy buffer planning
- Hardware acceleration abstractions
