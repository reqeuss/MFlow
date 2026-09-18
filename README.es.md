# MFlow

> **Mueve menos datos. Haz menos trabajo. Mide todo.**

MFlow es un motor multimedia nativo, local y de código abierto escrito en C++20.

## 🚀 v0.4.0

MFlow 0.4.0 introduce el primer modelo multimedia nativo reutilizable: paquetes, streams, timestamps, colas de paquetes y contexto multimedia. No se utiliza ningún ejecutable multimedia externo.

### What works

La base nativa de paquetes, streams y timestamps ya está disponible. La decodificación/codificación de codecs y los demuxers/muxers completos se implementarán progresivamente.


### Funciona actualmente

- Detección de plataforma y arquitectura
- Análisis ligero de archivos multimedia
- Detección de familias MP4, Matroska/WebM, WAV, MP3 y Ogg
- Pipeline de ejecución
- Scheduler paralelo
- Fundamentos de gestión de buffers
- Copia nativa de archivos/streams
- CLI para Windows y Linux
- Tests y benchmarks

### Todavía no implementado

El transcodificado completo de codecs todavía no está disponible. MFlow aún no implementa codificación/decodificación nativa completa de H.264, H.265, AV1, AAC u Opus.

Las operaciones no implementadas se rechazan explícitamente.

## 🔨 Compilación

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

La operación `convert` de v0.3.0 realiza una copia nativa con I/O por bloques. El transcodificado se añadirá cuando esté implementado de forma nativa.

## 🗺️ Roadmap

- v0.3.x: paquetes, streams, timestamps, probing y estabilidad
- v0.4.x: parser, demuxer y muxer MP4 nativos
- v0.5.x: frames, formatos de píxel/audio y primeros codecs nativos
- Más adelante: H.264, H.265, AV1, AAC, Opus, MKV/WebM, zero-copy, GPU e I/O asíncrono

## 📜 Licencia

MIT.

[Français](README.md) · [English](README.en.md) · [Deutsch](README.de.md)
