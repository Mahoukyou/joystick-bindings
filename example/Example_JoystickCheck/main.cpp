#include <thread>
#include <chrono>
#include <iostream>
#include "SFML/Window/Window.hpp"
#include "src/joystick.h"

void print_connected_joysticks()
{
	bool found_any_connected_joystick = false;
	for(int i = 0; i < sf::Joystick::Count; ++i)
	{
		if(sf::Joystick::isConnected(i))
		{
			auto id = sf::Joystick::getIdentification(i);
			std::cout << "Joystick: " << i << " connected. " << id.name.toAnsiString() <<
				". Vendor: " << id.vendorId << ". Product id: " << id.productId << ".\n";

			found_any_connected_joystick = true;
		}
	}

	if(!found_any_connected_joystick)
	{
		std::cout << "No connected joystick found\n";
	}
}

// Add every possible button binding to joystick for tests
void add_buttons_ids(prim_bindings::joystick& joystick)
{
	for (unsigned int i = 0; i < sf::Joystick::getButtonCount(joystick.get_joystick_id()); ++i)
	{
		prim_bindings::button_binding binding{ i };
		binding.on_state_change = [i, &joystick](const bool state) -> void
		{
			if(state)
			{
				std::cout << "Joystick id: " << joystick.get_joystick_id() << ", Button: " << i << " pressed\n";
			}
			else
			{
				std::cout << "Joystick id: " << joystick.get_joystick_id() << ", Button: " << i << " released\n";
			}
		};

		joystick.add_button_binding(binding);
	}
}

// Add every possible axis binding to joystick for tests
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
		binding.on_active = [i, &joystick](const float prev, const float newv, const double /*delta*/) -> void
		{
			std::cout << "Joystick id: " << joystick.get_joystick_id() << ", Axis: " << i << " has a value of: " << newv << '\n';
		};

		joystick.add_axis_binding(binding);
	}
}

int main()
{
	using namespace std::chrono_literals;
	using prim_bindings::joystick;

	sf::Joystick::update();
	print_connected_joysticks();

	std::vector<joystick> joysticks;
	for(int i = 0; i < sf::Joystick::Count; ++i)
	{
		if(sf::Joystick::isConnected(i))
		{
			joystick joy{ i };
			add_buttons_ids(joy);
			add_axis(joy);

			joysticks.push_back(std::move(joy));
		}
	}

	sf::Clock clock;
	while(true)
	{
		std::this_thread::sleep_for(1ms);
		for(auto& joy : joysticks)
		{
			joy.pool_joystick(true, clock.getElapsedTime().asSeconds());
		}

		clock.restart();
	}
}