#include <SFML/Graphics.hpp>
#include<iostream>
#include"maze.h"
#include "pac.h"
#include "gost.h"
#include "our_button.h"
using namespace sf;
int level_num = 2;

sf::Texture bg;
sf::RectangleShape bgsq;



sf::RenderWindow window(sf::VideoMode(1050, 960, 32), "pacman");
pac p(window , level_num);
string s1 = "g1.jpeg", s2 = "g2.jpeg", s3 = "g3.jpeg", s4 = "g4.jpeg";
gost g1(window, s1, 42 * 9    , 9 * 42, 4, level_num),
g2(window, s2, 42 * 10     , 9 * 42, 4, level_num),
g3(window, s3, 42 * 14     , 9 * 42, 4, level_num),
g4(window, s4, 42 * 15     , 9 * 42, 4, level_num);
maze maz(2);
void move(gost& g, int tx, int ty) {
	Vector2f gpos = g.gs.getPosition();
	g.BFS(gpos.y / (42/level_num), gpos.x /( 42/ level_num), ty, tx, maz.maze_arr);
	int n = g.final_path.size();

	if (n > 0)
	{
		int a = g.final_path[n - 1].x * (42/ level_num),
			b = g.final_path[n - 1].y * (42/ level_num);
		g.gs.setPosition(Vector2f(b, a));
		gpos = g.gs.getPosition();


		g.final_path.pop_back();
	}
}
void randmize_pos(int& x, int& y, int modx, int mody, bool placex, bool placey)
{
	do
	{
		modx *= level_num;
		mody *= level_num;
		x = (rand() % modx) + (placex * 10);
		y = (rand() % mody) + ((placey) * 10);
	} while (maz.maze_arr[x* level_num][y* level_num] == 2);
}
void inti() {

	pac p(window , level_num);
	string s1 = "g1.jpeg", s2 = "g2.jpeg", s3 = "g3.jpeg", s4 = "g4.jpeg";
	gost g1(window, s1, 42 * 9, 9 * 42, 4 , level_num),
		g2(window, s2, 42 * 10, 9 * 42, 4, level_num),
		g3(window, s3, 42 * 14, 9 * 42, 4, level_num),
		g4(window, s4, 42 * 15, 9 * 42, 4, level_num);
	maze maz(1);


}
int main()
{
	bool menu = 1, game = 0, ABOUT(0), LEVEL(0), SETTINGS(0), RANK(0);
	int frame = 0;
	int frame2 = 0;
	int frame3 = 0;
	int frame4 = 0;
	int pac_frame = 0;

	bg.loadFromFile("bg1.jpg");
	bgsq.setTexture(&bg);
	bgsq.setPosition(sf::Vector2f(0 , 0));
	bgsq.setSize(Vector2f(1050, 960));


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
			case sf::Event::MouseMoved:

			default:
				break;
			}
		}
		if (menu) {

			our_button play("Play", 30 * 15, 30 * 5, 75,175, window),
				settings("Settings", 30 * 13, 30 * 10, 75, 350, window),
				rank("Rank", 30 * 15, 30 * 15, 75, 210, window),
				exit("Exit", 30 * 15, 30 * 25, 75, 175, window),
				about("About", 30 * 14, 30 *20, 75, 250, window)
				;

			window.clear();
			if (Event::MouseMoved) {
				
				
				window.draw(bgsq);
				play.checkClick(event.mouseMove.x, event.mouseMove.y, window);
				rank.checkClick(event.mouseMove.x, event.mouseMove.y, window);
				exit.checkClick(event.mouseMove.x, event.mouseMove.y, window);
				about.checkClick(event.mouseMove.x, event.mouseMove.y, window);
				settings.checkClick(event.mouseMove.x, event.mouseMove.y, window);


				if (play.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))))
				{
					
					menu = 0; game = 0; ABOUT = 0; LEVEL = 0; SETTINGS = 0; RANK = 0;
					play.change_page(game);
				}
				
				if (rank.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))))
				{
					menu = 0; game = 0; ABOUT = 0; LEVEL = 0; SETTINGS = 0; RANK = 0;
					rank.change_page(RANK);
				}
				if (exit.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))))
				{
					menu = 0; game = 0; ABOUT = 0; LEVEL = 0; SETTINGS = 0; RANK = 0;
					window.close();
					return 0;
				}
				if (about.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))))
				{
					menu = 0; game = 0; ABOUT = 0; LEVEL = 0; SETTINGS = 0; RANK = 0;
					about.change_page(ABOUT);
				}
				if (settings.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))))
				{
					menu = 0; game = 0; ABOUT = 0; LEVEL = 0; SETTINGS = 0; RANK = 0;
					settings.change_page(SETTINGS);
				}

		
			}


			window.display();
			window.clear();
		}

		if (game) {
			frame++;
			frame2++;
			frame3++;
			frame4++;
			pac_frame++;

			if (frame == 300 / g1.speed) {
				frame = 0;
				Vector2f gpos = g1.gs.getPosition();
				move(g1, p.x, p.y);

			}
			if (frame2 == 300 / g2.speed) {
				frame2 = 0;
				int x, y;
				randmize_pos(x, y, 12, 10, 1, 0);
				move(g2, x, y);
			}
			if (frame3 == 300 / g3.speed) {
				frame3 = 0;

				int x, y;
				randmize_pos(x, y, 12, 10, 0, 1);
				move(g3, x, y);


			}
			if (frame4 == 300 / g4.speed) {
				frame4 = 0;
				int x, y;
				randmize_pos(x, y, 12, 10, 0, 0);
				move(g4, x, y);

			}
			if (pac_frame == 2)
			{
				pac_frame = 0;
				p.move(maz);


			}


			window.clear();
			maz.display(window);
			window.draw(p.pac_man);
			window.draw(g1.gs);
			window.draw(g2.gs);
			window.draw(g3.gs);
			window.draw(g4.gs);

			window.display();
			
		}
	}

	return 0;
}