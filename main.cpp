#include <iostream>
#include <sstream>
#include <deque>

#include <SFML/Graphics.hpp>
#include "vect.h"

using Path = std::deque<std::pair<double, double>>;
extern VECTOR::Vector process_path(Path& path, double target, double step);


int main()
{
	//create window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Random Walk");
	//setup font & text
	sf::Font font;
	if (!font.loadFromFile("../Source/SourceCodePro-Light.ttf")) {
		std::cerr << "cannot load font2\n";
	}

	//todo: add user input of target & dstep
	//200 is max
	double target = 190;
	double dstep = 1;
	Path path;
	VECTOR::Vector finish = process_path(path, target, dstep);
	//GUI
	sf::CircleShape circle(static_cast<float>(target));
	sf::Vector2f circle_pos{ 
		static_cast<float>(window.getSize().x * 0.5), 
		static_cast<float>(window.getSize().y * 0.2) };
	circle.setPosition(circle_pos);
	circle.setFillColor(sf::Color(217, 217, 217));
	circle.setOutlineThickness(1.0f);
	circle.setOutlineColor(sf::Color::Black);
	
	sf::Text ui_text;
	ui_text.setFont(font);
	ui_text.setCharacterSize(20);
	std::stringstream out;
	out << "After " << path.size() << " steps,\nthe subject's " <<
		"\nlocation is:\n" << finish << "\n" ;
	ui_text.setString(out.str());
	ui_text.setFillColor(sf::Color::Black);
	ui_text.setPosition(window.getSize().x * 0.05, circle_pos.y + circle.getRadius() * 1.2);
	//create vertex array from path
	std::vector<sf::Vertex> vertexes(path.size() + 1);
	vertexes[0] = (sf::Vertex(
		{ static_cast<float>(circle.getPosition().x + circle.getRadius()), static_cast<float>(circle.getPosition().y + circle.getRadius()) }));
	vertexes[0].color = sf::Color::Blue;
	for (unsigned int i = 0; i < vertexes.size() - 1; ++i) {
		vertexes[i + 1] = (sf::Vertex(sf::Vector2f(
			static_cast<float>(path[i].first + circle.getPosition().x + circle.getRadius()),
			static_cast<float>(path[i].second + circle.getPosition().y + circle.getRadius()))));
		vertexes[i + 1].color = sf::Color::Blue;
	}
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::White);
		window.draw(ui_text);
		window.draw(circle);
		window.draw(&vertexes[0], vertexes.size(), sf::LineStrip);
		window.display();
	}

	return 0;
}

