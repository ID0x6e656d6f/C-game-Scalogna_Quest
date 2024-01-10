[![Review Assignment Due Date](https:classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https:classroom.github.com/a/48qxWLnU)

# Progetto-finale-2023-Scalogna-Quest

Progetto finale Programmazione Procedurale UniPG Informatica

## Nome: Alessandro

## Cognome: Zaganelli

## Matricola: 371883

## Commenti/modifiche al progetto:

# Running the project using gcc
gcc -o out main.c terminallib.c players.c maps.c gamelib.c enemy.c -std=c11 -Wall 

# Brief description of some project methods, functions and variables:

## [gamelib.c](gamelib.c)

### throwDice(int n);
 method used to simplify the randomization of the die roll

### isGenerated(int n, int turnArray[]);
 check if a player is already generated on the turn array

### turnRandomizer(int turnArray[]);
 method used to randomize all players' turns. In this method the alive variable is used to check how many players are still actually alive and based on this in the last cycle for the random generation there will be as many iterations as there are players alive

### static void attack(int player, Abitante enemy, int turn)
In this method the attack (and defense) situation is managed during a fight. The "turn" variable is very important and is used to understand what type of attack it is. As can be seen from the code, if the turn variable is:
- 1 then it means that it is the player who attacks;
- 0 then the enemy attacks;
- 2 then the enemy attacks after a failed escape attempt, therefore with the player's dice halved


### static bool winCheck()
 checks if a player has reached the end of the map

### static bool deathCheck()
 Check if all players are dead

### extern bool created;
 check if the creation of the players and of the map is done correctly. Its shared with the main.c. This variable becomes True when the map has been generated because it means that the creation of the players has also been completed

### unsigned int zoneCounter = 0;
 saves the quantity of zones

### void stmpPlayableClasses();
 print the playable classes. A separate method was used to avoid overloading the player_loader() method

### static void mapsMenu();
this method is used to efficiently manage the menu for modifying the map


## [enemy.c](enemy.c)

### void enemyGeneration(Abitante *enemy, int level)
manages the generation of the newly spawned enemy. If the enemy has specific names, he gets different statistics


 ## [maps.c](maps.c)
 ### this file allows you to manage some methods for viewing and managing the map



## [players.c](players.c)
 ### this file allows you to manage some methods for viewing and managing the players


## [terminallib.c](terminallib.c)

### this file allows you to manage some methods for customize the output during different sitautions of the game
------------------------------
Dec 5, 2023:
first check of the repository and first commit with entry of student data.

Dec 7, 2023:
first commit with actual code. Here I created the files gamelib.c, gamelib.h, main.c, terminallib.c and terminallib.h. The first three are the required files, where I created:

- the first methods for inserting players and viewing them
- all the useful data to enter in the gamelib.h file
- the first version of the initial menu.

In the terminallib.c/.h files, I have declared and defined methods to make it easier to use different terminal colors throughout project development.

Dec 8, 2023:
small commit where graphic changes are made for the selection of characters, their insertion in the list and the termina_gioco() method is developed.

Dec 13, 2023:
committed to completing player insertion, despite a segmentation fault.

Dec 14, 2023 1:
fixed the segmentation fault through the use of strdup.

Dec 14, 2023 2:
moved for convenience various player methods to another globals.c file.

Dec 17, 2023:
first creation of the map and the methods used to manage and display it.

Dec 26, 2023:
creation of separate temporary files for map and player management.

Dec 29, 2023:
addition of the map management method by the game master and other related methods, control methods and addition of zones. Incomplete commit forced by a virtual machine memory error.

Jan 4, 2024:
several commits were made due to an error in the git files local to my virtual machine.
I finally solved it using commands.
find .git/objects/ -size 0 -exec rm -f {} \;
git fetch origin
Finally, all methods related to map management have been completed, and with the exception of small details, map management is considered complete. Many map methods have been moved back to the gamelib.c file for convenience. Furthermore, we also started setting the methods used in the gioca() method.

Jan 5, 2024:
Adding checks in all user input to avoid program crashes. Completed the random generation of the turns through the use of 2 methods and added the method to display them.
Added a short description of all previously executed commits.

Jan 6, 2024:
Changes in some structures used to save data and changes in how some data is input due to minor errors during program execution. Improved random turn generation and started the apri_porta() method. Completion of the main functions of the gioca() method and management of the game itself.
