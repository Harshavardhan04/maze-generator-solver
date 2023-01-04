#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int gridSize = 30;
int xMazeIndex = 1, yMazeIndex = 1;

struct maze
{
    int maze[21][21];
    int visited[21][21];
};
struct robot
{
    int robotX[3];
    int robotY[3];
    char robotDir;
};
void drawMaze(struct maze *m1);
void generateMaze(struct maze *m1);
void carvePath(struct maze *m1, int curX, int curY);

int atMarker(struct maze *m1, struct robot *r1)
{
    int finX, finY; 
    int robX = (*r1).robotX[1];
    int robY = (*r1).robotY[1];
    int breakLoop = 0;
    for (int k = 0; k < 21 && (breakLoop == 0); k++)
    {
        for (int l = 0; l < 21 && (breakLoop == 0); l++)
        {
            //identify the finishing square
            if ((*m1).maze[k][l] == 4)
            {
                finX = l;
                finY = k;
                breakLoop = 1;
            }
        }
    }
    int xMin = (50 + (finX * 30));
    int xMax = (50 + (30 * (finX + 1)));
    int yMin = (50 + (30 * finY));
    int yMax = (50 + (30 * (finY + 1)));
    if (((robX > xMin && robX < xMax)) && ((robY > yMin) && (robY < yMax)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int canMoveForward(struct maze *m1, struct robot *r1)
{
    int xToCheck, yToCheck;
    char robDir = (*r1).robotDir;
    int xCell = ((*r1).robotX[1] - 50) / 30;
    int yCell = ((*r1).robotY[1] - 50) / 30;

    int check;
    switch (robDir)
    {
    case 'e':
        xToCheck = xCell + 1;
        yToCheck = yCell;
        break;

    case 'n':
        xToCheck = xCell;
        yToCheck = yCell - 1;
        break;
    case 's':
        xToCheck = xCell;
        yToCheck = yCell + 1;
        break;
    case 'w':
        xToCheck = xCell - 1;
        yToCheck = yCell;
        break;
    }

    if (((*m1).maze[yToCheck][xToCheck]) == 1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
void drawRobot(struct maze *m1, struct robot *r1)
{
    foreground();
    setColour(green);
    drawPolygon(3, (*r1).robotX, (*r1).robotY);
    fillPolygon(3, (*r1).robotX, (*r1).robotY);
    if (atMarker(m1, r1) == 1)
    {
        foreground();
        clear();
    }
}

void drawMaze(struct maze *m1)
{
    setWindowSize(1000, 1400);
    background();
    int x = 50;
    int y = 50;
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            if ((*m1).maze[i][j] == 1)
            {
                drawRect(x, y, gridSize, gridSize);
                setColour(black);
                fillRect(x, y, gridSize, gridSize);
            }
            else if ((*m1).maze[i][j] == 4)
            {
                setColour(gray);
                drawRect(x, y, gridSize, gridSize);
                fillRect(x, y, gridSize, gridSize);
            }
            else
            {
                setColour(black);
                drawRect(x, y, gridSize, gridSize);
            }
            x += gridSize;
        }
        x = 50;
        y += gridSize;
    }
}

void moveForward(struct maze *m1, struct robot *r1)
{
    foreground();
    clear();

    switch ((*r1).robotDir)
    {
    case 'n':
        for (int a = 0; a < 3; a++)
        {
            (*r1).robotY[a] -= 30;
        }
        yMazeIndex--;
        break;

    case 'e':
        for (int a = 0; a < 3; a++)
        {
            (*r1).robotX[a] += 30;
        }
        xMazeIndex++;
        break;

    case 's':
        for (int a = 0; a < 3; a++)
        {
            (*r1).robotY[a] += 30;
        }
        yMazeIndex++;
        break;

    case 'w':
        for (int a = 0; a < 3; a++)
        {
            (*r1).robotX[a] -= 30;
        }
        xMazeIndex--;
        break;
    }
    drawRobot(m1, r1);
}

void turnLeft(struct maze *m1, struct robot *r1)
{
    foreground();
    clear();
    int tempX[3], tempY[3];
    switch ((*r1).robotDir)
    {
    case 'n':
        for (int i = 0; i < 3; i++)
        {
            tempX[i] = (*r1).robotX[i];
            tempY[i] = (*r1).robotY[i];
        }
        (*r1).robotDir = 'w';
        (*r1).robotY[0] = (tempY[0] - 10);
        (*r1).robotX[1] = (tempX[1] + 10);
        break;

    case 'e':
        for (int i = 0; i < 3; i++)
        {
            tempX[i] = (*r1).robotX[i];
            tempY[i] = (*r1).robotY[i];
        }
        (*r1).robotDir = 'n';
        (*r1).robotX[1] = (tempX[1] + 10);
        (*r1).robotY[2] = (tempY[2] + 10);
        break;

    case 's':
        for (int i = 0; i < 3; i++)
        {
            tempX[i] = (*r1).robotX[i];
            tempY[i] = (*r1).robotY[i];
        }
        (*r1).robotDir = 'e';
        (*r1).robotY[0] = (tempY[0] + 20);
        (*r1).robotX[1] = (tempX[1] - 20);
        (*r1).robotY[2] = (tempY[2] - 10);
        (*r1).robotX[2] = (tempX[2] + 10);
        break;

    case 'w':
        for (int i = 0; i < 3; i++)
        {
            tempX[i] = (*r1).robotX[i];
            tempY[i] = (*r1).robotY[i];
        }
        (*r1).robotDir = 's';
        (*r1).robotY[0] = (tempY[0] - 10);
        (*r1).robotX[2] = (tempX[2] - 10);
        break;
    }
    drawRobot(m1, r1);
}

void turnRight(struct maze *m1, struct robot *r1)
{
    foreground();
    clear();
    int tempX[3], tempY[3];
    switch ((*r1).robotDir)
    {
    case 'n':
        for (int i = 0; i < 3; i++)
        {
            tempX[i] = (*r1).robotX[i];
            tempY[i] = (*r1).robotY[i];
        }
        (*r1).robotDir = 'e';
        (*r1).robotX[1] = (tempX[1] - 10);
        (*r1).robotY[2] = (tempY[2] - 10);
        break;

    case 'e':
        for (int i = 0; i < 3; i++)
        {
            tempX[i] = (*r1).robotX[i];
            tempY[i] = (*r1).robotY[i];
        }
        (*r1).robotDir = 's';
        (*r1).robotY[0] = (tempY[0] - 20);
        (*r1).robotX[1] = (tempX[1] + 20);
        (*r1).robotY[2] = (tempY[2] + 10);
        (*r1).robotX[2] = (tempX[2] - 10);
        break;

    case 's':
        for (int i = 0; i < 3; i++)
        {
            tempX[i] = (*r1).robotX[i];
            tempY[i] = (*r1).robotY[i];
        }
        (*r1).robotDir = 'w';
        (*r1).robotX[2] = (tempX[2] + 10);
        (*r1).robotY[0] = (tempY[0] + 10);
        break;

    case 'w':
        for (int i = 0; i < 3; i++)
        {
            tempX[i] = (*r1).robotX[i];
            tempY[i] = (*r1).robotY[i];
        }
        (*r1).robotDir = 'n';
        (*r1).robotY[0] = (tempY[0] + 10);
        (*r1).robotX[1] = (tempX[1] - 10);
        break;
    }
    drawRobot(m1, r1);
}

void findMarker(struct maze *m1, struct robot *r1, int curXindex, int curYindex)
{
    while (!atMarker(m1, r1))
    {
        if ((canMoveForward(m1, r1)) == 1)
        {
            sleep(15);
            moveForward(m1, r1);
            sleep(15);
        }
        else
        {
            sleep(15);
            turnRight(m1, r1);
            sleep(15);
            findMarker(m1, r1, xMazeIndex, yMazeIndex);
        }
        sleep(15);
        turnLeft(m1, r1);
        sleep(15);
        findMarker(m1, r1, xMazeIndex, yMazeIndex);
    }
    sleep(150);
    background();
    clear();
    foreground();
    clear();
    setColour(black);
    drawString("Exited Maze Successfully", 400, 400);
}

void generateMaze(struct maze *m1)
{
    srand(time(NULL));
    int curX = 1;
    int curY = 1;
    // set starting point
    (*m1).maze[curX][curY] = 3;
    // generate maze
    carvePath(m1, curX, curY);
    // mark destination
    (*m1).maze[19][20] = 4;
    drawMaze(m1);
}

//inspired from Prim's algorithm
void carvePath(struct maze *m1, int curX, int curY)
{
    int randNo;
    // Check for empty cells around current coordinate
    while ((*m1).visited[curX - 1][curY - 1] == 2 || (*m1).visited[curX][curY - 1] == 2 ||
           (*m1).visited[curX + 1][curY - 1] == 2 || (*m1).visited[curX - 1][curY] == 2 || (*m1).visited[curX][curY] == 2 ||
           (*m1).visited[curX + 1][curY] == 2 || (*m1).visited[curX - 1][curY + 1] == 2 || (*m1).visited[curX][curY + 1] == 2 || (*m1).visited[curX + 1][curY + 1] == 2)
    {
        // Determine which direction to draw path in. 0 -left. 1 -right. 2 -up. 3 -down.
        randNo = rand() % 4;
        if (randNo == 0)
        {
            if ((curX > 1) && ((*m1).visited[curX - 2][curY] == 2))
            {
                curX--;
                // Eliminate wall, and mark as visited, and update coordinate
                (*m1).maze[curX][curY] = 0;
                (*m1).visited[curX][curY] = 0;
                curX--;
                (*m1).visited[curX][curY] = 0;
                carvePath(m1, curX, curY);
                curX += 2;
            }
            // If the path would lead to a loop, leave the wall intact and mark the cell as visted
            else if ((*m1).visited[curX - 2][curY] != 2)
            {
                (*m1).visited[curX - 1][curY] = 1;
            }
        }
        else if (randNo == 1)
        {
            if ((curX < 19) && ((*m1).visited[curX + 2][curY] == 2))
            {
                curX++;
                (*m1).maze[curX][curY] = 0;
                (*m1).visited[curX][curY] = 0;
                curX++;
                (*m1).visited[curX][curY] = 0;
                carvePath(m1, curX, curY);
                curX -= 2;
            }
            else if ((*m1).visited[curX + 2][curY] != 2)
            {
                (*m1).visited[curX + 1][curY] = 1;
            }
        }
        else if (randNo == 2)
        {
            if ((curY > 1) && ((*m1).visited[curX][curY - 2] == 2))
            {
                curY--;
                (*m1).maze[curX][curY] = 0;
                (*m1).visited[curX][curY] = 0;
                curY--;
                (*m1).visited[curX][curY] = 0;
                carvePath(m1, curX, curY);
                curY += 2;
            }
            else if ((*m1).visited[curX][curY - 2] != 2)
            {
                (*m1).visited[curX][curY - 1] = 1;
            }
        }
        else
        {
            if ((curY < 19) && ((*m1).visited[curX][curY + 2] == 2))
            {
                curY++;
                (*m1).maze[curX][curY] = 0;
                (*m1).visited[curX][curY] = 0;
                curY++;
                (*m1).visited[curX][curY] = 0;
                carvePath(m1, curX, curY);
                curY -= 2;
            }
            else if ((*m1).visited[curX][curY + 2] != 2)
            {
                (*m1).visited[curX][curY + 1] = 1;
            }
        }
    }
}

int main(void)
{
    struct maze m1 = {{{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                       {1, 3, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                       {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                       {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                       {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                       {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                       {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                       {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                       {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                       {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                       {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                       {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                       {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                       {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                       {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                       {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                       {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                       {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                       {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                       {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                       {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
                      {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                       {1, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
                       {1, 0, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1},
                       {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
                       {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1},
                       {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
                       {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1},
                       {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
                       {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1},
                       {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
                       {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1},
                       {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
                       {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1},
                       {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
                       {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1},
                       {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
                       {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1},
                       {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
                       {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1},
                       {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
                       {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}}};
    setWindowSize(700, 700);
    generateMaze(&m1);
    struct robot r1 = {{85, 85, 105}, {105, 85, 95}, 'e'};
    drawRobot(&m1, &r1);
    findMarker(&m1, &r1, xMazeIndex, yMazeIndex);
}