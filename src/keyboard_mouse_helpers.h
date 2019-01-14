#pragma once

// some helper functions that can be used to bind controller to keyboard and mouse
namespace prim_bindings
{

	void move_cursor_x(int delta_value);
	void move_cursor_y(int delta_value);
	void mouse_cursor(int delta_x, int delta_y);

#ifdef _WINDOWS
	enum class mouse_button { left, right, middle };

	/* key - virtual key code */
	void press_key(unsigned short key);

	/* key - virtual key code */
	void release_key(unsigned short key);

	/* key - virtual key code */
	void send_key_input(unsigned short key, bool pressed);

	void press_mouse_button(mouse_button button);
	void release_mouse_button(mouse_button button);
	void send_mouse_button(mouse_button button, bool pressed);
#else
	//button presses are only available on windows atm
#endif
}