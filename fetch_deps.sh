#!/usr/bin/env bash
set -euo pipefail

mkdir -p vendored

clone_or_update() {
  url="$1"
  dir="$2"
  commit="$3"

  if [ -d "$dir" ]; then
    if [ -d "$dir/.git" ]; then
      echo "Repository exists at $dir — fetching pinned revision $commit..."
      git -C "$dir" fetch --depth 1 origin "$commit"
      git -C "$dir" checkout --detach --force "$commit"
    else
      echo "Directory $dir exists but is not a git repo — refusing to continue." >&2
      exit 1
    fi
  else
    echo "Cloning $url at pinned revision $commit into $dir ..."
    git init "$dir"
    git -C "$dir" remote add origin "$url"
    git -C "$dir" fetch --depth 1 origin "$commit"
    git -C "$dir" checkout --detach --force "$commit"
  fi
}

clone_or_update https://github.com/libsdl-org/SDL.git vendored/SDL 64067c11acd856c6c989612030ac9b25d9ccde93
clone_or_update https://github.com/g-truc/glm.git vendored/glm 6f14f4792a0cde5d0cf2c910506724d61cb95834
clone_or_update https://github.com/jkuhlmann/cgltf.git vendored/cgltf 85cd62382dfea638278962690cf515023f33ed00
clone_or_update https://github.com/nothings/stb.git vendored/stb 31c1ad37456438565541f4919958214b6e762fb4
clone_or_update https://github.com/tinyobjloader/tinyobjloader.git vendored/tinyobjloader 45636bdcef1a4fec140346b90c0b50bf0bc3e23b

echo "Done."
exit 0
