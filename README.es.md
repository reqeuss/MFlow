# MFlow

> **Mueve menos datos. Haz menos trabajo. Mide todo.**

[🇬🇧 English](README.md) · [🇫🇷 Français](README.fr.md) · [🇪🇸 Español](README.es.md) · [🇩🇪 Deutsch](README.de.md)

> 🚧 **Versión actual: v0.4.1** — instalación para el usuario y comando global `mflow`. Los demuxers, muxers y codecs nativos siguen en desarrollo.

## 🧭 Hub del repositorio

El [README principal en inglés](README.md) es el hub del repositorio: instalación, CLI, arquitectura, base actual, roadmap, releases y documentación.

## 🚀 Instalación

### Windows

```powershell
Set-ExecutionPolicy -Scope CurrentUser RemoteSigned
.\scripts\install-windows.ps1
```

Instala MFlow en `%LOCALAPPDATA%\MFlow\bin` y añade esta carpeta al PATH del usuario.

### Linux

```bash
chmod +x scripts/install-linux.sh
./scripts/install-linux.sh
```

Instala MFlow en `~/.local/bin`.

Después:

```text
mflow version
mflow info
```

El comando funciona desde cualquier directorio.

## 🖥️ CLI

```text
mflow version
mflow info
mflow probe <file>
mflow convert <input> <output> [--no-overwrite]
mflow pipeline-demo
mflow benchmark
```

`convert` utiliza actualmente la copia nativa de MFlow. Todavía no realiza transcodificación general de codecs.

## 🧠 Arquitectura

MFlow busca construir una stack multimedia nativa e independiente:

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

Principio:

> **No proceses lo que no necesitas procesar.**

## 🧩 Base nativa actual

v0.4.x proporciona:

- `Packet`
- `Stream`
- `Timestamp`
- `PacketQueue`
- `MediaContext`
- pipeline
- scheduler
- fundamentos de memoria
- probing multimedia nativo
- instalación para usuarios en Windows/Linux

### Todavía no implementado

- decodificación/codificación H.264, H.265, AV1
- decodificación/codificación AAC, Opus
- demuxer/muxer MP4 nativos
- transcodificación general
- escalado de vídeo
- pipelines de codecs mediante GPU

Las operaciones no disponibles se rechazan explícitamente en lugar de delegarse a FFmpeg u otro ejecutable externo.

## 🗺️ Roadmap

### v0.4.x — Fundamentos multimedia

- [x] Packet
- [x] Stream
- [x] Timestamp
- [x] PacketQueue
- [x] MediaContext
- [x] Instalación para usuarios
- [ ] Normalización de timestamps
- [ ] Parser MP4 nativo
- [ ] Demuxer MP4 nativo
- [ ] Muxer MP4 nativo
- [ ] Frames de vídeo nativos
- [ ] Muestras de audio nativas

### v0.5.x — Fundamentos de codecs

- interfaces de codecs
- formatos de píxel
- formatos de audio
- abstracciones decoder/encoder
- primeros codecs nativos limitados

### Más adelante

H.264, H.265, AV1, AAC, Opus, MKV/WebM, zero-copy, GPU, aceleración por hardware, I/O asíncrono y planificación avanzada.

## 📦 Versiones

| Versión | Enfoque |
|---|---|
| **v0.4.1** | Instalación para usuarios y comando global |
| **v0.4.0** | Packet, Stream, Timestamp y MediaContext |
| **v0.3.0** | Base del motor multimedia nativo |
| **v0.2.0** | Milestone histórico de desarrollo |
| **v0.1.0** | Base C++, scheduler, pipeline y CLI |

Consulta [CHANGELOG.md](CHANGELOG.md) para el historial completo.

## 🧪 Desarrollo

Requisitos: CMake 3.20+, compilador C++20, Git, Windows o Linux.

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

## 📁 Estructura

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

## 🔐 Independencia

MFlow está diseñado para convertirse en una stack multimedia independiente. Las funciones no implementadas no se sustituyen silenciosamente por una dependencia externa.

## 📜 Licencia

MIT.

---

**MFlow v0.4.1** · Native multimedia engine · C++20
