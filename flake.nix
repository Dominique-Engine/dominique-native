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
    in
    {
      devShells.${system}.default = pkgs.clangStdenv.mkDerivation {
        name = "dominique-shell";

        buildInputs = with pkgs; [
          libxcrypt
          zstd
          autoconf
          automake
          libtool
          python312Packages.jinja2
        ];

        nativeBuildInputs = with pkgs; [
          cmake
          vcpkg
          pkg-config
          buildCmd
        ];

        VCPKG_ROOT = "${pkgs.vcpkg}/share/vcpkg";

        shellHook = ''
          export SHELL=zsh
        '';
      };
    };
}
