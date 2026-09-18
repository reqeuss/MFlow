# MFlow

> **Weniger Daten bewegen. Weniger Arbeit machen. Alles messen.**

MFlow ist eine lokale, Open-Source-Multimedia-Engine in nativem C++20.

## 🚀 v0.4.0

MFlow 0.4.0 führt das erste wiederverwendbare native Medienmodell ein: Pakete, Streams, Zeitstempel, Paketwarteschlangen und Media Context. Es wird kein externes Multimedia-Programm verwendet.

### What works

Die native Grundlage für Pakete, Streams und Zeitstempel ist jetzt vorhanden. Codec-Decodierung/-Codierung sowie vollständige Demuxer/Muxer werden schrittweise implementiert.


### Aktuell verfügbar

- Plattform- und Architektur-Erkennung
- Leichte Medien-Dateianalyse
- Erkennung von MP4-, Matroska/WebM-, WAV-, MP3- und Ogg-Familien
- Pipeline-Ausführung
- Paralleler Scheduler
- Grundlagen der Buffer-Verwaltung
- Native Datei-/Stream-Kopie
- CLI für Windows und Linux
- Tests und Benchmarks

### Noch nicht implementiert

Vollständiges Codec-Transcoding ist noch nicht verfügbar. Native vollständige H.264-, H.265-, AV1-, AAC- oder Opus-Codierung/Decodierung ist noch nicht Bestandteil dieser Version.

Nicht implementierte Operationen werden ausdrücklich abgelehnt.

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

## 🖥️ CLI

```text
mflow version
mflow info
mflow probe <file>
mflow convert <input> <output> [--no-overwrite]
mflow pipeline-demo
mflow benchmark
```

`convert` verwendet in v0.3.0 eine native gepufferte Kopie. Codec-Transcoding wird erst hinzugefügt, wenn es vollständig nativ implementiert ist.

## 🗺️ Roadmap

- v0.3.x: Pakete, Streams, Zeitstempel, Probing und Stabilität
- v0.4.x: nativer MP4-Parser, Demuxer und Muxer
- v0.5.x: Frames, Pixel-/Audioformate und erste native Codecs
- Später: H.264, H.265, AV1, AAC, Opus, MKV/WebM, Zero-Copy, GPU und asynchrones I/O

## 📜 Lizenz

MIT.

[Français](README.md) · [English](README.en.md) · [Español](README.es.md)
