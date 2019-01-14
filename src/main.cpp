#include "SFML/Window.hpp"
#include "joystick.h"
#include <thread>
#include <chrono>

#include <iostream>

void print_connected_joysticks()
{
	for(int i = 0; i < sf::Joystick::Count; ++i)
	{
		if(sf::Joystick::isConnected(i))
		{
			auto id = sf::Joystick::getIdentification(i);
			std::cout << "Joystick: " << i << " connected. " << id.name.toAnsiString() <<
				". Vendor: " << id.vendorId << ". Product id: " << id.productId << ".\n";
		}
	}
}

void add_buttons_ids(prim_bindings::joystick& joystick)
{
	for (unsigned int i = 0; i < sf::Joystick::getButtonCount(joystick.get_joystick_id()); ++i)
	{
		prim_bindings::button_binding binding{ i };
		binding.on_state_change = [i](const bool state) -> void
		{
			if(state)
			{
				std::cout << "Button " << i << " pressed\n";
			}
			else
			{
				std::cout << "Button " << i << " released\n";
			}
		};

		joystick.button_bindings.push_back(binding);
	}
}

void add_axis(prim_bindings::joystick& joystick)
{
	for (unsigned int i = 0; i < sf::Joystick::AxisCount; ++i)
	{
		const auto axis = static_cast<sf::Joystick::Axis>(i);
		if (!sf::Joystick::hasAxis(joystick.get_joystick_id(), axis))
		{
			continue;
		}

		prim_bindings::axis_binding binding{ axis, 1 };
		binding.on_active = [i](const float prev, const float newv, const double /*delta*/) -> void
		{
			std::cout << "Axis " << i << " has has value: " << newv << '\n';
		};

		joystick.axis_bindings.push_back(binding);
	}
}




int main()
{
	sf::Joystick::update();
	
	print_connected_joysticks();

	prim_bindings::joystick joystick{ 0 };
	add_buttons_ids(joystick);




	using namespace std::chrono_literals;
	sf::Clock clock;
	while(true)
	{
		std::this_thread::sleep_for(25ms);
		joystick.pool_joystick(true, clock.getElapsedTime().asSeconds());
	}
}