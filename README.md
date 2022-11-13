<!-- AUTO-GENERATED-CONTENT:START (STARTER) -->
<p align="center">
  <img alt="stickos" src="https://fs-prod-cdn.nintendo-europe.com/media/images/10_share_images/games_15/virtual_console_wii_u_7/H2x1_WiiUVC_RType.jpg" />
</p>

![Top Language](https://img.shields.io/badge/Langage-C%2B%2B-green)
![code style](https://img.shields.io/badge/Format-WebKit-orange)
![Graphical](https://img.shields.io/badge/Graphical-SFML-blue)

# R-Type

This project aims to recreate the [R-Type](https://fr.wikipedia.org/wiki/R-Type) game and add a multiplayer mode to it. We had to implement a multi-threaded server using [SFML::Network](https://www.sfml-dev.org/tutorials/2.1/network-socket-fr.php) and a graphical client in [SFML](https://www.sfml-dev.org/).

Made by : Romanie DE MEYER - Théo MILLASSEAU - Kevin ZILLIOX - Nykyta KUDRYA - Sylvian BURN

## Dependencies

[vcpkg](https://vcpkg.io/en/getting-started.html) is a submodule of this repository. If you wish to use [vcpkg](https://vcpkg.io/en/getting-started.html) and did not clone this repository with --recurse-submodules, please run:
```
git submodule update --init
```
before continuing.

**OR**

Clone our repository with:
```
git clone --recurse-submodule https://github.com/EpitechPromo2025/B-CPP-500-STG-5-1-rtype-romanie.de-meyer.git
```

You will need to install [vcpkg](https://vcpkg.io/en/getting-started.html) to build our game.

To install vcpkg, you will need to clone the repository somewhere on your computer using this command:

```
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg/
```
Then execute the following command:
```
./bootstrap-vcpkg.sh
```
Lastly, execute this command:
```
./vcpkg integrate install
```
## Building

This project uses CMake, allowing it to be built with a large range of compilers.

This is an explanation of how you should build on Linux or Windows.

**Linux:**

You just have to execute this `build.sh` script, from the top directory of this repository (i.e. the folder containing this README file):
```
./build.sh
```

**Windows:**

There are several ways to build under windows

1. Launch with visual studio 2022
* On the _top bar_ of visual studio 2022, click on `Project` then on `Configure cache`.
* Then on the _top bar_, click on `Build` then on `Build all` _(if this isn't available close and re-open VS then you should be able to build)_
* You will now _find_ our **binaries** in the _file explorer_.

2. If you are using vcpkg (this will automatically install all necessary dependencies).
```
cmake -B build "-DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake"
```
You can then compile the project with this command (again, from the top directory of this repository):
```
cmake --build build
```
3. Other

```
cd build
nmake
```

## UML

[**ECS**](https://github.com/EpitechPromo2025/B-CPP-500-STG-5-1-rtype-romanie.de-meyer/blob/main/Documentation/DiagrammeECS.pdf)\
[**Network**](https://github.com/EpitechPromo2025/B-CPP-500-STG-5-1-rtype-romanie.de-meyer/blob/main/Documentation/Network_diagram_R-Type.pdf)\
[**Doxygen**](https://nekyt.github.io/rtype-documentation/)

<p align="center">
You can find more informations about the rtype in the wiki.
</p>

<p align="center">
Have fun ! 
</p>
