#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>
#include<sstream>

using namespace std;
class our_button
{
public:
	sf::Font font;
	sf::Text text;
	sf::RectangleShape rect;
	sf::RenderWindow window;
	our_button(string words, int posx, int posy, int sz, int xrect, sf::RenderWindow& window);
	void checkClick(int x, int y, sf::RenderWindow& window);
	void setText(std::string);
	bool getVar();
	int sz;
	void change_page(bool& ok);
	bool clicked = 0;
	sf::String String;
	our_button( string mtext ,  int posx , int posy , int sz, sf::RenderWindow& window);
	void display(sf::RenderWindow& window);
};