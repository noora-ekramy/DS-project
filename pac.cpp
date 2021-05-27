#include "pac.h"
#include<iostream>
#include<vector>
#include "maze.h"
#include"our_button.h"
using namespace std;
pac::pac(sf::RenderWindow& window , int num)
{//
	mood = 0;
	level_number = num;
	if (!pacman_pic.loadFromFile("pac_man.jpg"))
	{
		cout << "hello world";
	}
	pac_man.setTexture(&pacman_pic);
	pac_man.setRadius(15/level_number);
	pac_man.setPosition(sf::Vector2f(12 * 42 , 15 * 42));
	window.draw(pac_man);
	
	//pac_man.setOrigin(30 * 42, 30 * 42 + 10);
}
void pac::move(maze& maze)
{
	sf::Vector2f pos = pac_man.getPosition();
	y = pos.y  / (42/ level_number);
	x = pos.x / (42/level_number);
	
	sf::Vector2f pos_rotate;
	action(maze);

	 if (dirction == 1) // done
	{

		if (int((pos.y - 1) / (42 / level_number)) >= 0 && maze.maze_arr[int((pos.y - 1) / (42 / level_number))][int(pos.x / (42 / level_number))] != 1)
		{
			if (maze.maze_arr[int((pos.y - 1) / (42 / level_number))][int(pos.x / (42 / level_number))] == 0)
			{
				maze.maze_arr[int((pos.y - 1) / (42 / level_number))][int(pos.x / (42 / level_number))] = 2;
				score++;
			}
			if (maze.maze_arr[int((pos.y - 1) / (42 / level_number))][int(pos.x / (42 / level_number))] == 4)
			{
				maze.maze_arr[int((pos.y - 1) / (42 / level_number))][int(pos.x / (42 / level_number))] = 2;
				score += 50;
				mood = 1;
			}
			pac_man.move(0, -speed);
			//sprite.setRotation(270);

		    pos_rotate = pac_man.getPosition();
			//pac_man.setPosition(pos_rotate.x + 15 / level_number, pos_rotate.y + 15 / level_number);


		}
	}
	else if (dirction == 2) // done
	{
		if (int((pos.y + 1) / (42 / level_number)) + 1 < (21 * level_number) && maze.maze_arr[int((pos.y + 1) / (42 / level_number)) + 1][int(pos.x / (42 / level_number))] != 1)
		{
			if (maze.maze_arr[int((pos.y + 1) / (42 / level_number)) + 1][int(pos.x / (42 / level_number))] == 0)
			{
				maze.maze_arr[int((pos.y + 1) / (42 / level_number)) + 1][int(pos.x / (42 / level_number))] = 2;
				score++;
			}
			if (maze.maze_arr[int((pos.y + 1) / (42 / level_number)) + 1][int(pos.x / (42 / level_number))] == 4)
			{
				maze.maze_arr[int((pos.y + 1) / (42 / level_number)) + 1][int(pos.x / (42 / level_number))] = 2;
				score += 50;
				mood = 1;
			}
			pac_man.move(0, speed);
			//pac_man.setRotation(90);

			pos_rotate = pac_man.getPosition();
			//pac_man.setPosition(pos_rotate.x + 15 / level_number, pos_rotate.y + 15 / level_number);

		}
	}
	else if (dirction == 3) // DONE
	{

		if (maze.maze_arr[int(pos.y / (42 / level_number))][int((pos.x + 1) / (42 / level_number)) + 1] != 5)
		{
			if (int((pos.x + 1) / (42 / level_number)) + 1 < (25 * level_number) && maze.maze_arr[int(pos.y / (42 / level_number))][int((pos.x + 1) / (42 / level_number)) + 1] != 1)
			{
				if (maze.maze_arr[int(pos.y / (42 / level_number))][int((pos.x + 1) / (42 / level_number)) + 1] == 0)
				{
					maze.maze_arr[int(pos.y / (42 / level_number))][int((pos.x + 1) / (42 / level_number)) + 1] = 2;
					score++;
				}
				if (maze.maze_arr[int(pos.y / (42 / level_number))][int((pos.x + 1) / (42 / level_number)) + 1] == 4)
				{
					maze.maze_arr[int(pos.y / (42 / level_number))][int((pos.x + 1) / (42 / level_number)) + 1] = 2;
					score += 50;
					mood = 1;
				}
				pac_man.move(speed, 0);
				//pac_man.setRotation(0);


				pos_rotate = pac_man.getPosition();
				//pac_man.setPosition(pos_rotate.x + 15 / level_number, pos_rotate.y + 15 / level_number);
			}

		}
	}
	else if (dirction == 4)
	{
		
		if (maze.maze_arr[int(pos.y / (42 / level_number))][int((pos.x - 1) / (42 / level_number))] != 5)
		{
			if ((int(pos.x - 1) / (42 / level_number)) - 1 >= 0 && maze.maze_arr[int(pos.y / (42 / level_number))][int((pos.x - 1) / (42 / level_number))] != 1)
			{
				if (maze.maze_arr[int(pos.y / (42 / level_number))][int((pos.x - 1) / (42 / level_number))] == 0)
				{
					maze.maze_arr[int(pos.y / (42 / level_number))][int((pos.x - 1) / (42 / level_number))] = 2;
					score++;
				}
				if (maze.maze_arr[int(pos.y / (42 / level_number))][int((pos.x - 1) / (42 / level_number))] == 4)
				{
					maze.maze_arr[int(pos.y / (42 / level_number))][int((pos.x - 1) / (42 / level_number))] = 2;
					score += 50;
					mood = 1;
				}
				
				pac_man.move(-speed, 0);
				
				//sprite.setRotation(180);


				pos_rotate = pac_man.getPosition();
				//pac_man.setPosition(pos_rotate.x + 15, pos_rotate.y + 15);
			}
		}
	}



}

void pac::action(maze& maze)
{

	sf::Vector2f pos = pac_man.getPosition();
	

	if (abs(pos.x - int(pos.x)) == 0 && abs(pos.y - int(pos.y)) == 0
		&& int(pos.y) % (42 / level_number) == 0 && int(pos.x) % (42 / level_number) == 0)
	{
		if (abs(pos.y - int(pos.y)) == 0 && int(pos.y) % (42 / level_number) == 0 && Keyboard::isKeyPressed(Keyboard::Up)
			&& int((pos.y - 1) / (42 / level_number)) >= 0 && maze.maze_arr[int((pos.y - 1) / (42 / level_number))][int(pos.x / (42 / level_number))] != 1)
		{
			
			dirction = 1;
		}
		else if (abs(pos.y - int(pos.y)) == 0 && int(pos.y) % (42 / level_number) == 0 && Keyboard::isKeyPressed(Keyboard::Down)
			&& int((pos.y + 1) / (42 / level_number)) + 1 < (21 * level_number) && maze.maze_arr[int((pos.y + 1) / (42 / level_number)) + 1][int(pos.x / (42 / level_number))] != 1)
		{
			
			dirction = 2;
		}
		else if (abs(pos.x - int(pos.x)) == 0 && Keyboard::isKeyPressed(Keyboard::Right)
			&& int((pos.x + 1) / (42 / level_number)) + 1 < (25 * level_number) && maze.maze_arr[int(pos.y / (42 / level_number))][int((pos.x + 1) / (42 / level_number)) + 1] != 1)
		{
			
			dirction = 3;
		}
		else if (abs(pos.x - int(pos.x)) == 0 && int(pos.x) % (42 / level_number) == 0 && Keyboard::isKeyPressed(Keyboard::Left)
			&& (int(pos.x - 1) / (42 / level_number)) - 1 >= 0 && maze.maze_arr[int(pos.y / (42 / level_number))][int((pos.x - 1) / (42 / level_number))] != 1)
		{
			
			dirction = 4;
		}
		
	}
	
}