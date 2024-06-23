# Zappy

A network game where several teams confront each other on a tile map containing resources.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
  - [Server](#server)
  - [GUI](#gui)
  - [AI](#ai)
- [Tests](#tests)
- [License](#license)

## Installation

1. Clone the repository. 
2. Install the SFML library. (for more information: https://www.sfml-dev.org/tutorials/2.5/start-linux.php)
3. Run `make` in the root directory to compile the project.

> **Note:** The project is only compatible with Linux. 

## Usage


---
In the root directory, you will find the following executables: `zappy_server`, `zappy_gui` and `zappy_ai`.
which are respectively the server, the graphical user interface and the artificial intelligence. 
You can use it as follows:
---
### Server
```bash
./zappy_server -p port -x width -y height -n name1 name2 ... -c clientsNb -f freq
```
- **port**: The port number.
- **width**: The width of the world.
- **height**: The height of the world.
- **name1 name2 ...**: The name of the teams.
- **clientsNb**: The number of authorized clients per team.
- **freq**: The frequency of the game. by default 100.
- **-h**: Print the usage.
- **-d**: Print debug information.
---
### GUI

```
./zappy_gui -p port -h machine
```
- **port**: The port number.
- **machine**: The host name of the machine where the server is running.
- **-help**: Print the usage.

Use **directional arrows to move** around the map.

Use the key **Z to zoom in**, the key **X to zoom out** and the key **S to reset** the zoom level.

You can **stop and start the music** with the key **P** on your keyboard.

---

### AI

Work in progress...

---
## Tests

For testing the server, you can use the following command:
```make tests_run```
it will run the unit tests for the server.
You will also find a binary file named `functional_tests_server` in the root directory, you can run it to test the server with the following command:
```./functional_tests [OPTIONS]```

For this binary, you can use the following flags:
- **-d, --debug** : Run the server in debug mode. By default, this option is disabled.
- **-h, --host <HOST>** : Define the host name. By default, the host name is localhost.
- **-p, --port <PORT>** : Define the port number. By default, the port number is localhost.
- **-s, --server** : Run the server in the background. By default, this option is disabled.
- **-t, --type <type>** : Define the type of the test. By default, the type is basic, you can also use the following types: basic, capacity and full.
- **-V, --version** : Print the version of the test.

> **Note:** The units tests are written using the criterion library. For more information: https://criterion.readthedocs.io/en/master/

## Language

- **C** for the server, _something speed is important_
- **C++** for the graphical user interface, _more practical for the graphical part_
- **Python** for the artificial intelligence, _more comfortable for the artificial intelligence_
- **Rust** for the tests, _something we don't want to be broken_

## Authors

- [**Sebastien BERTIL-SOUCHET**] - *Server Developer / Functional Test* - [GitHub](https://github.com/Sebabacou)
- [**Tom LEFOIX**] - *Server Developer / Unit Test* - [GitHub](https://github.com/tlmx25)
- [**Justine LOIZEL**] - *Graphical User Interface Developer / Graphic Designer* - [GitHub](https://github.com/justineloizel)
- [**Arthur DORIEL**] - *Graphical User Interface Developer / Project Manager* - [GitHub](https://github.com/MrMarmotte)
- [**Maxcence LARGEOT**] - *Artificial Intelligence Developer* - [GitHub](https://github.com.com/MaxenceLgt)
- [**Ewen EMERAUD**] - *Artificial Intelligence Developer* - [GitHub](https:://github.com/ewen1507)
