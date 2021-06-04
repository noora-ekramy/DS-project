#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include"maze.h"
#include "pac.h"
#include "gost.h"
#include "our_button.h"
#include<sstream>
#include <fstream>
#include<vector>
#include "rapidxml.hpp"
#include<map>
#include<vector>
#include <cstring>
#include <fstream>
#include "string.h"
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
#include "tinyxml2.cpp"
#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif
using namespace rapidxml;
using namespace sf;
using namespace tinyxml2;

map<string, int >highscormap;
vector<pair<int ,  string>>highscorvector;

xml_document<> doc;
xml_node<>* root_node = NULL;


void reading_from_xmlfile()
{
	
		string name;
		string score;
		int iscore;

		XMLDocument doc;
		const char* path = "XMLFile.xml";
		char accountNumberChar[100];
		doc.LoadFile(path);


		XMLElement* pRootElement = doc.RootElement();
		if (NULL != pRootElement) {

			XMLElement* pmemberss = pRootElement->FirstChildElement("members");
			if (NULL != pmemberss) {

				XMLElement* pmember = pmemberss->FirstChildElement("member");
				while (pmember) {

					XMLElement* pname = pmember->FirstChildElement("name");
					if (NULL != pname) {

						name=pname->GetText();
					}
					//Get 'type' Child
					XMLElement* pscore = pmember->FirstChildElement("score");
					if (NULL != pscore) {

						score=pscore->GetText();

					}
					stringstream nora(score);
					nora >> iscore;
					highscorvector.push_back(make_pair(iscore, name));
					// Next Account
					pmember = pmember->NextSiblingElement("member");
				}

			}

		}
		for (int i = 0; i < highscorvector.size(); i++)
		{
			cout << highscorvector[i].first << " " << highscorvector[i].second << endl;
		}
	
}

void saving_to_xmlfile()
{
	XMLDocument doc;
	const char* path = "XMLFile.xml";
	char accountNumberChar[100];
	doc.LoadFile(path);

	int i = 0;
	XMLElement* pRootElement = doc.RootElement();
	if (NULL != pRootElement) {

		XMLElement* pmemberss = pRootElement->FirstChildElement("members");
		if (NULL != pmemberss) {

			XMLElement* pmember = pmemberss->FirstChildElement("member");
			while (pmember && i<highscorvector.size()) {

				XMLElement* pname = pmember->FirstChildElement("name");
				if (NULL != pname) {
					
					char s[ 100];
					strcpy(s, highscorvector[i].second.c_str());
					pname->SetText(s);
				}
				
				XMLElement* pscore = pmember->FirstChildElement("score");
				if (NULL != pscore) {
					
					string sscore ;
					char s[100];
					sscore = to_string(highscorvector[i].first);
					strcpy(s, sscore.c_str());
					pscore->SetText(s);

				}


				i++;
				pmember = pmember->NextSiblingElement("member");
			}

		}

	}
	doc.SaveFile(path);
}

int level_num = 1;
int maze_num = 1;
bool inf = 0;
sf::Texture bg;
sf::RectangleShape bgsq;
int diffeculty = 4;


sf::RenderWindow window(sf::VideoMode(1050, 960, 32), "pacman");
pac p(window , level_num);
string s1 = "g1.jpeg", s2 = "g2.jpeg", s3 = "g3.jpeg", s4 = "g4.jpeg" ,  s5="fri.jpg";
gost g1(window, s1, 42 * 9, 9 * 42, diffeculty, level_num),
g2(window, s2, 42 * 10, 9 * 42, diffeculty, level_num),
g3(window, s3, 42 * 14, 9 * 42, diffeculty, level_num),
g4(window, s4, 42 * 15, 9 * 42, diffeculty, level_num),
gfri(window, s5, 42 * 15, 9 * 42, diffeculty, level_num),
gfri2(window, s5, 42 * 15, 9 * 42, diffeculty, level_num),
gfri3(window, s5, 42 * 15, 9 * 42, diffeculty, level_num),
gfri4(window, s5, 42 * 15, 9 * 42, diffeculty, level_num);
maze maz(maze_num);
bool menu = 1, game = 0, ABOUT(0), LEVEL(0), SETTINGS(0), RANK(0), mood(0);

int frame = 0;
int frame2 = 0;
int frame3 = 0;
int frame4 = 0;
int pac_frame = 0;
int firmoodfr = 1000;
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
		if (inf)
		{
			maz.maze_arr[g.final_path[n - 1].x][g.final_path[n - 1].y] = 0;
		}

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

	
	p.init(level_num);
	g1.init(level_num, 42 * 9, 9 * 42);
	g2.init(level_num, 42 * 10, 9 * 42);
	g3.init(level_num, 42 * 14, 9 * 42);
	g4.init(level_num, 42 * 15, 9 * 42);
	gfri.init(level_num, 42 * 9, 9 * 42);
	gfri2.init(level_num, 42 * 10, 9 * 42);
	gfri3.init(level_num, 42 * 14, 9 * 42);
	gfri4.init(level_num, 42 * 15, 9 * 42);
	maz.init( level_num , maze_num  , inf);
	 frame = 0;
	frame2 = 0;
	frame3 = 0;
	 frame4 = 0;
	 pac_frame = 0;
 firmoodfr = 1000;

}
bool lose(gost g)
{    
	Vector2f gpos = g.gs.getPosition();
	return(gpos.x / (42 / level_num) == p.x && gpos.y / (42 / level_num) == p.y);
}
int main()
{
	reading_from_xmlfile();
	
	
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("sound2.wav"))
		cout << "yalhwwwwwy";
	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.play();
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
					inti();
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
		if (ABOUT)
		{
		
			window.clear();
			our_button back("BACk", 30, 30 * 28, 75, 175, window);
			window.clear();
			our_button ab1("Pac-Man[a] is a maze action game developed and released by Namco for arcades in 1980. The original " , 40 , 30 , 20 , window);
			ab1.display(window);

			our_button ab2("Japanese title of Puck Man was changed to Pac-Man for international releases as a preventative", 40, 30+30, 20, window);
			ab2.display(window);
			our_button ab3("measure against defacement of the arcade machines by changing the P to an In North America, the game was  ", 40, 30+ 30*2, 20, window);
			ab3.display(window);
			our_button ab4("released by Midway Manufacturing as part of its licensing agreement with Namco America. The player", 40, 30*4, 20, window);
			ab4.display(window);
			our_button ab5("controls Pac-Man, who must eat all the dots inside an enclosed maze while avoiding four colored ghosts.", 40, 30*5, 20, window);
			ab5.display(window);
			our_button ab6(" Eating large flashing dots called 'Power Pellets' causes the ghosts to turn blue,", 40, 30*6, 20, window);
			ab6.display(window);
			our_button ab7(" allowing Pac-Man to eat them for bonus points.", 40, 30*7, 20, window);
			ab7.display(window);
			our_button ab8("Game development began in early 1979, directed by Toru Iwatani with a nine-man team. Iwatani wanted ", 40, 30*8, 20, window);
			ab8.display(window);
			our_button ab9("to create a game that could appeal to women as well as men, because most video games of the time had themes ", 40, 30 + 30*8, 20, window);
			ab9.display(window);
			our_button ab10("of war or sports. [citation needed] Although the inspiration for the Pac-Man character was, reportedly, ", 40, 30 + 30 * 9, 20, window);
			ab10.display(window);
			our_button ab11("the image of a pizza with a slice removed, Iwatani has said he also rounded out the Japanese  character for mouth, ", 40, 30 * 11, 20, window);
			ab11.display(window);
			our_button ab12("kuchi (Japanese: 口). The in-game characters were made to be cute and colorful to appeal to younger players.", 40, 30 * 12, 20, window);
			ab12.display(window);
			our_button ab13(" The original Japanese title of Puckman was derived from the titular character's hockey-puck shape.", 40, 30 * 13, 20, window);
			ab13.display(window);
			our_button ab14(" DEVOLEPERS", 400, 30 * 14, 40, window);
			ab14.display(window);
			our_button ab15(" NORA EKRAMY", 400, 30 * 16 , 35, window);
			ab15.display(window);
			our_button ab16("MOSTAFA ABOELNOUR ", 400, 30 * 18 , 35, window);
			ab16.display(window);
			our_button ab17(" MOHAMMED SAID", 400, 30 * 20 , 35, window);
			ab17.display(window);
			our_button ab18(" HAGER SALEM", 400, 30 * 22 , 35, window);
			ab18.display(window);
			our_button ab19(" MOHAMMED REFAT", 400, 30 * 24 , 35, window);
			ab19.display(window);
			our_button ab20(" MARAWAN ELGENDY", 400, 30 * 26 , 35, window);
			ab20.display(window);




			back.checkClick(event.mouseMove.x, event.mouseMove.y, window);
			if (back.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))))
			{

				menu = 0; game = 0; ABOUT = 0; LEVEL = 0; SETTINGS = 0; RANK = 0;
				back.change_page(menu);
			}
			window.display();
			window.clear();
		}
		if (game) {

				window.clear();
				maz.display(window);

				
				frame++;
				frame2++;
				frame3++;
				frame4++;
				pac_frame++;
				p.set_mood(mood);
		
				
				if (!inf && maz.allpoint == 0)
				{
					if (maze_num < 3)
					{
						maze_num++;
						level_num = 2;
						if (maze_num == 2 ) 
						{
							maz.allpoint = 1041;
						}
						if (maze_num == 3)
						{
							maz.allpoint = 1006;
						}
					}
					else
					{
						maze_num = 1;
						level_num = 1;
						maz.allpoint = 250;
						diffeculty += 2;

						continue;
					}
					inti();

				}
				if (mood)
				{
					firmoodfr--;

					if (frame == 300 / g1.speed) {
						frame = 0;
						int x, y;
						randmize_pos(x, y, 20, 20, 1, 0);
						gfri.gs.setPosition(g1.gs.getPosition().x, g1.gs.getPosition().y);
						move(g1, x, y);
						move(gfri, x, y);
						gfri.gs.setPosition(g1.gs.getPosition().x, g1.gs.getPosition().y);
						gfri.gs.getPosition();
						

					}
					if (frame2 == 300 / g2.speed) {
						frame2 = 0;
						int x, y;
						randmize_pos(x, y, 20, 20, 1, 0);
						move(g2, x, y);
						gfri2.gs.setPosition(g2.gs.getPosition().x, g2.gs.getPosition().y);
						
					}
					if (frame3 == 300 / g3.speed) {
						frame3 = 0;

						int x, y;
						randmize_pos(x, y, 22, 10, 0, 0);
						move(g3, x, y);
						gfri3.gs.setPosition(g3.gs.getPosition().x, g3.gs.getPosition().y);
						


					}
					if (frame4 == 300 / g4.speed) {
						frame4 = 0;
						int x, y;
						randmize_pos(x, y, 12, 10, 0, 0);
						move(g4, x, y);
						gfri4.gs.setPosition(g4.gs.getPosition().x, g4.gs.getPosition().y);
						


					}
					if (pac_frame == 1)
					{
						pac_frame = 0;
						p.move(maz);


					}
					if (firmoodfr == 2)
					{
						g1.set_pic(s1, level_num);
						g2.set_pic(s2, level_num);
						g3.set_pic(s3, level_num);
						g4.set_pic(s4, level_num);
						mood = 0;
						p.get_mood(mood);
						firmoodfr = 1000;

					}
					window.draw(gfri.gs);
					window.draw(gfri2.gs);
					window.draw(gfri3.gs);
					window.draw(gfri4.gs);
				}
				else
				{
					if (lose(g1) || lose(g2) || lose(g3) || lose(g4))
					{
						game = 0;
						menu = 1;
						inti();
						continue;
					}

					if (frame == 300 / g1.speed) {
						frame = 0;
						Vector2f gpos = g1.gs.getPosition();
						move(g1, p.x, p.y);

					}
					if (frame2 == 300 / g2.speed) {
						frame2 = 0;
						int x, y;
						randmize_pos(x, y, 20, 20, 1, 0);
						move(g2, x, y);
					}
					if (frame3 == 300 / g3.speed) {
						frame3 = 0;

						int x, y;
						randmize_pos(x, y, 22, 10, 0, 0);
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
					window.draw(g1.gs);
					window.draw(g2.gs);
					window.draw(g3.gs);
					window.draw(g4.gs);

				}
				string sscore;
				sscore = to_string(p.score);

				our_button ga1(sscore, 150, 900, 30, window);
				our_button ga2("Score : ", 30, 900, 30, window);

				ga1.display(window);
				ga2.display(window);

				window.draw(p.pac_man);


				window.display();
	
			
		}
		if (SETTINGS)
		{
			window.clear();
			our_button maze1("Maze1", 100, 430, 50, 175, window),
				maze2("Maze2", 450, 430, 50, 350, window),
				maze3("Maze3", 800, 430, 50, 210, window),
				d1("Easy", 100, 600, 50, 175, window),
				d2("Medium", 450, 600, 50, 350, window),
				d3("Hard", 800, 600, 50, 210, window),
                f1("Finite", 100, 770, 50, 350, window),
				f2("Final distnation", 500, 770, 50, 210, window);
			sf::CircleShape c1 , c2 , c3;
			c1.setRadius(5);
			c2.setRadius(5);
			c3.setRadius(5);
			c1.setFillColor(Color::Green);
			c2.setFillColor(Color::Green);
			c3.setFillColor(Color::Green);
			c1.setPosition(Vector2f(80, 460));
			c2.setPosition(Vector2f(80, 630));
			c3.setPosition(Vector2f(80, 800));

			our_button back("BACk", 30, 30 * 28, 50, 175, window);
			window.clear();

			our_button ab1("Select the maze : ", 40, 20, 30, window);
			ab1.display(window);
			our_button stt1("Mood : ", 40, 700, 30, window);
			stt1.display(window);
			our_button stt2("Difficulty :", 40, 520, 30, window);
			stt2.display(window);

			sf::Texture st1;
			sf::RectangleShape st1s;
			st1.loadFromFile("Capture1.png");
			st1s.setTexture(&st1);
			st1s.setPosition(sf::Vector2f(50, 100));
			st1s.setSize(Vector2f(300,300 ));

			sf::Texture st2;
			sf::RectangleShape st2s;
			st2.loadFromFile("2.png");
			st2s.setTexture(&st2);
			st2s.setPosition(sf::Vector2f(400, 100));
			st2s.setSize(Vector2f(300,300));

			sf::Texture st3;
			sf::RectangleShape st3s;
			st3.loadFromFile("Capture3.png");
			st3s.setTexture(&st3);
			st3s.setPosition(sf::Vector2f(750, 100));
			st3s.setSize(Vector2f(300, 300));



			maze1.checkClick(event.mouseMove.x, event.mouseMove.y, window);
			maze2.checkClick(event.mouseMove.x, event.mouseMove.y, window);
			maze3.checkClick(event.mouseMove.x, event.mouseMove.y, window);
			d1.checkClick(event.mouseMove.x, event.mouseMove.y, window);
			d2.checkClick(event.mouseMove.x, event.mouseMove.y, window);
			d3.checkClick(event.mouseMove.x, event.mouseMove.y, window);
			f1.checkClick(event.mouseMove.x, event.mouseMove.y, window);
			f2.checkClick(event.mouseMove.x, event.mouseMove.y, window);
			if (maze_num == 2)
			{
				c1.setPosition(Vector2f(430, 460));
			}
			else if (maze_num == 3)
			{
				c1.setPosition(Vector2f(780, 460));
			}
			if (diffeculty == 6)
			{
				c2.setPosition(Vector2f(430, 630));
			}
			else if (diffeculty == 8)
			{
				c2.setPosition(Vector2f(780, 630));
			}
			if (inf)
			{
				c3.setPosition(Vector2f(480, 800));

			}
			if (maze1.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))))
			{
				maze_num = 1;
				level_num = 1;
			}

			if (maze2.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))))
			{
				maze_num = 2;
				level_num = 2;

			}
			if (maze3.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))))
			{
				maze_num = 3;
				level_num = 2;
			}

			if (d1.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))))
			{
				diffeculty = 4;
			}

			if (d2.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))))
			{
				diffeculty = 6;
			}
			if (d3.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))))
			{
				diffeculty = 8;
			}
			if (f1.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))))
			{
				inf = 0;
			}

			if (f2.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))))
			{
				inf = 1;
			}

			window.draw(st1s);
			window.draw(st2s);
			window.draw(st3s);
			window.draw(c1);
			window.draw(c2);
			window.draw(c3);

			back.checkClick(event.mouseMove.x, event.mouseMove.y, window);
			if (back.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))))
			{

				menu = 0; game = 0; ABOUT = 0; LEVEL = 0; SETTINGS = 0; RANK = 0;
				back.change_page(menu);
			}
			window.display();
			window.clear();

		}
		if (RANK)
		{


			window.clear();
			our_button back("BACk", 30, 30 * 28, 75, 175, window);
			window.clear();

			for (int i = 4; i >= 0; i++)
			{
				our_button ab2("NAME", 40, 30, 30, window);
				ab2.display(window);
				our_button ab3("SCore", 300, 30, 30, window);
				ab3.display(window);
				if (highscorvector[i].second == "0")
				{
					our_button ab1("..... ", 40, 30 + (5-i) * 50, 20, window);
					ab1.display(window);
					our_button ab4("..... ", 300, 30 + (5 - i) * 50, 20, window);
					ab4.display(window);
				}
				else
				{
					our_button ab1(highscorvector[i].second, 40, 30 + (5 - i) * 50, 20, window);
					ab1.display(window);
					our_button ab4(to_string(highscorvector[i].first), 300, 30 + (5 - i) * 50, 20, window);
					ab4.display(window);
				}
			}
			back.checkClick(event.mouseMove.x, event.mouseMove.y, window);
			if (back.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))))
			{

				menu = 0; game = 0; ABOUT = 0; LEVEL = 0; SETTINGS = 0; RANK = 0;
				back.change_page(menu);
			}
			window.display();
			window.clear();
			
		}
	}

	return 0;
}