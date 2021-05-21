#include<iostream>
#include<vector>
using namespace std;
class gost
{
public:
	int x_position;
	int y_position;
	bool vis[19][20] = {0};
	struct path 
	{
		int x;
		int y;
		int brv;
	};
	struct npair
	{
		int x;
		int y;
	};
	vector<path>nodes;
	vector<npair>final_path;
	int dx[4] = { 1,-1,0,0 };
	int dy[4] = { 0,0,-1,1 };
	



	void display();
	void BFS(int g_x, int g_y, int t_x, int t_y, int maze_arr[23][23]);
};

