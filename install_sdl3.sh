#!/usr/bin/env bash
set -e

INSTALL_DIR="${1:-$(dirname "$0")/lib}"

echo "Installing SDL3 and dependencies into $INSTALL_DIR..."

mkdir -p "$INSTALL_DIR"

INSTALL_FULL_DIR=$(realpath "$INSTALL_DIR")

REPOS=(
    "https://github.com/libsdl-org/SDL.git"
    "https://github.com/libsdl-org/SDL_image.git"
    "https://github.com/libsdl-org/SDL_mixer.git"
    "https://github.com/libsdl-org/SDL_ttf.git"
)

for REPO in "${REPOS[@]}"; do
    NAME=$(basename "$REPO" .git)
    SRC_DIR="$INSTALL_DIR/$NAME"
    BUILD_DIR="$SRC_DIR/build"

    echo -e "\n=== Installing $NAME ==="
    if [ ! -d "$SRC_DIR" ]; then
        git clone "$REPO" "$SRC_DIR"
    fi

    mkdir -p "$BUILD_DIR"
    pushd "$BUILD_DIR" > /dev/null

    cmake -DCMAKE_INSTALL_PREFIX="$INSTALL_FULL_DIR" -DCMAKE_BUILD_TYPE=Release -DSDL3_DIR="$INSTALL_FULL_DIR/cmake" ..
    cmake --build . --config Release --target install -- -j$(nproc)

    popd > /dev/null

    rm -rf "$SRC_DIR"
done

echo -e "\nSDL3 installation complete in $INSTALL_DIR"
exit 0
