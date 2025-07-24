Name1: Yosef Kovan
ID: 328607304

Name2: Shmuel Friedman
ID: 312252588

//========================
//   about the program
//========================

this program is a pick up stick game. the idea of the game is to pick up all
the sticks as quickly as possible and to beat the time on the clock.

//========================
//  basic data structures
//========================

the main data structure that hold the sticks throughout the game
is a list container. we chose this since removing from a list is o(1).

we have a map container which each key is the color and the value is a vector
of pointers to that colored stick. drawing the sticks according to color is
o(k) when k is the amount of sticks left of that color. the points for each color 
is according to its order in the alphabet therefore picking a blue stick is the 
highest amount of points. 

each stick holds a unordered set in which it points to all the sticks above, 
and a vector which points to all the stick under the current stick. removing 
a stick from the above is o(1) on average since it is stored in a unorderes_set. 
therefore removing sticks that are no longer valid is on average o(k) =< o(n).

//========================
//   about the classes
//========================
we have the controller which is in charge of the main scree. Board class,
which holds all the sticks and is in charge of the main game logic. Top bar class, 
is in charge of storing the clock data how many sticks were lifted and etc... .
We used a Resources class which holds all the game data and is implemented using
a singletone design pattern. The side bar class is in charge of the three buttons on 
the side. End screen class delas with drawing the end screen. 
Stick class is in charge of holding all data regarding the stick and all logic used
for the stick. File dealing is in charge of loading a file and saving a file.

//========================
//      save file
//========================

the info is saved to a text file. a file must exist in order to run due to the 
cmake file. if you wish to delete the file and check what happens you can
either remove the line from the cmake file and re-compile, or you can leave the 
file empty and see the exception thrown.

//========================
//    time in the game
//========================
each stick is given 2 seconds.