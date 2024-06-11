# Zappy AI Documentation
![Python](https://img.shields.io/badge/python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54)

> The goal of the AI is to control a drone (the player) to replicate the behavior of a Trantor, advancing it to the highest elevation level.

> [!NOTE]
> Since the bot's information can be used against us, we will not provide any explanation on how it works. Only the overall functionality of the classes and the architecture will be presented.

## Table of content
1. [How to use](#how-to-use)
2. [AI Architecture](#ai-architecture)
3. [Class explanations](#class-explanations)
4. [Functional tests](#functional-tests)
    - [Running tests](#running-tests)
    - [Implement tests](#implement-tests)
5. [Contributors](#contributors)

## How to use

To run our bot, simply go to the root and create executables using make command.

```sh
make
```

Then run our bot using the following command:

```sh
./zappy_ai -p port -n name -h host
```

| Flag | Description |
|:------|:-------------|
| -p port | port number |
| -n name | name of the team |
| -h host | name of the machine, localhost by default |

> [!IMPORTANT]
> Make sure to have a zappy server running to run the bot.


## AI Architecture

## Class explanations

<details>

<Summary>FlagParser class<Summary>

### Behavior

This class is primarily used to parse the flags provided during the AI's execution. It stores the last occurrence of each used flag and detects errors such as invalid flags and incorrect numbers of arguments for exemple.

</details>

<details>
    <Summary>Server class<Summary>
</details>


## Functional tests

### Running tests

> [!IMPORTANT]
> To run functional tests, make sure to start a Zappy server on your PC using port 8581 and host 127.0.0.1 or localhost.

Go to the ai folder and use the following Makefile command:

```
make test_run
```

### Implement tests

In case a command is already created, just add the command input to the `inputs` table and the expected output to the `expected_outputs` table in `ai_test.sh`.

The following commands are implemented:

| Command | Param | Exemple |
|:--------|:------|:--------|
| host | [1] : host | host localhost |
| port | [1] : port | port 8581 |
| connect | [1] : host</br>[2] : port | connect localhost 8581 |
| send | [1] : host</br>[2] : port</br>[3] -> [...] : message | send localhost 8581 Broadcast test |

If the command doesn't exist follow these instructions:

1. Add command and associated function inside `self.functions`.
2. Create your associated function taking `self` and `cmd` as parameters.
3. Write content of your test in it and print expected outputs in error output (`sys.stderr`).

## Contributors

[LARGEOT Maxence](https://github.com/MaxenceLgt)</br>
[EMERAUD Ewen](https://github.com/ewen1507)