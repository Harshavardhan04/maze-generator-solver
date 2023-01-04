C Coursework: Readme file

This program is used to get a robot from one side of a random maze to another. 

First, a random maze is generated using logic inspired from Prim’s algorithm. They have a fixed starting point (1,1) and end point.

Next, a recursive pathfinding algorithm is used to get the robot from the starting point to the end point, which works with any maze that my maze generation algorithm generates.

Upon reaching the end point, the program is terminated. 

To compile and run: 
gcc -o run ccoursework.c graphics.c
./run | java -jar drawapp-2.0.jar


