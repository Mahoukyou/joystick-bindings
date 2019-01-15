#include <thread>
#include <chrono>
#include <iostream>
#include <windows.h>

#include "src/joystick.h"
#include "src/keyboard_mouse_helpers.h"
#include "SFML/Window/Window.hpp"

void print_connected_joysticks()
{
	bool found_any_connected_joystick = false;
	for (int i = 0; i < sf::Joystick::Count; ++i)
	{
		if (sf::Joystick::isConnected(i))
		{
			auto id = sf::Joystick::getIdentification(i);
			std::cout << "Joystick: " << i << " connected. " << id.name.toAnsiString() <<
				". Vendor: " << id.vendorId << ". Product id: " << id.productId << ".\n";

			found_any_connected_joystick = true;
		}
	}

	if (!found_any_connected_joystick)
	{
		std::cout << "No connected joystick found\n";
	}
}

int main()
{
	sf::Joystick::update();

	print_connected_joysticks();

	std::cout << "Adding bindings to joystick id: 0\n";
	prim_bindings::joystick joystick{ 0 };

	// cursor movement via controller axis, fast
	constexpr float cursor_speed_multiplier = 25;
	prim_bindings::axis_binding cursor_movement_x{ sf::Joystick::Axis::X, 1 };
	cursor_movement_x.on_active = [cursor_speed_multiplier](const float /*prev_value*/, const float new_value, const double delta) -> void
	{
		prim_bindings::move_cursor_x(static_cast<int>(new_value * delta * cursor_speed_multiplier));
	};

	prim_bindings::axis_binding cursor_movement_y{ sf::Joystick::Axis::Y, 1 };
	cursor_movement_y.on_active = [cursor_speed_multiplier](const float /*prev_value*/, const float new_value, const double delta) -> void
	{
		prim_bindings::move_cursor_y(static_cast<int>(new_value * delta * cursor_speed_multiplier));
	};

	joystick.add_axis_binding(cursor_movement_x);
	joystick.add_axis_binding(cursor_movement_y);

	// cursor movement via controller axis, slow
	constexpr float slow_cursor_speed_multiplier = 10;
	prim_bindings::axis_binding cursor_movement_x_slow{ sf::Joystick::Axis::R, 1 };
	cursor_movement_x_slow.on_active = [slow_cursor_speed_multiplier](const float /*prev_value*/, const float new_value, const double delta) -> void
	{
		prim_bindings::move_cursor_x(static_cast<int>(new_value * delta * slow_cursor_speed_multiplier));
	};

	prim_bindings::axis_binding cursor_movement_y_slow{ sf::Joystick::Axis::Z, 1 };
	cursor_movement_y_slow.on_active = [slow_cursor_speed_multiplier](const float /*prev_value*/, const float new_value, const double delta) -> void
	{
		prim_bindings::move_cursor_y(static_cast<int>(new_value * delta * slow_cursor_speed_multiplier));
	};

	joystick.add_axis_binding(cursor_movement_x_slow);
	joystick.add_axis_binding(cursor_movement_y_slow);

	// mouse buttons
	prim_bindings::button_binding mouse_left_button{ 2 };
	mouse_left_button.on_state_change = [](const bool state)
	{
		prim_bindings::send_mouse_button(prim_bindings::mouse_button::left, state);
	};

	prim_bindings::button_binding mouse_right_button{ 1 };
	mouse_right_button.on_state_change = [](const bool state)
	{
		prim_bindings::send_mouse_button(prim_bindings::mouse_button::right, state);
	};

	joystick.add_button_binding(mouse_left_button);
	joystick.add_button_binding(mouse_right_button);

	// keyboard key test
	prim_bindings::button_binding key_a{ 0 };
	key_a.on_state_change = [](const bool state)
	{
		prim_bindings::send_key_input(0x41, state);
	};

	joystick.add_button_binding(key_a);

	// multiple keys test
	prim_bindings::button_binding alt_tab_key{ 3 };
	alt_tab_key.on_state_change = [](const bool state)
	{
		prim_bindings::send_key_input(VK_MENU, state);
		prim_bindings::send_key_input(VK_TAB, state);
	};

	joystick.add_button_binding(alt_tab_key);
			
	using namespace std::chrono_literals;
	sf::Clock clock;
	while(true)
	{
		std::this_thread::sleep_for(1ms);
		joystick.pool_joystick(true, clock.getElapsedTime().asSeconds());
		clock.restart();
	}
}