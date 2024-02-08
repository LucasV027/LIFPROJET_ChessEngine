# Chess Engine

![Language](https://img.shields.io/badge/Language-C%2B%2B-0052cf)
![Static Badge](https://img.shields.io/badge/Librairies-SDL2%20SDL2__image-brightgreen)
![Size](https://img.shields.io/badge/Size-10%20Mo-f12222)

<br>
<p align="center">
	<img src="https://i.imgur.com/ZRsmdCo.png" width="400" style="margin-right: 20px;">
	<img src="https://imgur.com/gtWsVkX.png" width="400">
</p>
<br>

## Description

An uncomplicated Chess Engine that accommodates multiple players with varied orientations on boards of any dimensions.
It includes an AI opponent, subnode tracking, and features for saving and loading games via the console.
Additionally, the engine allows for undoing moves at any point during the game.
You have the option to engage in matches on a visual interface, either against friends on the same screen or directly against the AI.

## Install

#### Prerequisite

- C++

- SDL2, SDL2_image set in your global path on your computer :

  On linux you can simply do (depending of your distribution)

  ```
  sudo apt-get install libsdl2-dev
  ```

  Manual installation (and other platforms) : [SDL2](https://wiki.libsdl.org/SDL2/Installation)
  [SDL2_Image](https://wiki.libsdl.org/SDL2/Installation)

#### Compile

```
cd lifprojet_chess/
make
```

Ignore the warning and then run
`./bin/main`.

#### Additional information

The project heavily rely on the console for displaying informations and inputs so you should keep it open and visible during the execution.

The project uses .h et .cpp to work but the makefile wont see changes in the .h, so if you're changing the .h
you might want to do `make clean` and after re-do a `make`.

## How to play

#### Application :

- Left click on a piece -> if you can move it, it will appear in light blue and you will have transparant circle for the possible moves of this pieces (if there is any)
- You then click again to make this piece move.

### Console :

- Press h on the keyboard to print the help menu on you console all the commands and parameters you can set will be display on this help menu

### Create your own games :

- If you want to create your own string to load a game there are the rules

## Code

- Language : c++
- Graphical interface : SDL2
- Compilation : Makefile
- Developped on Linux

### Classes :

- Application (Link between user & back-end)
- Renderer (All of the drawing on the screen & Textures holder)
- Box (A class for the rendering to make resizing the window easier)
- ChessPiece (A generic class with implementation for each of the piece's movement)
- ChessIA (A namespace where all the recursive IA functions are written)
- Player (A generic class with the color, direction, index of a player )
- ChessGame (The class containing all info about the current game (The chessBoard, the turn index, and all the players))
- Utils (Vec2Int, Vec3Int, Color...)

### Files

- SRC/ : .h & .cpp
- BIN/ : .o & executable
- EXTERN/ : All the extern librairies
- RES/ : Ressources (.png fonts ...)
- DATA/ : Save / load games
- Makefile

## Results

## Links | Sources

#### Academy links

[LIFPROJET](http://cazabetremy.fr/wiki/doku.php?id=start)

[LIFPROJET Perso](https://perso.liris.cnrs.fr/samir.aknine/L3/)

#### Research links

[SDL Course](https://lazyfoo.net/tutorials/SDL/)

[Chess English terms](https://ecole.apprendre-les-echecs.com/vocabulaire-echecs-anglais/)

[Researchs](https://www.youtube.com/watch?v=l-hh51ncgDI)

[Perft results](https://www.chessprogramming.org/Perft_Results)

#### Textures sources

[Pieces textures](https://commons.wikimedia.org/wiki/Category:PNG_chess_pieces/Standard_transparent)

## Credits

- [**Lucas VIOLENT**]() : creator of the project.
