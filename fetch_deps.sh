#!/usr/bin/env bash
set -euo pipefail

mkdir -p vendored

clone_or_update() {
  url="$1"
  dir="$2"

  if [ -d "$dir" ]; then
    if [ -d "$dir/.git" ]; then
      echo "Repository exists at $dir — fetching updates (shallow)..."
      git -C "$dir" fetch --depth 1 origin || true
      # try to update checked-out ref to the latest fetched commit on origin/HEAD
      git -C "$dir" reset --hard origin/HEAD 2>/dev/null || git -C "$dir" checkout --detach FETCH_HEAD 2>/dev/null || true
    else
      echo "Directory $dir exists but is not a git repo — skipping clone."
    fi
  else
    echo "Cloning $url into $dir ..."
    git clone --depth 1 "$url" "$dir" || true
  fi
}

clone_or_update https://github.com/libsdl-org/SDL.git vendored/SDL
clone_or_update https://github.com/g-truc/glm.git vendored/glm

echo "Done."
exit 0