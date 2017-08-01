# Potree Converter Emscripten
#### A very rough, very experimental JS port of [Potree](https://github.com/potree/PotreeConverter)

### Build Instructions

Download and install the [Emscripten SDK]('https://github.com/kripken/emscripten')

Download and install the fork of [LAStools]('https://github.com/rochester-rcl/LAStools') optimized for compilation with Emscripten

Build LASZip with Emscripten
```
cd /path/to/LAStools/LASZip
mkdir build
cd build
emcmake cmake -DCMAKE_BUILD_TYPE=Release ..
make
```
Compile Boost for Emscripten following the instructions [here](https://github.com/arielm/chronotext-boost)

clone this repository and build the PotreeConverter with Emscripten

```
cd /path/to/PotreeConverter
mkdir build
cd build
emcmake cmake -DCMAKE_BUILD_TYPE=Release \
-DLASZIP_INCLUDE_DIRS=/path/to/LASZip/dll \
-DLASZIP_LIBRARY=/path/to/LASZip/build/src/liblaszip.bc ..
make
```
