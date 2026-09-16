# Changelog

## 0.2.0 — 2026-09-16

First MFlow release with a real media conversion command.

### Added

- Media conversion API
- External media backend detection
- `mflow convert <input> <output>`
- Video codec selection
- Audio codec selection
- Video scaling
- Safe no-overwrite mode
- Conversion backend status in `mflow info`
- Converter API test coverage

### Architecture

The conversion backend is isolated behind `MediaConverter`, keeping the MFlow pipeline and scheduler independent from the backend implementation.

### Next

- Stream-level planning
- Native media backend integration
- Better metadata and timestamp handling
- Buffer lifetime optimization
- Zero-copy paths
- Hardware acceleration
- Real media benchmarks
