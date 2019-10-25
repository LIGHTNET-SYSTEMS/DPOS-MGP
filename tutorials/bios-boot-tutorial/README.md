# Bios Boot Tutorial

The `bios-boot-tutorial.py` script simulates the LightNetIO bios boot sequence.

``Prerequisites``:

1. Python 3.x
2. CMake
3. git

``Steps``:

1. Install LightNetio binaries by following the steps outlined in below tutorial
[Install LightNetio binaries](https://github.com/LightNetIO/LightNet#mac-os-x-brew-install)

2. Install LightNetio.cdt binaries by following the steps outlined in below tutorial
[Install LightNetio.cdt binaries](https://github.com/LightNetIO/LightNetio.cdt#binary-releases)

3. Compile LightNetio.contracts

```bash
$ cd ~
$ git clone https://github.com/LightNetIO/LightNetio.contracts.git
$ cd ./LightNetio.contracts/
$ ./build.sh
$ pwd

```

4. Make note of the directory where the contracts were compiled
The last command in the previous step printed on the bash console the contracts' directory, make note of it, we'll reference it from now on as `LightNetIO_CONTRACTS_DIRECTORY`

5. Launch the `bios-boot-tutorial.py` script
Minimal command line to launch the script below, make sure you replace `LightNetIO_CONTRACTS_DIRECTORY` with actual directory

```bash
$ cd ~
$ git clone https://github.com/LightNetIO/LightNet.git
$ cd ./LightNet/tutorials/bios-boot-tutorial/
$ python3 bios-boot-tutorial.py --clLightNet="clLightNet --wallet-url http://127.0.0.1:6666 " --nodLightNet=nodLightNet --kLightNetd=kLightNetd --contracts-dir="/LightNetIO_CONTRACTS_DIRECTORY/" -a

```

See [LightNetIO Documentation Wiki: Tutorial - Bios Boot](https://github.com/LightNetIO/LightNet/wiki/Tutorial-Bios-Boot-Sequence) for additional information.