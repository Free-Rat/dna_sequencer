{
  description = "Flake with shell for dna sequencer Project";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs, ... }@inputs:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
    in
    {
      devShells.x86_64-linux.default =
        pkgs.mkShell {

          shellHook = ''
            echo "Hello in dna sequencer"
          '';

          packages = (with pkgs; [
            gnumake
            gcc
            gdb
            lldb
            clang-tools_17
            git
          ]);
        };
    };
}
