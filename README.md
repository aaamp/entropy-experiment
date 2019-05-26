# TODO: Ładniejszy plik readme

[![Build status](https://ci.appveyor.com/api/projects/status/fcs8eqfluka7o7jg?svg=true)](https://ci.appveyor.com/project/Antollo/entropy-experiment)

### Co jest potrzebne?

- `git`
- `g++` / `Visual Studio` (wspierający c++17)
- `cmake` (co najmniej 3.10)

Instalacja zależności do kompilacji na Ubuntu 19.04:

```
sudo apt install build-essential git cmake udev libudev-dev libopenal-dev libflac-dev libvorbis-dev libxrandr-dev libfreetype6-dev
```

### Jak to sklonować i skompilować?

```
git clone https://github.com/aaamp/entropy-experiment.git --recursive --shallow-submodules
cd entropy-experiment
cmake .
cmake --build . --config Release
```

#### Zabrania się wykorzystania zamieszczonego tu kodu w jakiejkolwiek formie bez wiedzy i zgody twórców.
