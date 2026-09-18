#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD="$ROOT/build-install"
PREFIX="${HOME}/.local"
BIN="${PREFIX}/bin"

command -v cmake >/dev/null 2>&1 || { echo "Error: cmake is required." >&2; exit 1; }

printf '[1/5] Checking prerequisites...\n'
command -v c++ >/dev/null 2>&1 || command -v g++ >/dev/null 2>&1 || command -v clang++ >/dev/null 2>&1 || { echo "Error: a C++ compiler is required." >&2; exit 1; }

printf '[2/5] Configuring MFlow...\n'
cmake -S "$ROOT" -B "$BUILD" -DCMAKE_BUILD_TYPE=Release -DMFLOW_BUILD_TESTS=OFF -DMFLOW_BUILD_BENCHMARKS=OFF -DMFLOW_BUILD_EXAMPLES=OFF

printf '[3/5] Building MFlow...\n'
cmake --build "$BUILD" --config Release --parallel

printf '[4/5] Installing into %s...\n' "$PREFIX"
cmake --install "$BUILD" --config Release --prefix "$PREFIX"

printf '[5/5] Checking PATH...\n'
case ":${PATH}:" in
  *":${BIN}:"*) ;;
  *)
    echo "MFlow is installed, but ${BIN} is not in PATH."
    echo "Add this line to ~/.bashrc or ~/.zshrc:"
    echo 'export PATH="$HOME/.local/bin:$PATH"'
    ;;
esac

printf '\nMFlow 0.4.1 installed successfully.\n'
printf 'Installation directory: %s\n' "$PREFIX"
printf 'Run from any directory: mflow version\n'