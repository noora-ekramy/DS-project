#include "our_button.h"
#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>
#include<sstream>
///#include<>
using namespace std;
our_button::our_button(string words, int posx, int posy, int size, int xrect, sf::RenderWindow& window)
{
	sz = size;
	stringstream ss;
	//Font font;
	font.loadFromFile("ZCOOLKuaiLe-Regular.ttf");
	text.setFont(font);
	ss << words;
	text.setString(ss.str());
	text.setFillColor(sf::Color(224, 227, 19));
	text.setCharacterSize(sz);
	text.setPosition(posx, posy);
	text.getPosition();
	window.draw(text);
	rect.setSize(sf::Vector2f(xrect, sz + 30));
	rect.setPosition(posx, posy);
	text.getPosition();
	rect.setFillColor(sf::Color(172, 175, 183));


}
void our_button::checkClick(int x, int y, sf::RenderWindow& window) {
	sf::Event e;

	if (x > rect.getPosition().x && x < rect.getPosition().x + rect.getSize().x) {
		if (y > rect.getPosition().y && y < rect.getPosition().y + rect.getSize().y) {
			rect.setFillColor(sf::Color(43, 60, 106));
			text.setFillColor(sf::Color::White);
			text.setCharacterSize(sz + 5);
			window.draw(rect);
			window.draw(text);
	
	
					//clicked = 1;


		}


	}
	window.draw(text);

}

void our_button::change_page(bool& ok)
{
		ok = 1;
}