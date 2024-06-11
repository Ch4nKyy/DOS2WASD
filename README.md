# DOS2 WASD Movement

A mod for Divinity: Original Sin 2 that allows direct character movement with hotkeys and improves the camera.

Find it on [Nexusmods](https://www.nexusmods.com/divinityoriginalsin2definitiveedition/mods/460).

This is a port of my mod [BG3 WASD Movement](https://github.com/Ch4nKyy/BG3WASD).  
BG3 WASD will be better maintained and documented!  
For technical differences, see doc/guide.md.

## Building

### Requirements

- [CMake](https://cmake.org/)
  - Add this to your `PATH`
- [PowerShell](https://github.com/PowerShell/PowerShell/releases/latest)
- [Vcpkg](https://github.com/microsoft/vcpkg)
  - Add the environment variable `VCPKG_ROOT` with the value as the path to the folder containing
  vcpkg
- [Visual Studio Community 2022](https://visualstudio.microsoft.com/)
  - Desktop development with C++
- [Divinity: Original Sin 2 Steam Distribution](https://store.steampowered.com/app/435150/Divinity_Original_Sin_2__Definitive_Edition/)
  - Add the environment variable `DOS2PATH` with the value as path to game install folder
- [7zip](https://www.7-zip.org/)
  - Install to default dir
  
### Register Visual Studio as a Generator

- Open `x64 Native Tools Command Prompt`
- Run `cmake`
- Close the cmd window

### Building

```
git clone https://github.com/Ch4nKyy/DOS2WASD.git
cd DOS2WASD
git submodule init
git submodule update --remote
.\build-release.ps1
```

### Solution Generation (Optional)
If you want to generate a Visual Studio solution, run the following command:
```
.\generate-sln.ps1
```

> ***Note:*** *This will generate a `DOS2WASD.sln` file in the **build** directory.*
