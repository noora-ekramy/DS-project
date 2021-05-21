#include "maze.h"
#include<iostream>
using namespace std;
void maze::display()
{
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			if (maze_arr[i][j] == 1)
			{
				cout << " ";
		    }
			else if(maze_arr[i][j] == 2)
			{
				cout << "#";
			}
			else if(maze_arr[i][j] == 3)
			{
				cout << " ";
			}
			else if (maze_arr[i][j] == 4)
			{
				cout << ".";
			}
			else if (maze_arr[i][j] == 5)
			{
				cout << "o";
			}
			else
			{
				cout << " ";
			}
			

		}
		cout << endl;
	}
}
