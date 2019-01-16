#include "keyboard_mouse_helpers.h"
#include <SFML/Window/Mouse.hpp>
#include <windows.h>

namespace
{
	void send_mouse_input(const DWORD flags)
	{
		constexpr int input_size{ 1 };

		INPUT input[input_size];
		memset(input, 0, sizeof(input));

		input[0].type = INPUT_MOUSE;
		input[0].mi.dwFlags = flags;

		SendInput(input_size, input, sizeof(input));
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
void prim_bindings::press_key(const unsigned short key)
{
	send_key_input(key, false);
}

void prim_bindings::release_key(const unsigned short key)
{
	send_key_input(key, true);	
}

void prim_bindings::send_key_input(const unsigned short key, const bool pressed)
{
	constexpr int input_size{ 1 };

	INPUT input[input_size];
	memset(input, 0, sizeof(input));

	input[0].type = INPUT_KEYBOARD;
	input[0].ki.wVk = key;
	input[0].ki.dwFlags = pressed ? 0 : KEYEVENTF_KEYUP;

	SendInput(input_size, input, sizeof(input));
};

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

void prim_bindings::send_mouse_button(const mouse_button button, const bool pressed)
{
	if (pressed)
	{
		press_mouse_button(button);
	}
	else
	{
		release_mouse_button(button);
	}
}
#endif