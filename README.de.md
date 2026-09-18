# MFlow

> **Weniger Daten bewegen. Weniger Arbeit machen. Alles messen.**

[🇬🇧 English](README.md) · [🇫🇷 Français](README.fr.md) · [🇪🇸 Español](README.es.md) · [🇩🇪 Deutsch](README.de.md)

> 🚧 **Aktuelle Version: v0.4.1** — Benutzerinstallation und globaler `mflow`-Befehl. Native Demuxer, Muxer und Codecs befinden sich noch in Entwicklung.

## 🧭 Repository-Hub

Das [englische Haupt-README](README.md) ist der Repository-Hub: Installation, CLI, Architektur, aktueller Stand, Roadmap, Releases und Dokumentation.

## 🚀 Installation

### Windows

```powershell
Set-ExecutionPolicy -Scope CurrentUser RemoteSigned
.\scripts\install-windows.ps1
```

MFlow wird unter `%LOCALAPPDATA%\MFlow\bin` installiert und dieser Ordner zum Benutzer-PATH hinzugefügt.

### Linux

```bash
chmod +x scripts/install-linux.sh
./scripts/install-linux.sh
```

MFlow wird unter `~/.local/bin` installiert.

Danach:

```text
mflow version
mflow info
```

Der Befehl funktioniert aus jedem Verzeichnis.

## 🖥️ CLI

```text
mflow version
mflow info
mflow probe <file>
mflow convert <input> <output> [--no-overwrite]
mflow pipeline-demo
mflow benchmark
```

`convert` verwendet derzeit den nativen Kopierpfad von MFlow. Allgemeines Codec-Transcoding ist noch nicht implementiert.

## 🧠 Architektur

MFlow soll eine unabhängige native Multimedia-Stack werden:

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

Prinzip:

> **Bearbeite nichts, was nicht benötigt wird.**

## 🧩 Aktuelle native Grundlage

v0.4.x enthält:

- `Packet`
- `Stream`
- `Timestamp`
- `PacketQueue`
- `MediaContext`
- Pipeline
- Scheduler
- Grundlagen der Speicherverwaltung
- natives Media-Probing
- Benutzerinstallation für Windows/Linux

### Noch nicht implementiert

- H.264-, H.265- und AV1-Decodierung/-Codierung
- AAC- und Opus-Decodierung/-Codierung
- nativer MP4-Demuxer/Muxer
- allgemeines Audio-/Video-Transcoding
- Videoskalierung
- GPU-Codec-Pipelines

Nicht verfügbare Operationen werden ausdrücklich abgelehnt, statt an FFmpeg oder ein anderes externes Programm delegiert zu werden.

## 🗺️ Roadmap

### v0.4.x — Mediengrundlagen

- [x] Packet
- [x] Stream
- [x] Timestamp
- [x] PacketQueue
- [x] MediaContext
- [x] Benutzerinstallation
- [ ] Timestamp-Normalisierung
- [ ] nativer MP4-Parser
- [ ] nativer MP4-Demuxer
- [ ] nativer MP4-Muxer
- [ ] native Video-Frames
- [ ] Audio-Samples

### v0.5.x — Codec-Grundlagen

- Codec-Schnittstellen
- Pixelformate
- Audioformate
- Decoder-/Encoder-Abstraktionen
- erste eingeschränkte native Codecs

### Später

H.264, H.265, AV1, AAC, Opus, MKV/WebM, Zero-Copy, GPU, Hardwarebeschleunigung, asynchrones I/O und erweitertes Planning.

## 📦 Versionen

| Version | Schwerpunkt |
|---|---|
| **v0.4.1** | Benutzerinstallation und globaler Befehl |
| **v0.4.0** | Packet, Stream, Timestamp und MediaContext |
| **v0.3.0** | Native Multimedia-Engine-Grundlage |
| **v0.2.0** | Historischer Entwicklungsmeilenstein |
| **v0.1.0** | C++-Grundlage, Scheduler, Pipeline und CLI |

Siehe [CHANGELOG.md](CHANGELOG.md) für die vollständige Historie.

## 🧪 Entwicklung

Voraussetzungen: CMake 3.20+, C++20-Compiler, Git, Windows oder Linux.

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

## 📁 Projektstruktur

```text
MFlow/
├── .github/
├── benchmarks/
├── cli/
├── core/
├── docs/
├── examples/
├── scripts/
├── tests/
├── CMakeLists.txt
├── CHANGELOG.md
├── LICENSE
└── README*.md
```

## 🔐 Unabhängigkeit

MFlow soll zu einer unabhängigen Multimedia-Stack werden. Nicht implementierte Funktionen werden nicht stillschweigend durch externe Abhängigkeiten ersetzt.

## 📜 Lizenz

MIT.

---

**MFlow v0.4.1** · Native multimedia engine · C++20
