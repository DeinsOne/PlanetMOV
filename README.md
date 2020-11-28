# PlanetMOV

![](docs/MovIco.svg)
![GitHub repo size](https://img.shields.io/github/languages/code-size/DeinsOne/PlanetMOV?style=flat-square&color=red)
![Licence](https://img.shields.io/github/license/DeinsOne/PlanetMOV?style=flat-square&color=red)

PlanetMOV is a lightweight solar system emulator that uses Lua scripts and different shaders instead of control components. Main purpose of project is getting know how to work with Cinder library(Render process and function set), Lua binder, shader languages and program architecture.

Currently supports only Linux.


## Futures

- [x] Linux build system
- [x] Planets config file
- [x] Glsl shaders
    - [x] FragmetShaders
    - [ ] Vertex shaders
- [ ] Hlsl shaders
- [x] Lua scripting
    - [x] VM binding(binding scripts to plants) 
    - [x] Events(onSetup, onUpdate)
    - [ ] PlanetMOV Lua set(classes, functions)


More information can be found on [PlanetMOV Trello](https://trello.com/b/55gNFNto)



## Dependencies

This project uses:
- [cinder/Cinder](https://github.com/cinder/Cinder.git)
- [flingengine/Catch2](https://github.com/flingengine/Catch2.git)
- [open-source-parsers/jsoncpp](https://github.com/open-source-parsers/jsoncpp.git)
- [lua/lua](https://github.com/lua/lua.git)
- [vinniefalco/LuaBridge](https://github.com/vinniefalco/LuaBridge.git)



## Building

Clone the project & submodules:

```
git clone https://github.com/DeinsOne/PlanetMOV.git
cd PlanetMov
git submodule update --init
```

## Linux

Install all the libraries that are needed:

```
# Ubuntu
sudo apt-get install libxcursor-dev \
    libxrandr-dev \
    libxinerama-dev \
    libxi-dev \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    zlib1g-dev \
    libfontconfig1-dev \
    libmpg123-dev \
    libsndfile1 \
    libsndfile1-dev \
    libpulse-dev \
    libasound2-dev \
    libcurl4-gnutls-dev \
    libgstreamer1.0-dev \
    libgstreamer-plugins-bad1.0-dev \
    libgstreamer-plugins-base1.0-dev \
    gstreamer1.0-libav \
    gstreamer1.0-alsa \
    gstreamer1.0-pulseaudio \
    gstreamer1.0-plugins-bad \
    libboost-filesystem-dev

# Fedora
sudo dnf install \
    mesa-libGL-devel \
    mesa-libGLU-devel \
    zlib-devel \
    libcurl-devel \
    pulseaudio-libs-devel \
    libmpg123-devel \
    libsndfile-devel \
    libXcursor-devel \
    libXrandr-devel \
    libXinerama-devel \
    libXi-devel \
    gstreamer1-devel \
    gstreamer1-plugins-base-devel \
    gstreamer1-plugins-bad-free-devel \
    fontconfig-devel
```

__Note:__ See [Cinder](https://libcinder.org/docs/index.html) documentation to get required libs

### Build

```
./build.sh

# or 
./build.sh -buildtype="Release/Debug" -gltarget="ogl/es2"
```

__Note:__ You can use building flags to specify building behavior. All flags detecting manually by default 


## Licence

PlanetMOV is licensed under MIT license. See [LICENSE](./LICENSE) for more details.