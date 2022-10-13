<!-- AUTO-GENERATED-CONTENT:START (STARTER) -->
<p align="center">
  <a href="http://zeleph.fr/">
    <img alt="stickos" src="https://drive.google.com/uc?id=1uxZUVfXys-5X-yk242oydfuDpmYuh9ra" width="250" />
  </a>
</p>
<h2 align="center">
  Zeleph tournaments
</h2>

![Top Language](https://img.shields.io/badge/Langage-C%2B%2B-green)
![code style](https://img.shields.io/badge/Format-WebKit-orange)
![Graphical](https://img.shields.io/badge/Graphical-SFML-blue)

# R-Type

This project aims to recreate the [R-Type](https://fr.wikipedia.org/wiki/R-Type) game and add a multiplayer mode to it. We had to implement a multi-threaded server using [Boost::asio](https://www.boost.org/doc/libs/1_66_0/doc/html/boost_asio.html) and a graphical client in [SFML](https://www.sfml-dev.org/).

Made by : Romanie DE MEYER - Théo MILLASSEAU - Kevin ZILLIOX - Nykyta KUDRYA - Sylvian BURN

## Server

- [ ] The server must be multi-threaded
- [ ] The server must be able to handle more than one game at a time

## Client

> The client is the display terminal of the game.

- [ ] The client must contain anything necessary to display the game and handle player input.
- [X] The client must use the SFML.

## Requirements

### Platforms

- [ ] The project must be OS independent. (Linux, Windows)
- [ ] The project must be built using a [CMake](https://github.com/EpitechPromo2025/B-CPP-500-STG-5-1-rtype-romanie.de-meyer/blob/main/CMakeLists.txt) and dependencies must be handled using [conan]().

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


This is our architecture :

