{
  description = "Linnux kernel module build for rpi5";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";

    nixos-raspberrypi = {
      url = "github:nvmd/nixos-raspberrypi/main";
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };

  outputs =
    { nixpkgs, nixos-raspberrypi, ... }@inputs:
    let
      system = "aarch64-linux";

      pkgs = import nixpkgs {
        inherit system;
        overlays = [
          nixos-raspberrypi.overlays.vendor-kernel
        ];
      };

      kernel = pkgs.linux_rpi5_v6_12_34;
      linuxPackages = pkgs.linuxPackagesFor kernel;
    in
    {
      devShells."${system}".default = pkgs.mkShell {
        packages = [
          linuxPackages.kernel.dev
        ]
        ++ (with pkgs; [
          gnumake
          clang
        ]);

        shellHook = let
          libModulePath = "${linuxPackages.kernel.dev}/lib/modules/${linuxPackages.kernel.modDirVersion}";
          in
          ''
          cat > .clangd <<EOF
          CompileFlags:
            Add:
              - -I$(pwd)/src/include
              - -I${libModulePath}/source/include
          Diagnostics:
            Suppress:
              - '*'
          EOF

          sed -i '\%#MODCOMPPATH%{n;s%.*%COMPPATH = ${libModulePath}/build%}' ./Makefile
          
          exec ${pkgs.zsh}/bin/zsh
        '';
      };
    };
}
