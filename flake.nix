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
        ]);

        shellHook = ''
          cat > .clangd <<EOF
          CompileFlags:
            Add:
              - -I${linuxPackages.kernel.dev}/lib/modules/6.12.63/source/include
          EOF

          exec ${pkgs.zsh}/bin/zsh
        '';
      };
    };
}
