# SigMaker

creates AOB signatures from multilevel pointers

.\sigmaker.exe --config config.yml

config.yml

```
module: witcher.exe
window: The Witcher (1.4.5.1304)
offsets:
  - 00DC09E4
  - 29C
  - 4
  - 24
  - 0
  - 58
size: 4
offset: -30
length: 60
```

## Build

```
git clone https://github.com/microsoft/vcpkg
.\vcpkg\bootstrap-vcpkg.bat
.\vcpkg\vcpkg.exe install boost:x64-windows-static sqlite3:x64-windows-static yaml-cpp:x64-windows-static
mkdir build
cd build
..\build-ninja-msvc-x64-static.bat
```
