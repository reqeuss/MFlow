#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD="$ROOT/build-install"
PREFIX="${HOME}/.local"

command -v cmake >/dev/null 2>&1 || { echo "Error: cmake is required." >&2; exit 1; }

printf '[1/3] Configuring MFlow...\n'
cmake -S "$ROOT" -B "$BUILD" \
  -DMFLOW_BUILD_TESTS=OFF \
  -DMFLOW_BUILD_BENCHMARKS=OFF \
  -DMFLOW_BUILD_EXAMPLES=OFF

printf '[2/3] Building MFlow...\n'
cmake --build "$BUILD" --config Release

printf '[3/3] Installing into %s...\n' "$PREFIX"
cmake --install "$BUILD" --config Release --prefix "$PREFIX"

case ":${PATH}:" in
  *":${PREFIX}/bin:"*) ;;
  *)
    echo "Add this line to ~/.bashrc or ~/.zshrc if needed:"
    echo "export PATH=\"\$HOME/.local/bin:\$PATH\""
    ;;
esac

printf '\nMFlow was installed successfully.\n'
printf 'Open a new terminal, then run: mflow version\n'
