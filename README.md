# MFlow

> **Move less data. Do less work. Measure everything.**

MFlow est un moteur multimédia open source, local et natif écrit en C++20.

L'objectif est de construire une alternative indépendante aux outils multimédias classiques, avec une architecture capable de décider quelles opérations sont réellement nécessaires avant de traiter les données.

## 🌍 Langues

- 🇫🇷 Français — ce README
- 🇬🇧 [English](README.en.md)
- 🇪🇸 [Español](README.es.md)
- 🇩🇪 [Deutsch](README.de.md)

## 🚀 v0.3.0

MFlow 0.3.0 pose les premières bases du moteur multimédia natif.

**MFlow n'a pas besoin d'un exécutable multimédia externe.** Le chemin natif actuel est intégré directement au projet.

### Ce qui fonctionne

- Détection de plateforme et architecture
- Analyse légère de fichiers média
- Détection des familles MP4, Matroska/WebM, WAV, MP3 et Ogg
- Pipeline d'exécution
- Scheduler parallèle
- Gestion de buffers
- Copie native de fichiers/flux
- CLI Windows et Linux
- Tests et benchmarks

### Ce qui n'est pas encore implémenté

La conversion codec complète n'est pas encore disponible. MFlow ne prétend donc pas encoder ou décoder nativement H.264, H.265, AV1, AAC, Opus, etc. dans cette version.

Une demande de codec ou de redimensionnement non supportée est refusée explicitement au lieu d'être déléguée à un programme externe.

## 🧠 Philosophie

MFlow est conçu autour d'une règle simple :

> **Ne traite pas ce dont tu n'as pas besoin.**

À terme, le planner pourra déterminer si une opération nécessite :

- un décodage ;
- un encodage ;
- une conversion de format ;
- une copie directe de flux ;
- une allocation mémoire supplémentaire ;
- un transfert CPU/GPU ;
- ou aucune de ces opérations.

Architecture visée :

```text
INPUT
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

## 📦 Arborescence

```text
MFlow/
├── core/
│   ├── include/mflow/
│   └── src/
├── cli/
├── tests/
├── benchmarks/
├── examples/
├── docs/
├── CMakeLists.txt
├── README.md
├── README.en.md
├── README.es.md
├── README.de.md
├── CHANGELOG.md
└── LICENSE
```

## 🔨 Compilation

### Windows

Pré-requis : CMake 3.20+, un compilateur C++20 compatible et Git.

```powershell
cmake -S . -B build
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
```

Avec Ninja, les exécutables sont généralement directement dans `build/`.

```powershell
.\build\mflow.exe version
.\build\mflow.exe info
```

### Linux

Pré-requis : CMake 3.20+, un compilateur C++20 et Git.

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
ctest --test-dir build --output-on-failure
```

Puis :

```bash
./build/mflow version
./build/mflow info
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

### Informations système

```text
mflow info
```

Affiche notamment la plateforme, l'architecture, le nombre de threads et le statut du moteur média natif.

### Analyser un fichier

```text
mflow probe input.mp4
```

MFlow inspecte actuellement les signatures de conteneurs/fichiers connues sans lancer de programme externe.

### Copie native

```text
mflow convert input.mp4 backup.mp4
```

Dans v0.3.0, cette commande utilise le chemin natif de copie. Elle ne réalise pas encore de transcodage codec.

Pour empêcher l'écrasement :

```text
mflow convert input.mp4 backup.mp4 --no-overwrite
```

## ⚡ Performance

MFlow vise une réduction du travail inutile plutôt qu'une simple augmentation du nombre de threads.

Les futurs benchmarks devront préciser :

- version de MFlow ;
- système d'exploitation ;
- CPU ;
- GPU ;
- RAM ;
- compilateur ;
- fichier d'entrée ;
- format de sortie ;
- paramètres de traitement.

Aucune comparaison de performances sérieuse ne doit être publiée sans mesures reproductibles.

## 🧩 Architecture native

Les composants sont séparés pour permettre une évolution progressive :

```text
Media Probe
    ↓
Stream Model
    ↓
Planner
    ↓
Pipeline / Scheduler
    ↓
Decoder / Filter / Encoder
    ↓
Muxer
```

La prochaine étape consiste à développer de vrais modèles `Packet`, `Stream` et `Frame`, puis les parseurs/demuxers/muxers natifs.

## 🗺️ Roadmap

### v0.3.x

- stabilité ;
- tests supplémentaires ;
- modèle Packet ;
- modèle Stream ;
- timestamps ;
- amélioration du probe ;
- benchmarks média réels.

### v0.4.x

- parseur MP4 natif ;
- demuxer/muxer MP4 ;
- métadonnées ;
- audio/video stream model.

### v0.5.x

- frames ;
- formats pixel ;
- formats audio ;
- premières implémentations codec natives.

### Plus tard

- H.264 / H.265 / AV1 ;
- AAC / Opus ;
- MKV/WebM ;
- zero-copy ;
- GPU ;
- pipeline fusion ;
- I/O asynchrone ;
- accélération matérielle.

Les versions intermédiaires (`v0.3.1`, `v0.3.2`, etc.) serviront à intégrer progressivement ces fonctionnalités sans casser la base stable.

## 🧪 Tests

```bash
ctest --test-dir build --output-on-failure
```

Le projet doit rester compilable et testable sur Windows et Linux.

## 🤝 Contribution

Les contributions sont les bienvenues. Pour une modification importante, privilégiez une architecture modulaire, des tests et, lorsqu'il s'agit de performance, un benchmark reproductible.

## 🔐 Indépendance

MFlow est conçu pour fonctionner sans dépendre d'un exécutable multimédia externe. Les fonctionnalités non encore implémentées sont refusées explicitement plutôt que remplacées silencieusement par une dépendance externe.

## 📜 Licence

MFlow est distribué sous licence MIT.

---

**MFlow v0.3.0** — Native media engine foundation.
