#include "gost.h"

void gost::move() {

}
gost::gost(sf::RenderWindow& window, string s, int x, int y ,int spd ,int level_number) {

    if (!gt.loadFromFile(s))
    {
        cout << "hello world";
    }
    gs.setTexture(&gt);
    gs.setSize(Vector2f(30.f/level_number ,30.f/ level_number));
    gs.setPosition(sf::Vector2f(x/ level_number, y/ level_number));
    speed = spd;


}
void gost::BFS(int x_position, int y_position,int t_x, int t_y, int maze_arr[42][50])
{
    memset(vis, 0, sizeof vis);
    nodes.clear();
    vis[x_position][y_position] = 1;

    path add_point;
    add_point.x = x_position;
    add_point.y = y_position;
    add_point.brv = -1;
    nodes.push_back(add_point);
    int node = 0;
    while (node < nodes.size())
    {
        for (int i = 0; i < 4; i++)
        {
            int xx = nodes[node].x + dx[i], yy = nodes[node].y + dy[i];

            if (maze_arr[xx][yy] != 1 && !vis[xx][yy])
            {
                vis[xx][yy] = 1;
                add_point.x = xx;
                add_point.y = yy;
                add_point.brv = node;
                nodes.push_back(add_point);
                if (xx == t_x && yy == t_y)
                {

                    final_path.clear();
                    npair temp;
                    temp.x = xx;
                    temp.y = yy;
                    final_path.push_back(temp);
                    while (nodes[node].brv != -1) {

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