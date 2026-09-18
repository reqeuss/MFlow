# MFlow

> **Déplacer moins de données. Faire moins de travail. Tout mesurer.**

[🇬🇧 English](README.md) · [🇫🇷 Français](README.fr.md) · [🇪🇸 Español](README.es.md) · [🇩🇪 Deutsch](README.de.md)

> 🚧 **Version actuelle : v0.4.1** — installation utilisateur et commande globale `mflow`. Les demuxers, muxers et codecs natifs sont encore en développement.

## 🧭 Hub du dépôt

Le [README principal en anglais](README.md) est le hub du dépôt : installation, CLI, architecture, fondations actuelles, roadmap, releases et documentation.

## 🚀 Installation

### Windows

```powershell
Set-ExecutionPolicy -Scope CurrentUser RemoteSigned
.\scripts\install-windows.ps1
```

Installe MFlow dans `%LOCALAPPDATA%\MFlow\bin` et ajoute ce dossier au PATH utilisateur.

### Linux

```bash
chmod +x scripts/install-linux.sh
./scripts/install-linux.sh
```

Installe MFlow dans `~/.local/bin`.

Après installation :

```text
mflow version
mflow info
```

La commande fonctionne depuis n'importe quel répertoire.

## 🖥️ CLI

```text
mflow version
mflow info
mflow probe <file>
mflow convert <input> <output> [--no-overwrite]
mflow pipeline-demo
mflow benchmark
```

`convert` utilise actuellement le chemin de copie native de MFlow. Il ne réalise pas encore de transcodage général de codecs.

## 🧠 Architecture

MFlow vise une stack multimédia native indépendante :

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

Principe :

> **Ne traite pas ce dont tu n'as pas besoin.**

À terme, MFlow doit éviter les décodages, encodages, copies mémoire et transferts CPU/GPU inutiles.

## 🧩 Fondations actuelles

v0.4.x fournit notamment :

- `Packet`
- `Stream`
- `Timestamp`
- `PacketQueue`
- `MediaContext`
- pipeline
- scheduler
- fondations mémoire
- probing média natif
- installation utilisateur Windows/Linux

### Pas encore implémenté

- décodage/encodage H.264, H.265, AV1
- décodage/encodage AAC, Opus
- demuxer/muxer MP4 natifs
- transcodage audio/vidéo général
- redimensionnement vidéo
- pipelines codecs GPU

Les opérations non disponibles sont refusées explicitement au lieu d'être déléguées à FFmpeg ou à un autre exécutable externe.

## 🗺️ Roadmap

### v0.4.x — Fondations média

- [x] Packet
- [x] Stream
- [x] Timestamp
- [x] PacketQueue
- [x] MediaContext
- [x] Installation utilisateur
- [ ] Normalisation des timestamps
- [ ] Parseur MP4 natif
- [ ] Demuxer MP4 natif
- [ ] Muxer MP4 natif
- [ ] Frames vidéo natives
- [ ] Échantillons audio natifs

### v0.5.x — Fondations codecs

- interfaces de codecs
- formats de pixels
- formats audio
- abstractions decoder/encoder
- premiers codecs natifs contraints

### Plus tard

H.264, H.265, AV1, AAC, Opus, MKV/WebM, zero-copy, GPU, accélération matérielle, I/O asynchrone et planner avancé.

## 📦 Versions

| Version | Focus |
|---|---|
| **v0.4.1** | Installation utilisateur et commande globale |
| **v0.4.0** | Packet, Stream, Timestamp et MediaContext |
| **v0.3.0** | Fondation du moteur média natif |
| **v0.2.0** | Milestone historique de développement |
| **v0.1.0** | Fondation C++, scheduler, pipeline et CLI |

Voir [CHANGELOG.md](CHANGELOG.md) pour l'historique complet.

## 🧪 Développement

Prérequis : CMake 3.20+, compilateur C++20, Git, Windows ou Linux.

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

## 📁 Structure

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

## 🔐 Indépendance

MFlow est conçu pour devenir une stack multimédia indépendante. Les fonctionnalités non implémentées ne sont pas remplacées silencieusement par une dépendance externe.

## 📜 Licence

MIT.

---

**MFlow v0.4.1** · Native multimedia engine · C++20
