#include <iostream>
#include <deque>

#include <SFML/Graphics.hpp>
#include "vect.h"

int main()
{
	using VECTOR::Vector;
	std::srand(time(0));
	double direction = 0.0;
	Vector step;
	Vector result(0.0, 0.0);
	std::deque<std::pair<double, double>> map;
	unsigned long steps = 0;
	double target = 300;
	double dstep = 10;
	//user input here
	while (result.magval() < target) {
		direction = std::rand() % 360;
		step.reset(dstep, direction, Vector::POL);
		result = result + step;
		map.push_back(std::make_pair(result.xval(), result.yval()));
		++steps;
	}

	std::cout << "After " << steps << " steps, the subject "
		"has the following location:\n";
	std::cout << result << std::endl;
	result.polar_mode();
	std::cout << "or\n" << result << std::endl;
	std::cout << "Average outward distance per step = "
		<< result.magval() / steps << std::endl;

	//result here
	//create window
	sf::RenderWindow window(sf::VideoMode(1000, 800), "Random Walk");
	sf::CircleShape circle(static_cast<float>(target));
	sf::Vector2f circle_pos{ 100.0f, 100.0f };
	circle.setPosition(circle_pos);
	circle.setFillColor(sf::Color(217, 217, 217));
	circle.setOutlineThickness(1.0f);
	circle.setOutlineColor(sf::Color::Black);
	//create path
	std::vector<sf::Vertex> path(map.size() + 1);
	path[0] = (sf::Vertex(
		{ static_cast<float>(circle.getPosition().x + circle.getRadius()), static_cast<float>(circle.getPosition().y + circle.getRadius()) }));
	path[0].color = sf::Color::Blue;
	for (unsigned int i = 0; i < map.size(); ++i) {
		path[i + 1] = (sf::Vertex(sf::Vector2f(
			static_cast<float>(map[i].first + circle.getPosition().x + circle.getRadius()), 
			static_cast<float>(map[i].second + circle.getPosition().y + circle.getRadius()))));
		path[i + 1].color = sf::Color::Blue;
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
		window.draw(circle);
		window.draw(&path[0], path.size(), sf::LineStrip);
		window.display();
	}

	return 0;
}
