#include "wall.h"
#include "maze.h"
/*******************************************************************/
/*                                                                 */
/*  A1 Part 3: runMaze() function                                  */
/*                                                                 */
/*  Author1 Name: Navid Najarali Vadsariya                         */
/*  Author2 Name: Faramarz Hosseini                                */
/*                                                                 */
/*******************************************************************/

#include <iostream>

using namespace std;
//finds path from startCell to endcell
//recursive calls to same function
int recursive(Maze &theMaze, int path[], int startCell, int endCell)
{
    theMaze.mark(startCell);

    int rc = 0;

    int startCellRow = theMaze.getRow(startCell);
    int startCellCol = theMaze.getCol(startCell);

    int top = theMaze.getCell(startCellRow - 1, startCellCol);
    int right = theMaze.getCell(startCellRow, startCellCol + 1);
    int bottom = theMaze.getCell(startCellRow + 1, startCellCol);
    int left = theMaze.getCell(startCellRow, startCellCol - 1);

    if (rc == 0 && top >= 0 && theMaze.canGo(startCell, top) && !theMaze.isMarked(top))
    {
        rc += recursive(theMaze, path, top, endCell);
    }
    if (rc == 0 && right >= 0 && theMaze.canGo(startCell, right) && !theMaze.isMarked(right))
    {
        rc += recursive(theMaze, path, right, endCell);
    }
    if (rc == 0 && bottom >= 0 && theMaze.canGo(startCell, bottom) && !theMaze.isMarked(bottom))
    {
        rc += recursive(theMaze, path, bottom, endCell);
    }
    if (rc == 0 && left >= 0 && theMaze.canGo(startCell, left) && !theMaze.isMarked(left))
    {
        rc += recursive(theMaze, path, left, endCell);
    }
    if (startCell == endCell)
    {
        path[rc] = endCell;
    }

    if (rc > 0)
    {
        path[rc] = startCell;
        rc += 1;
    }
    return (startCell == endCell) ? 1 : rc;
}
//finds path for theMaze
int runMaze(Maze &theMaze, int path[], int startCell, int endCell)
{
    int rc = recursive(theMaze, path, startCell, endCell);
    for (int i = 0; i < rc / 2; i++)
    {
        int temp = path[i];
        path[i] = path[rc - 1 - i];
        path[rc - 1 - i] = temp;
    }
    return rc;
}