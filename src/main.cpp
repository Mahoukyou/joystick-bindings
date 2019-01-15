#include "SFML/Window.hpp"
#include "joystick.h"
#include <thread>
#include <chrono>

#include <iostream>

#include "keyboard_mouse_helpers.h"

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

// Add every possible button binding to joystick for tests
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
		binding.on_active = [i](const float prev, const float newv, const double /*delta*/) -> void
		{
			std::cout << "Axis " << i << " has has value: " << newv << '\n';
		};

		joystick.add_axis_binding(binding);
	}
}

int main()
{
	sf::Joystick::update();
	
	print_connected_joysticks();

	prim_bindings::joystick joystick{ 0 };

	// some test, remove later

	// cursor movement via controller axis, fast
	constexpr float cursor_move_mult = 25;
	prim_bindings::axis_binding mouse_X{ sf::Joystick::Axis::X, 1 };
	mouse_X.on_active = [cursor_move_mult](const float /*prev_value*/, const float newv, const double delta) -> void
	{
		prim_bindings::move_cursor_x(newv * delta * cursor_move_mult);
	};

	prim_bindings::axis_binding mouse_Y{ sf::Joystick::Axis::Y, 1 };
	mouse_Y.on_active = [cursor_move_mult](const float /*prev*/, const float newv, const double delta) -> void
	{
		prim_bindings::move_cursor_y(newv * delta * cursor_move_mult);
	};

	joystick.add_axis_binding(mouse_X);
	std::cout << joystick.has_axis_binding(mouse_Y.get_axis());
	joystick.add_axis_binding(mouse_Y);
	std::cout << joystick.has_axis_binding(mouse_Y.get_axis());

	// cursor movement via controller axis, slow
	constexpr float slow_cursor_move_mult = 10;
	prim_bindings::axis_binding mouse_X_slow{ sf::Joystick::Axis::R, 1 };
	mouse_X_slow.on_active = [slow_cursor_move_mult](const float /*prev_value*/, const float newv, const double delta) -> void
	{
		prim_bindings::move_cursor_x(newv * delta * slow_cursor_move_mult);
	};

	prim_bindings::axis_binding mouse_Y_slow{ sf::Joystick::Axis::Z, 1 };
	mouse_Y_slow.on_active = [slow_cursor_move_mult](const float /*prev*/, const float newv, const double delta) -> void
	{
		prim_bindings::move_cursor_y(newv * delta * slow_cursor_move_mult);
	};

	joystick.add_axis_binding(mouse_X_slow);
	joystick.add_axis_binding(mouse_Y_slow);

	// mouse buttons
	prim_bindings::button_binding mouseleft{ 2 };
	mouseleft.on_state_change = [](const bool state)
	{
		prim_bindings::send_mouse_button(prim_bindings::mouse_button::left, state);
	};

	prim_bindings::button_binding mouseright{ 1 };
	mouseright.on_state_change = [](const bool state)
	{
		prim_bindings::send_mouse_button(prim_bindings::mouse_button::right, state);
	};

	joystick.add_button_binding(mouseleft);
	joystick.add_button_binding(mouseright);

	// keyboard key test
	prim_bindings::button_binding key_a{ 0 };
	key_a.on_state_change = [](const bool state)
	{
		prim_bindings::send_key_input(0x41, state);
	};

	joystick.add_button_binding(key_a);

	using namespace std::chrono_literals;
	sf::Clock clock;
	while(true)
	{
		std::this_thread::sleep_for(1ms);
		joystick.pool_joystick(true, clock.getElapsedTime().asSeconds());
		clock.restart();
	}
}