#include "keyboard_mouse_helpers.h"
#include <SFML/Window/Mouse.hpp>
#include <windows.h>

void prim_bindings::move_cursor_x(const int delta_value)
{
	auto mouse_position = sf::Mouse::getPosition();
	mouse_position.x += delta_value;

	sf::Mouse::setPosition(mouse_position);
}

void prim_bindings::move_cursor_y(const int delta_value)
{
	auto mouse_position = sf::Mouse::getPosition();
	mouse_position.y += delta_value;

	sf::Mouse::setPosition(mouse_position);
}

void prim_bindings::mouse_cursor(const int delta_x, const int delta_y)
{
	auto mouse_position = sf::Mouse::getPosition();
	mouse_position.x += delta_x;
	mouse_position.y += delta_y;

	sf::Mouse::setPosition(mouse_position);
}

void prim_bindings::press_key(unsigned char key)
{
	//...
}

void prim_bindings::release_key(unsigned char key)
{
	//...
}