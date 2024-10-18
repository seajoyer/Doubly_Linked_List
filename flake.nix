{
  description = "Doubly Linked List";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-24.05";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};

        testDoublyLinkedList = pkgs.stdenv.mkDerivation {
          pname = "doubly_linked_list_tests";
          version = "0.1.0";
          name = "doubly_linked_list_tests-0.1.0";

          src = ./.;

          nativeBuildInputs = with pkgs; [ gnumake libgcc cmake ];

          buildInputs = with pkgs; [ libcxx catch ];

          cmakeFlags = [
            "-DCMAKE_BUILD_TYPE=Release"
            "-DCMAKE_CXX_FLAGS=-std=c++17"
          ];

          buildPhase = ''
            cmake .
            make VERBOSE=1 -j $NIX_BUILD_CORES
          '';

          installPhase = ''
            mkdir -p $out/bin
            cp doubly_linked_list_tests $out/bin/
          '';
        };

      in {
        packages = {
          default = testDoublyLinkedList;
        };

        apps = {
          default = flake-utils.lib.mkApp { drv = testDoublyLinkedList; };
        };

        devShells.default = pkgs.mkShell {
          name = "doubly_linked_list-dev-shell";

          nativeBuildInputs = with pkgs; [ gnumake cmake ccache git bear libgcc ];

          buildInputs = with pkgs; [ libcxx catch ];

          shellHook = ''
            export CC=gcc
            export CXX=g++
            export CXXFLAGS="''${CXXFLAGS:-}"

            export CCACHE_DIR=$HOME/.ccache
            export PATH="$HOME/.ccache/bin:$PATH"
            export CPATH=${pkgs.catch}/include:$CPATH

            alias c=clear

            echo "======================================"
            echo "$(gcc    --version | head -n 1)"
            echo "$(make   --version | head -n 1)"
            echo ""
            echo "Build the project:  nix build"
            echo "Run the project:    nix run"
            echo ""
            echo "Happy coding!"
          '';
        };
      });
}
