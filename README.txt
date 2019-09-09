================================================================================

Pacman game, using SFML
========
by: Hof Ronis 
================================================================================
Description
===========
I developed the game Pacman using "SFML". 
================================================================================
classes
==============

1)Controller.cpp - this class is responsible of all the other classes, it managing  all thing related to the game.
It contains the classes: screen,menu,Player_Status.
3)Screen.cpp - it responsible of all the things on the screen, like the movement of objects, score and collisions.
It contains the classes: Stage_Loader, Search_Algorithm 
4)Menu.cpp - it responsible of presenting the menu in the game.
5)Player_Status.cpp- it responsible of the user game data like score,lives and speed(of pacman).
6)ResourceManager.cpp - it responsible of loading pictures and audio.
7)Stage_Loader.cpp- it responsible of loading levels, it holds the number of rows,cols and the number of cookies in the level.
8)Devil.cpp- it abstruct class, it holds boolean which tells if the devil is smart or not,the devil direction and the devil previous direction.
9)Cookie.cpp- it resposible of the object cookie, it inherit from Static.
10)Dynamic.cpp- it abstruct class,  which holds the innitiale position of the objects which inherit from it. This class inherit from Object
11)Pacman.cpp- it responsible of the object it give the pacman it direction and draw it. it inherit from Dynamic.
12)Random_Devil.cpp- it responsible of the object it give the Random_Devilit direction and draw it. it inherit from Static.
13)Smart_Devil.cpp- it responsible of the object it give the Smart_Devilit direction and draw it. it inherit from Static. 
14)Static.cpp- it abstruct class,  classes Cookie and Wall inherit from it. This class inherit from Object.
15)Search_Algorithm.cpp- it responsible of the algorithm bfs, which finds the shortest path to pacman.
16)Wall.cpp-it resposible of the object wall, it draw it and this class inherit from Static 

17 source + 16 header = 33 files in total.
================================================================================
Levels Format
============================
The format is "level"+ "number of stage"+ ".txt"

Data Structures
===================
I used 2d vector of unique ptr's which holds the cookies and the walls.

Algorithms worth mention:
==========================
I used BFS for finding the shortest path from smart_devil to pacman.

================================================================================

Known bugs
=========
- if there are more than two smart_devil the program runs a bit slower,
so I put condition which limit the smart devil to 2 in a level.
================================================================================

