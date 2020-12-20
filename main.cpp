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
	sf::RenderWindow window(sf::VideoMode(1100, 700), "Random Walk", sf::Style::Titlebar | sf::Style::Close);
	//setup font, texts, shapes for user input
	sf::Font font;
	if (!font.loadFromFile("../Source/good_times_rg.ttf")) {
		std::cerr << "cannot load font2\n";
	}
	sf::Text text_input_distanse;
	text_input_distanse.setFont(font);
	text_input_distanse.setCharacterSize(20);
	text_input_distanse.setString("Enter distance to walk");
	text_input_distanse.setFillColor(sf::Color::Black);
	text_input_distanse.setPosition(window.getSize().x * 0.05f, 10);
	int vertical_shift = 40;
	sf::RectangleShape input_distance_field(sf::Vector2f(text_input_distanse.getLocalBounds().width, text_input_distanse.getLocalBounds().height * 2));
	input_distance_field.setPosition(text_input_distanse.getGlobalBounds().left, text_input_distanse.getGlobalBounds().top + vertical_shift);
	input_distance_field.setOutlineThickness(1);
	input_distance_field.setOutlineColor(sf::Color::Black);
	sf::Text text_input_dstep(text_input_distanse);
	text_input_dstep.setString("Enter length of step");
	text_input_dstep.setPosition(input_distance_field.getGlobalBounds().left,
		input_distance_field.getGlobalBounds().top + input_distance_field.getLocalBounds().height + vertical_shift);
	sf::RectangleShape input_dstep_field(input_distance_field);
	input_dstep_field.setPosition(text_input_dstep.getGlobalBounds().left, text_input_dstep.getGlobalBounds().top + vertical_shift);
	std::string distance_str;
	std::string dstep_str;
	sf::Text text_user_input_distance(text_input_distanse);
	text_user_input_distance.setString(distance_str);
	text_user_input_distance.setPosition(input_distance_field.getPosition());
	sf::Text text_user_input_dstep(text_input_distanse);
	text_user_input_dstep.setString(dstep_str);
	text_user_input_dstep.setPosition(input_dstep_field.getPosition());
	//restart "button"
	sf::RectangleShape button_restart(input_distance_field);
	button_restart.setPosition(input_dstep_field.getGlobalBounds().left,
		input_dstep_field.getGlobalBounds().top + input_dstep_field.getLocalBounds().height + vertical_shift * 5);
	button_restart.setFillColor(sf::Color(205, 207, 209));
	sf::Text text_button(text_input_dstep);
	text_button.setString("Clear");
	text_button.setPosition(button_restart.getPosition().x + button_restart.getLocalBounds().width / 3, button_restart.getPosition().y);

	int target = 0;
	int dstep = 0;
	//GUI
	sf::CircleShape circle(static_cast<float>(target));
	sf::Vector2f circle_pos{
		static_cast<float>(window.getSize().x * 0.5),
		static_cast<float>(window.getSize().y * 0.01) };
	circle.setPosition(circle_pos);
	circle.setFillColor(sf::Color(217, 217, 217));
	circle.setOutlineThickness(1.0f);
	circle.setOutlineColor(sf::Color::Black);

	sf::Text user_output;
	user_output.setFont(font);
	user_output.setCharacterSize(20);

	std::vector<sf::Vertex> vertexes;
	int enter_event_cnt = 0;
	bool input_received = false;
	bool distance_received = false;
	bool clear_received = false;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::TextEntered) {
				//handle backspace
				if (event.text.unicode == '\b') {
					if (enter_event_cnt == 0) {
						if (distance_str.size() > 0)
							distance_str.erase(std::prev(distance_str.end()), distance_str.end());
						text_user_input_distance.setString(distance_str);
					}
					else {
						if (dstep_str.size() > 0)
							dstep_str.erase(std::prev(dstep_str.end()), dstep_str.end());
						text_user_input_dstep.setString(dstep_str);
					}
				}
				if ((event.text.unicode < 48 || event.text.unicode > 57) && event.text.unicode != 13) break;
				//handle digits
				if (event.text.unicode != 13) {
					if (enter_event_cnt == 0) {
						distance_str.push_back(static_cast<char>(event.text.unicode));
						text_user_input_distance.setString(distance_str);
					}
					else if (enter_event_cnt == 1) {
						dstep_str.push_back(static_cast<char>(event.text.unicode));
						text_user_input_dstep.setString(dstep_str);
					}
				}
				else {
					//handle enter
					enter_event_cnt++;
					clear_received = false;
					if (enter_event_cnt == 1) {
						distance_received = true;
						target = std::stoi(distance_str);
						circle.setRadius(target);
					}
				}
				if (event.text.unicode == 13 && enter_event_cnt == 2) {
					dstep = std::stoi(dstep_str);
					if (!(target == 0 || dstep == 0)) {
						input_received = true;
						Path path;
						VECTOR::Vector finish = process_path(path, target * 1.0, dstep * 1.0);
						std::stringstream out;
						out << "After " << path.size() << " steps,\nthe subject's "
							<< "location\n(relative to the center)\nis:"
							<< finish << "\n";
						user_output.setString(out.str());
						user_output.setFillColor(sf::Color::Black);
						user_output.setPosition(text_user_input_dstep.getGlobalBounds().left,
							text_user_input_dstep.getGlobalBounds().top + text_user_input_dstep.getLocalBounds().height + vertical_shift);
						//create vertex array from path
						vertexes.resize(path.size() + 1);
						vertexes[0] = (sf::Vertex(
							{ static_cast<float>(circle.getPosition().x + circle.getRadius()), static_cast<float>(circle.getPosition().y + circle.getRadius()) }));
						vertexes[0].color = sf::Color::Blue;
						for (unsigned int i = 0; i < vertexes.size() - 1; ++i) {
							vertexes[i + 1] = (sf::Vertex(sf::Vector2f(
								static_cast<float>(path[i].first + circle.getPosition().x + circle.getRadius()),
								static_cast<float>(path[i].second + circle.getPosition().y + circle.getRadius()))));
							vertexes[i + 1].color = sf::Color::Blue;
						}
					}
				}
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (button_restart.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
						clear_received = true;
						target = 0;
						dstep = 0;
						distance_str.clear();
						text_user_input_distance.setString(distance_str);
						dstep_str.clear();
						text_user_input_dstep.setString(dstep_str);
						enter_event_cnt = 0;
						input_received = false;
						distance_received = false;
					}
				}
			}
		}

		window.clear(sf::Color::White);
		window.draw(text_input_distanse);
		window.draw(input_distance_field);
		window.draw(text_user_input_distance);
		window.draw(text_input_dstep);
		window.draw(input_dstep_field);
		window.draw(text_user_input_dstep);
		if (!clear_received) {
			if (input_received) {
				window.draw(user_output);
				window.draw(circle);
				window.draw(&vertexes[0], vertexes.size(), sf::LineStrip);
			}
		}
		window.draw(button_restart);
		window.draw(text_button);
		window.display();
	}

	return 0;
}
