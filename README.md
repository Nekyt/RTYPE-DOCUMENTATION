<!-- AUTO-GENERATED-CONTENT:START (STARTER) -->
<p align="center">
  <img alt="stickos" src="https://fs-prod-cdn.nintendo-europe.com/media/images/10_share_images/games_15/virtual_console_wii_u_7/H2x1_WiiUVC_RType.jpg" />
</p>

![Top Language](https://img.shields.io/badge/Langage-C%2B%2B-green)
![code style](https://img.shields.io/badge/Format-WebKit-orange)
![Graphical](https://img.shields.io/badge/Graphical-SFML-blue)

# Structure

<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
<!-- https://github.com/thlorenz/doctoc -->

- [Structure](#structure)
  - [R-Type overview](#r-type)
    - [Software architecture](#software-architecture)
      - [Platforms](#platforms)
      - [Server](#server)
      - [Client](#client)
      - [Protocol](#protocol)
      - [Libraries](#libraries)
      - [Game Engine](#game-engine)
    - [Installing](#installing)
    - [Controller](#controller)
    - [UML](#uml)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# R-Type

This project aims to recreate the [R-Type](https://fr.wikipedia.org/wiki/R-Type) game and add a multiplayer mode to it. We had to implement a multi-threaded server using [Boost::asio](https://www.boost.org/doc/libs/1_66_0/doc/html/boost_asio.html) and a graphical client in [SFML](https://www.sfml-dev.org/).

Made by : Romanie DE MEYER - Théo MILLASSEAU - Kevin ZILLIOX - Nykyta KUDRYA - Sylvian BURN


##  Software architecture

### Platforms

- [ ] The project must be OS independent. (Linux, Windows)
- [ ] The project must be built using a [CMake](https://github.com/EpitechPromo2025/B-CPP-500-STG-5-1-rtype-romanie.de-meyer/blob/main/CMakeLists.txt).

### Server

- [ ] The server must be multi-threaded and not blocking.
- [ ] The server must have authority on what happens in the end.

### Client

> The client is the display terminal of the game.

- [ ] The client must contain anything necessary to display the game and handle player input.
- [X] The client must use the SFML.

### Protocol

- [ ] You must **design** a binary protocol for client/server communications.
- [X] You must use _UDP_ for communications between the server and the clients in game. 
- [ ] A second connection using _TCP_ can be used for the rest.
- [ ] You must document your protocol and the documentation must be an RFC as discribed in [RFC 2223](https://www.ietf.org/rfc/rfc2223.txt).
- [ ] Your RFC must be formatted like an official RFC.
- [ ] You must write the RFC in ASCII format.
- [ ] You must respect standard RFC keywords as described in [RFC 2119](https://www.ietf.org/rfc/rfc2119.txt).

### Libraries

- [X] You must use the SFML on the client side and any rendering must be done using the SFML.
- [ ] You are allowed to use **Boost::ASIO** for your server.

### Game Engine

> The game engine is the core foundation of any video game: it determines how you represent an object in-game, how the coordinate system works, and how the various systems of your game (graphics, physics, network... ) communicate.

- [ ] Your engine must provides type-safety at compile-time.

We choosed to use an [ECS architecture](https://en.wikipedia.org/wiki/Entity%E2%80%93component%E2%80%93system) for our engine.

## Installing

**Prerequisites:**

You will need to install [vcpkg](https://vcpkg.io/en/getting-started.html) to build our game.
To install vcpkg, you will need to clone the repository somewhere on your computer using this command:
```git clone https://github.com/Microsoft/vcpkg.git```
Then execute the following command:
```./vcpkg/bootstrap-vcpkg.sh```
Lastly, execute this last command inside the repository containing vcpkg:
```./vcpkg integrate install```

**Linux:**

```
./build.sh
```

**Windows:**

```
Launch with visual studio
cmake
```

## Controller

**Player**

 Button        | Direction
 --------------|-------------
 Arrow Up      | Top
 Arrow Down    | Down
 Arrow Left    | Left
 Arrow Right   | Right
 Space         | Shoot

## UML

[**ECS**]()


