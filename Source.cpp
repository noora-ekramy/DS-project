#include <iostream>
#include"maze.h"
#include"gost.h"
#include<vector>
using namespace std;
int main()
{
	maze lol;
	lol.display();
	int x1 = 1, y1 = 1;
	int x2 = 2, y2 = 9;
	gost lol1;
	lol1.BFS(x1, y1, x2, y2, lol.maze_arr);
	for (int i = 0; i < lol1.final_path.size(); i++)
	{
		
		cout << lol1.final_path[i].x << " " << lol1.final_path[i].y << endl;
	}

}