# Changelog

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
