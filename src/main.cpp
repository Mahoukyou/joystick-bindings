#include "SFML/Window.hpp"
#include "joystick.h"
#include <thread>
#include <chrono>

#include <iostream>

void print_connected_joysticks()
{
	constexpr int max_joys{ 8 };

	for(int i = 0; i < max_joys; ++i)
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
int main()
{
	sf::Joystick::update();
	
	print_connected_joysticks();

	prim_bindings::joystick joystick{ 0 };
	add_buttons_ids(joystick);

	using namespace std::chrono_literals;
	while(true)
	{
		std::this_thread::sleep_for(1ms);
		joystick.pool_joystick(true);
	}

	return 0;
}