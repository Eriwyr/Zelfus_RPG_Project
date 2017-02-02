
# Zelfus

Zelfus is a RPG offering two game phases. The [normal](#rpg) mode and the [fight](#fight)
You will have to complete all sorts of quests to end this game.
Dungeon and monsters will wait for you, so prepare yourself.

## Install
The game uses the following librairies :
- SDL2
- SDL2_image
- SDL2_TTF
- SDL2_mixer


### On Linux

#### Ubuntu
Open a terminal and type the following commands :
```
$ sudo apt-get install libsdl2-dev
$ sudo apt-get install libsdl2-image-dev
$ sudo apt-get install libsdl2-mixer-dev
$ sudo atp-get install libsdl2-ttd-dev
```

#### Arch Linux
```
$ sudo pacman -s sdl2
$ sudo pacman -s sdl2-mixer
$ sudo pacman -s sdl2-ttf
$ sudo pacman -s sdl2-image
```

### On Windows And MacOS
- [SDL2](https://www.libsdl.org/download-2.0.php)
- [SDL2-image](https://www.libsdl.org/projects/SDL_image/)
- [SDL2-ttf](https://www.libsdl.org/projects/SDL_ttf/)
- [SDL2-mixer](https://www.libsdl.org/projects/SDL_mixer/)

## Compile
A makefile is furnished at the root of the game.
Open a terminal at the root of the project.
To compile graphical version :
```
$ make
```
To compile unit tests :
```
$ make test
```
To compile textual version :
```
$ make txt
```
To compile all :
```
$ make all
```


## Execute
To execute the graphical version : 
```
$ make exec
```
To execute the textual version : 
```
$ make exec_txt
```
To execute the unit tests : 
```
$ make exec_test
```

## Game Rules

### Menu
When the game is starting, you'll arrive in the menu. To move arround in it, use the  
arrow keys up and down to navigate and the enter key to select.
You'll see everything about the game keys in the lower right corner of the menu.

### RPG 
You embody a hero who wakes up in a dungeon. You seem to have lost memory.  
You'll have to solve many quests to understand who you are et how to get out of this place.
You goal in this game version, is to solve the quests offered by the NPCs.
The quests will ask you to pick a certain amount of objects and to kill a certain amount of monsters.
To solve this quests, you need to accept them first.  
To acchieve so, you need to place yourself next to a NPC and talk to him ("T" key).  
You can now see your quests in the journal ("J" key).  
Once you determined how many objects must be found and how many monsters killed,  
you must search this items and monsters. When you find an object on the ground, you can pick it up ("P" key). When you step on a monster, the fight mode launches (*c.f* [Fight](#fight) mode). 
When you have completed all of the objectives of your quests, you need to get your reward.
For this, nothing simpler, just go back to the NPC that gave you the quests and talk to him again ("T" key). You automatically receive the reward.

### Fight
The fight is a turn by turn mode. The objectif is to kill every monsters before they kill you.
You have a number of movement points (one step = one movement point), some action points and some life points.
You can move for as many boxes as the number of movement points you have.
When an enemy is in range, you can cast a spell to hurt it ("1" "2" "3" keys of the numpad).  
The game will determine which target is the closest and will cast the spell on this one.  
When you can no longer move or cast, you need to pass your turn and let the enemies play ("Enter" key).
At the end of the fight, two outcomes are possible : Either you won, either you lost.
When you win, the monsters killed are accounted for the quest objective. When you lose, nothing is acounted and you need to win another fight.

## Features
- Menu
- Initialisation from .init files
- Game saving
- 2D view from above
- SDL2 for main display
- 2 game mode: exploration and fight
- Fight turn by turn
- Quest management
- Artificial intelligence (Hit n run) for the monsters.
- Experience mangement
- Musics
- Every action from the keyboard
- Custom extensions .map/.init/.save

## Organisation
### Root

- bin : binary files
- data : Contains init files, save files, resources files
- doc : Documentation, powerPoint presentation, Module diagramme, Gantt
- obj : object file  (.o)
- src : Source code of the project
- makefie : Makefile to compile and run


