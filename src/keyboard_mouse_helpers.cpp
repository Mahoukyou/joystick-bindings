#include "keyboard_mouse_helpers.h"
#include <SFML/Window/Mouse.hpp>
#include <windows.h>

namespace
{
	void send_mouse_input(const DWORD flags)
	{
		INPUT input[1];
		memset(input, 0, sizeof(input));

		input[0].type = INPUT_MOUSE;
		input[0].mi.dwFlags = flags;

		SendInput(1, input, sizeof(input));
	};
}

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

#ifdef _WINDOWS
void prim_bindings::press_key(unsigned char key)
{
	//...
}

void prim_bindings::release_key(unsigned char key)
{
	//...
}

void prim_bindings::press_mouse_button(const mouse_button button)
{
	DWORD flags{ 0 };
	switch(button)
	{
	case mouse_button::left:
		flags = MOUSEEVENTF_LEFTDOWN;
		break;

	case mouse_button::right:
		flags = MOUSEEVENTF_RIGHTDOWN;
		break;

	case mouse_button::middle:
		flags = MOUSEEVENTF_MIDDLEDOWN;
		break;
	}

	send_mouse_input(flags);
}

void prim_bindings::release_mouse_button(const mouse_button button)
{
	DWORD flags{ 0 };
	switch (button)
	{
	case mouse_button::left:
		flags = MOUSEEVENTF_LEFTUP;
		break;

	case mouse_button::right:
		flags = MOUSEEVENTF_RIGHTUP;
		break;

	case mouse_button::middle:
		flags = MOUSEEVENTF_MIDDLEUP;
		break;
	}

	send_mouse_input(flags);
}

void prim_bindings::send_mouse_button(const mouse_button button, const bool press)
{
	if(press)
	{
		press_mouse_button(button);
	}
	else
	{
		release_mouse_button(button);
	}
}

#endif