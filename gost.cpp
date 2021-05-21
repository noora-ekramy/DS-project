#include "gost.h"
void gost::BFS(int g_x, int g_y, int t_x, int t_y  , int maze_arr[23][23] )
{
	memset(vis, 0, sizeof vis);
	nodes.clear();
	vis[g_x][g_y] = 1;

	path add_point;
	add_point.x = g_x;
	add_point.y = g_y;
	add_point.brv = -1;
	nodes.push_back(add_point);
	int node = 0;
	while (node < nodes.size())
	{
		for (int i = 0; i < 4; i++)
		{
			int xx = nodes[node].x + dx[i], yy = nodes[node].y + dy[i];

			if (maze_arr[xx][yy] != 2 && maze_arr[xx][yy] != 7 && !vis[xx][yy])
			{
				vis[xx][yy] = 1;
				add_point.x = xx;
				add_point.y = yy;
				add_point.brv = node;
				nodes.push_back(add_point);
				if (xx==t_x && yy==t_y)
				{
					
					final_path.clear();
					npair temp;
					temp.x = xx;
					temp.y = yy;
					final_path.push_back(temp);
					while (nodes[node].brv!=-1) {
						
						temp.x = nodes[node].x;
						temp.y = nodes[node].y;
						
						final_path.push_back(temp);
						node = nodes[node].brv;

					}
					return;
					
				}


			}

		}
		node++;
	}
	

}
