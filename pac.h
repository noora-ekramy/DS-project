#include<SFML/Graphics.hpp>
#include<iostream>
#include"maze.h"
class pac
{
public:
	sf::Texture pacman_pic;
	sf::CircleShape pac_man;
	sf::RenderWindow window;
	pac(sf::RenderWindow& window , int num);
	sf::Vector2f position;
	int score = 0 ,speed=3;
	int  x ,y;
	int dirction=0;
	bool mood;
	int level_number;
	void move(maze& maze);
	void set_mood(bool& mood1)
	{
		mood1 = mood;
	}
	void get_mood(bool mood1)
	{
		mood = mood1;
	}
	void action(maze& maze);
};
