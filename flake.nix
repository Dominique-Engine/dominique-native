{
  inputs.nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";

  outputs = { self, nixpkgs, ... }:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs {
        inherit system;
      };
      buildCmd = pkgs.writeScriptBin "build" ''
        cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" || exit 1
        cmake --build build || exit 1
      '';
      clearCmd = pkgs.writeScriptBin "clear-artifacts" ''
        rm -rf build
        rm -rf ~/.cache/vcpkg
        rm -rf ~/.vcpkg
      '';
    in
    {
      devShells.${system}.default = pkgs.stdenv.mkDerivation {
        name = "dominique-shell";

        buildInputs = with pkgs; [
          libGL
          libGLU
          clang-tools
          libxcrypt
          zstd
          autoconf
          automake
          libtool
          python312Packages.jinja2
          #   You will need to install Xorg dependencies to use feature x11:
          xorg.libX11
          xorg.libXft
          xorg.libXext
          #   You will need to install Wayland dependencies to use feature wayland:
          # libwayland-dev
          # libxkbcommon-dev
          # libegl1-mesa-dev
          #   You will need to install ibus dependencies to use feature ibus:
          # ibus
        ];

        nativeBuildInputs = with pkgs; [
          cmake
          vcpkg
          pkg-config
          buildCmd
          clearCmd
        ];

        VCPKG_ROOT = "${pkgs.vcpkg}/share/vcpkg";

        shellHook = ''
          export SHELL=zsh
        '';
      };
    };
}
