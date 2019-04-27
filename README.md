# TODO: Ładniejszy plik readme

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

