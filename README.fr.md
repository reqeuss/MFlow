# MFlow

> **Déplacer moins de données. Faire moins de travail. Tout mesurer.**

MFlow est un moteur multimédia open source, local et natif écrit en C++20.

Le projet vise à construire un moteur multimédia indépendant, sans dépendre de FFmpeg ni d'un autre exécutable multimédia externe.

## 🌍 Langues

- 🇬🇧 [English](README.md)
- 🇫🇷 **Français — ce README**
- 🇪🇸 [Español](README.es.md)
- 🇩🇪 [Deutsch](README.de.md)

## 🚀 v0.3.0

MFlow 0.3.0 pose les premières bases du moteur multimédia natif.

**MFlow ne nécessite pas FFmpeg ni d'exécutable multimédia externe.** Le chemin média actuel est directement intégré au projet.

### Ce qui fonctionne

- Détection de la plateforme et de l'architecture
- Analyse légère des fichiers média
- Détection des familles MP4, Matroska/WebM, WAV, MP3 et Ogg
- Pipeline d'exécution natif
- Scheduler parallèle
- Gestion des buffers
- Copie native de fichiers/flux
- CLI Windows et Linux
- Tests et benchmarks

### Ce qui n'est pas encore implémenté

La conversion complète des codecs n'est pas encore disponible. MFlow ne prétend donc pas prendre en charge nativement l'encodage ou le décodage H.264, H.265, AV1, AAC, Opus ou de codecs similaires dans cette version.

Les demandes de codec ou de redimensionnement non prises en charge sont explicitement refusées au lieu d'être déléguées à un programme externe.

## 🧠 Philosophie

MFlow repose sur une règle simple :

> **Ne traite pas ce dont tu n'as pas besoin.**

À terme, le planner déterminera si une opération nécessite réellement :

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

## 📦 Structure du projet

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
├── README.fr.md
├── README.es.md
├── README.de.md
├── CHANGELOG.md
└── LICENSE
```

## 🔨 Compilation

### Windows

Prérequis : CMake 3.20+, un compilateur compatible C++20 et Git.

```powershell
cmake -S . -B build
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
```

Avec Ninja, les exécutables se trouvent généralement directement dans `build/`.

```powershell
.\build\mflow.exe version
.\build\mflow.exe info
```

### Linux

Prérequis : CMake 3.20+, un compilateur compatible C++20 et Git.

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

Affiche notamment la plateforme, l'architecture, le nombre de threads matériels et l'état du moteur média natif.

### Analyser un fichier

```text
mflow probe input.mp4
```

MFlow inspecte actuellement les signatures connues de conteneurs/fichiers sans lancer de programme externe.

### Copie native

```text
mflow convert input.mp4 backup.mp4
```

Dans v0.3.0, cette commande utilise le chemin de copie natif de MFlow. Elle ne réalise pas encore de transcodage de codec.

Pour empêcher l'écrasement d'un fichier existant :

```text
mflow convert input.mp4 backup.mp4 --no-overwrite
```

## ⚡ Performances

MFlow cherche avant tout à réduire le travail inutile plutôt qu'à augmenter simplement le nombre de threads.

Les futurs benchmarks média devront préciser :

- la version de MFlow ;
- le système d'exploitation ;
- le CPU ;
- le GPU ;
- la RAM ;
- le compilateur ;
- le média d'entrée ;
- le format de sortie ;
- les paramètres de traitement.

Aucune comparaison sérieuse de performances ne doit être publiée sans mesures reproductibles.

## 🧩 Architecture native

Les composants sont séparés afin de permettre une évolution progressive du moteur :

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

Les prochaines étapes sont les vrais modèles `Packet`, `Stream` et `Frame`, puis les parseurs, demuxers et muxers natifs.

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
- modèle de flux audio/vidéo.

### v0.5.x

- frames ;
- formats de pixels ;
- formats audio ;
- premières implémentations de codecs natifs.

### Plus tard

- H.264 / H.265 / AV1 ;
- AAC / Opus ;
- MKV/WebM ;
- zero-copy ;
- traitement GPU ;
- fusion de pipelines ;
- I/O asynchrone ;
- accélération matérielle.

Les versions intermédiaires (`v0.3.1`, `v0.3.2`, etc.) ajouteront progressivement ces capacités tout en conservant une base stable.

## 🧪 Tests

```bash
ctest --test-dir build --output-on-failure
```

Le projet doit rester compilable et testable sur Windows et Linux.

## 🤝 Contribution

Les contributions sont les bienvenues. Pour les modifications importantes, privilégiez une architecture modulaire, des tests et des benchmarks reproductibles pour tout travail lié aux performances.

## 🔐 Indépendance

MFlow est conçu pour fonctionner sans exécutable multimédia externe. Les fonctionnalités qui ne sont pas encore implémentées sont explicitement refusées plutôt que remplacées silencieusement par une dépendance externe.

## 📜 Licence

MFlow est distribué sous licence MIT.

---

**MFlow v0.3.0** — Fondations du moteur multimédia natif.
