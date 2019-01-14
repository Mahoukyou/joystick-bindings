#include "SFML/Window.hpp"
#include "joystick.h"


int main()
{
	sf::Window window(sf::VideoMode(800, 600), "My Window");
	window.setFramerateLimit(60);

	prim_bindings::joystick joystick{ prim_bindings::joystick::any_joystick };

	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		joystick.pool_joystick(false);

		window.display();
	}

	return 0;
}